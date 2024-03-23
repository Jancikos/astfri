#include <cassert>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;

namespace libastfri::cpp {

lsfs::Expression *AstfriClangVisitor::getExpression(clang::Expr *Declaration) {
    // skontroluj pociatocny stav
    assert(visitedStatement == nullptr);
    assert(visitedExpression == nullptr);

    try {
        auto traversalFailed = TraverseStmt(Declaration);
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