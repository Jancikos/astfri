#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri-cpp/clang_tools.hpp>
#include <libastfri/factories/FunctionFactory.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Function.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;
namespace lsfs = libastfri::structures;

namespace libastfri::cpp {
bool AstfriClangVisitor::VisitExpr(clang::Expr *Declaration) { return true; }

bool AstfriClangVisitor::VisitBinaryOperator(
    clang::BinaryOperator *Declaration) {
  auto &exprFac = lsff::ExpressionFactory::getInstance();

  // TODO - neviem spustit len TraverseExpr ale musim volat cely TraverseStmt???
  // viem si naimplementovat vlastny TraverseExpr?

  RecursiveASTVisitor::TraverseStmt(
      Declaration->getLHS()); // musim volat TraverseStmt z predka, aby sa
                              // neriesilo spracovanie LHS ako statement
  auto *left = popVisitedExpression<lsfs::Expression>();

  RecursiveASTVisitor::TraverseStmt(Declaration->getRHS());
  auto *right = popVisitedExpression<lsfs::Expression>();

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
  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &refFac = lsff::ReferenceFactory::getInstance();

  auto *var = funFac.createVariable(Declaration->getNameInfo().getAsString(),
                                    Tools::convertType(Declaration->getType()),
                                    nullptr);
  visitedExpression = refFac.createVarRefExpression(var);
  return false;
}

bool AstfriClangVisitor::VisitCallExpr(clang::CallExpr *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &refFac = lsff::ReferenceFactory::getInstance();
  auto &exprFac = lsff::ExpressionFactory::getInstance();

  std::vector<lsfs::Expression *> args;
  for (auto arg : Declaration->arguments()) {
    VisitExpr(arg);
    args.push_back(popVisitedExpression<Expression>());
  }

  auto *functionDecl =
      static_cast<clang::FunctionDecl *>(Declaration->getCalleeDecl());

  visitedExpression = refFac.createFunctionCallExpression(
      functionDecl->getNameInfo().getAsString(), args);

  return false;
}

} // namespace libastfri::cpp