#include <cassert>
#include <libastfri-cpp/ClangVisitor.hpp>

#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;

namespace libastfri::cpp {

lsfs::Expression *ClangVisitor::getExpression(clang::Expr *Expr) {
    // skontroluj pociatocny stav
    assert(visitedStatement == nullptr);
    assert(visitedExpression == nullptr);

    try {
        auto traversalFailed = TraverseStmt(Expr);
        if (traversalFailed) {
            // prehliadka sa nepodarila
            throw std::runtime_error("Expr traversal failed");
        }
        auto *expression = popVisitedExpression<lsfs::Expression>();

        if (expression != nullptr) {
            return expression; // ak sa nasiel expression, tak ho vrat
        }

        // nezachytili sme ziadny expression
        throw std::runtime_error("No expression found");
    } catch (std::exception &e) {
        auto *exprFac = &lsff::ExpressionFactory::getInstance();

        // clearVisited(); // TODO - je to potrebne?

        return exprFac->createUnknownExpression(e.what());
    }
}

bool ClangVisitor::VisitExpr(clang::Expr *Expr) { return true; }

bool ClangVisitor::VisitBinaryOperator(
    clang::BinaryOperator *Expr) {
    auto &exprFac = lsff::ExpressionFactory::getInstance();

    auto *left = getExpression(Expr->getLHS());
    auto *right = getExpression(Expr->getRHS());

    visitedExpression = exprFac.createBinaryExpression(
        Tools::convertBinaryOperator(Expr->getOpcode()), left, right);
    return false;
}

bool ClangVisitor::VisitIntegerLiteral(
    clang::IntegerLiteral *Expr) {
    auto &literalFac = lsff::LiteralFactory::getInstance();

    visitedExpression =
        literalFac.getIntLiteral(Expr->getValue().getSExtValue());
    return false;
}

bool ClangVisitor::VisitDeclRefExpr(clang::DeclRefExpr *Expr) {
    auto &declFac = lsff::DeclarationFactory::getInstance();
    auto &refFac = lsff::ReferenceFactory::getInstance();

    auto *var = declFac.createVariable(
        Expr->getNameInfo().getAsString(),
        Tools::convertType(Expr->getType()), nullptr);
    visitedExpression = refFac.createVarRefExpression(var);
    return false;
}

bool ClangVisitor::VisitCallExpr(clang::CallExpr *Expr) {
    auto &declFac = lsff::DeclarationFactory::getInstance();
    auto &refFac = lsff::ReferenceFactory::getInstance();
    auto &exprFac = lsff::ExpressionFactory::getInstance();

    std::vector<lsfs::Expression *> args;
    for (auto arg : Expr->arguments()) {
        args.push_back(getExpression(arg));
    }

    auto *functionDecl = llvm::dyn_cast<clang::FunctionDecl>(
        Expr->getCalleeDecl()->getAsFunction());

    auto *functionDef =

        visitedExpression = refFac.createFunctionCallExpression(
            functionDecl->getNameInfo().getAsString(), args);
    return false;
}

} // namespace libastfri::cpp