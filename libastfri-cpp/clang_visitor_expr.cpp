#include <cassert>
#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri-cpp/clang_tools.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Declaration.hpp>

namespace lsff = libastfri::factories;
namespace lsfs = libastfri::structures;

namespace libastfri::cpp {

lsfs::Expression *AstfriClangVisitor::getExpression(clang::Expr *Declaration) {
    // skontroluj pociatocny stav
    assert(visitedStatement == nullptr);
    assert(visitedExpression == nullptr);

    auto traversalFailed = TraverseStmt(Declaration);
    if (traversalFailed) {
        throw std::runtime_error("Expr traversal failed");
        return nullptr; // prehliadka sa nepodarila
    }
    auto *expression = Tools::popPointer<lsfs::Expression>(visitedExpression);

    if (expression != nullptr) {
        return expression; // ak sa nasiel expression, tak ho vrat
    }

    throw std::runtime_error("No expression found");
    return nullptr; // nezachytili sme ziadny expression
}

bool AstfriClangVisitor::VisitExpr(clang::Expr *Declaration) { return true; }

bool AstfriClangVisitor::VisitBinaryOperator(
    clang::BinaryOperator *Declaration) {
    auto &exprFac = lsff::ExpressionFactory::getInstance();

    auto *left = getExpression(Declaration->getLHS());
    auto *right = getExpression(Declaration->getRHS());

    visitedExpression = exprFac.createBinaryExpression(
        Tools::convertBinaryOperator(Declaration->getOpcode()), left, right);
    return false;
}

bool AstfriClangVisitor::VisitIntegerLiteral(
    clang::IntegerLiteral *Declaration) {
    auto &literalFac = lsff::LiteralFactory::getInstance();

    visitedExpression =
        literalFac.getIntLiteral(Declaration->getValue().getSExtValue());
    return false;
}

bool AstfriClangVisitor::VisitDeclRefExpr(clang::DeclRefExpr *Declaration) {
    auto &declFac = lsff::DeclarationFactory::getInstance();
    auto &refFac = lsff::ReferenceFactory::getInstance();

    auto *var = declFac.createVariable(
        Declaration->getNameInfo().getAsString(),
        Tools::convertType(Declaration->getType()), nullptr);
    visitedExpression = refFac.createVarRefExpression(var);
    return false;
}

bool AstfriClangVisitor::VisitCallExpr(clang::CallExpr *Declaration) {
    auto &declFac = lsff::DeclarationFactory::getInstance();
    auto &refFac = lsff::ReferenceFactory::getInstance();
    auto &exprFac = lsff::ExpressionFactory::getInstance();

    std::vector<lsfs::Expression *> args;
    for (auto arg : Declaration->arguments()) {
        args.push_back(getExpression(arg));
    }

    auto *functionDecl = llvm::dyn_cast<clang::FunctionDecl>(
        Declaration->getCalleeDecl()->getAsFunction());

    auto *functionDef = 

    visitedExpression = refFac.createFunctionCallExpression(
        functionDecl->getNameInfo().getAsString(), args);
    return false;
}

} // namespace libastfri::cpp