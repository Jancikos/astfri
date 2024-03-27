#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

#include <cassert>
#include <libastfri-cpp/ClangVisitor.hpp>

namespace lsff = libastfri::factories;

namespace libastfri::cpp
{

lsfs::Statement* ClangVisitor::getStatement(clang::Stmt* Stmt)
{
    // skontroluj pociatocny stav
    assert(visitedStatement == nullptr);
    assert(visitedExpression == nullptr);
    assert(visitedDeclaration == nullptr);

    try
    {
        if (Stmt == nullptr)
        {
            // nullovy pointer na vstupe
            throw std::runtime_error("Null pointer to statement");
        }

        auto traversalFailed = TraverseStmt(Stmt);
        if (traversalFailed)
        {
            // prehliadka sa nepodarila
            throw std::runtime_error("Stmt traversal failed");
        }
        auto* statement = popVisitedStatement<lsfs::Statement>();

        if (statement != nullptr)
        {
            return statement; // ak sa nasiel statement, tak ho vrat
        }

        auto& statementFac = lsff::StatementFactory::getInstance();
        // skus skontrovlovat, ci sa nejedna o declaration statement
        auto* decl = popVisitedDeclaration<lsfs::Declaration>();
        if (decl != nullptr)
        {

            auto* expr = popVisitedExpression<lsfs::Expression>();
            if (expr != nullptr)
            {
                // WARN - toto bude treba este otestovat, ze aka dalsia
                // deklaracia tu moze nastat
                return statementFac.createDeclarationAndAssigmentStatement(
                    decl,
                    expr
                );
            }

            return statementFac.createDeclarationStatement(decl);
        }

        // skus skontrovlovat, ci sa nejedna o expression statement
        auto* expr = popVisitedExpression<lsfs::Expression>();
        if (expr != nullptr)
        {
            return statementFac.createExpressionStatement(expr);
        }

        // nezachytili sme ziadny statement ani expression
        throw std::runtime_error("No statement or expression found");
    }
    catch (std::exception& e)
    {
        auto* statementFac = &lsff::StatementFactory::getInstance();

        clearVisited();

        return statementFac->createUnknownStatement(e.what());
    }
}

bool ClangVisitor::VisitStmt(clang::Stmt* Stmt)
{
    return true;
}

bool ClangVisitor::VisitCompoundStmt(clang::CompoundStmt* Stmt)
{

    auto& statementFac      = lsff::StatementFactory::getInstance();
    auto* compoundStatement = statementFac.createCompoundStatement({});

    for (auto nestedStmt : Stmt->body())
    {
        compoundStatement->statements.push_back(getStatement(nestedStmt));
    }

    visitedStatement = compoundStatement;

    return false;
}

bool ClangVisitor::VisitReturnStmt(clang::ReturnStmt* Stmt)
{
    auto& statementFac = lsff::StatementFactory::getInstance();

    visitedStatement
        = statementFac.createReturnStatement(getExpression(Stmt->getRetValue())
        );
    return false;
}

bool ClangVisitor::VisitIfStmt(clang::IfStmt* Stmt)
{
    auto& statementFac        = lsff::StatementFactory::getInstance();
    auto& declFac             = lsff::DeclarationFactory::getInstance();

    auto* thenStmt            = getStatement(Stmt->getThen());

    lsfs::Statement* elseStmt = nullptr;
    if (Stmt->getElse() != nullptr)
    {
        elseStmt = getStatement(Stmt->getElse());
    }

    auto* condition  = getExpression(Stmt->getCond());

    visitedStatement = statementFac.createIfConditionalStatement(
        condition,
        thenStmt,
        elseStmt
    );
    return false;
}

bool ClangVisitor::VisitWhileStmt(clang::WhileStmt* Stmt)
{
    auto& statementFac = lsff::StatementFactory::getInstance();
    auto& declFac      = lsff::DeclarationFactory::getInstance();

    auto* body         = getStatement(Stmt->getBody());

    auto* condition    = getExpression(Stmt->getCond());

    visitedStatement   = statementFac.createWhileLoopStatement(condition, body);
    return false;
}

bool ClangVisitor::VisitForStmt(clang::ForStmt* Stmt)
{
    auto& statementFac = lsff::StatementFactory::getInstance();
    auto& declFac      = lsff::DeclarationFactory::getInstance();

    auto* body         = getStatement(Stmt->getBody());

    auto* condition    = getExpression(Stmt->getCond());
    auto* init         = getStatement(Stmt->getInit());
    auto* inc          = getExpression(Stmt->getInc());

    visitedStatement
        = statementFac.createForLoopStatement(init, condition, inc, body);
    return false;
}

} // namespace libastfri::cpp