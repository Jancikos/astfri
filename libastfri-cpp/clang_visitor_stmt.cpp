#include "libastfri/structures/Declaration.hpp"
#include <cassert>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;

namespace libastfri::cpp {

lsfs::Statement *AstfriClangVisitor::getStatement(clang::Stmt *Declaration) {
    // skontroluj pociatocny stav
    assert(visitedStatement == nullptr);
    assert(visitedExpression == nullptr);
    assert(visitedDeclaration == nullptr);

    if (Declaration == nullptr) {
        return nullptr; // ak je nullptr, tak vrat nullptr
    }

    auto traversalFailed = TraverseStmt(Declaration);
    if (traversalFailed) {
        // TODO - lepsie ohandlovat chybu
        throw std::runtime_error("Stmt traversal failed");
        return nullptr; // prehliadka sa nepodarila
    }
    auto *statement = popVisitedStatement<lsfs::Statement>();

    if (statement != nullptr) {
        return statement; // ak sa nasiel statement, tak ho vrat
    }

    auto &statementFac = lsff::StatementFactory::getInstance();
    // skus skontrovlovat, ci sa nejedna o declaration statement
    auto *decl = popVisitedDeclaration<lsfs::Declaration>();
    if (decl != nullptr) {

        auto *expr = popVisitedExpression<lsfs::Expression>();
        if (expr != nullptr) {
            return statementFac.createDeclarationAndAssigmentStatement(decl,
                                                                       expr);
        }

        return statementFac.createDeclarationStatement(decl);
    }

    // skus skontrovlovat, ci sa nejedna o expression statement
    auto *expr = popVisitedExpression<lsfs::Expression>();
    if (expr != nullptr) {
        return statementFac.createExpressionStatement(expr);
    }

    throw std::runtime_error("No statement or expression found");
    return nullptr; // nezachytili sme ziadny statement ani expression
}

bool AstfriClangVisitor::VisitStmt(clang::Stmt *Declaration) { return true; }

bool AstfriClangVisitor::VisitCompoundStmt(clang::CompoundStmt *Declaration) {

    auto &statementFac = lsff::StatementFactory::getInstance();
    auto *compoundStatement = statementFac.createCompoundStatement({});

    for (auto stmt : Declaration->body()) {
        compoundStatement->statements.push_back(getStatement(stmt));
    }

    visitedStatement = compoundStatement;

    return false;
}

bool AstfriClangVisitor::VisitReturnStmt(clang::ReturnStmt *Declaration) {
    auto &statementFac = lsff::StatementFactory::getInstance();

    visitedStatement = statementFac.createReturnStatement(
        getExpression(Declaration->getRetValue()));
    return false;
}

bool AstfriClangVisitor::VisitIfStmt(clang::IfStmt *Declaration) {
    auto &statementFac = lsff::StatementFactory::getInstance();
    auto &declFac = lsff::DeclarationFactory::getInstance();

    auto *thenStmt = getStatement(Declaration->getThen());

    auto *elseStmt = getStatement(Declaration->getElse());

    auto *condition = getExpression(Declaration->getCond());

    visitedStatement = statementFac.createIfConditionalStatement(
        condition, thenStmt, elseStmt);
    return false;
}

bool AstfriClangVisitor::VisitWhileStmt(clang::WhileStmt *Declaration) {
    auto &statementFac = lsff::StatementFactory::getInstance();
    auto &declFac = lsff::DeclarationFactory::getInstance();

    auto *body = getStatement(Declaration->getBody());

    auto *condition = getExpression(Declaration->getCond());

    visitedStatement = statementFac.createWhileLoopStatement(condition, body);
    return false;
}
} // namespace libastfri::cpp