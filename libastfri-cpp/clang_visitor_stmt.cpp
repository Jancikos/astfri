#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri/factories/FunctionFactory.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Function.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;
namespace lsfs = libastfri::structures;

namespace libastfri::cpp {

bool AstfriClangVisitor::TraverseStmt(clang::Stmt *S,
                                      DataRecursionQueue *Queue) {
  if (S == nullptr) {
    return true;
  }

  auto result = RecursiveASTVisitor::TraverseStmt(S, Queue);

  if (result) {
    return true;
  }

  if (visitedStatement != nullptr) {
    return false; // nasiel sa statement
  }

  // skus pozriet ci sa nejedna o expression
  auto *expr = popVisitedExpression<Expression>();

  if (expr == nullptr) {
    return true; // nenasiel sa ziadny nacitany statement ani expression
  }

  // ak sa jedna o binary expression s operaciou priradenia, tak ho spracuj ako
  // assigment statement
  if (auto *binaryExpr = static_cast<lsfs::BinaryExpression *>(expr)) {
    if (binaryExpr->op == lsfs::BinaryOperators::Assign) {
      auto &statementFac = lsff::StatementFactory::getInstance();

      auto *left = static_cast<lsfs::VarRefExpression *>(binaryExpr->left); // TODO - vyriesit nejako bezpecnejsie
      auto *right = binaryExpr->right;

      visitedStatement =
          statementFac.createAssigmentStatement(left->variable, right);
      return false;
    }
  }

  // ak sa jedna o neodchyteny expression, tak ho spracuj ako expression
  // statement
  auto &statementFac = lsff::StatementFactory::getInstance();
  visitedStatement = statementFac.createExpressionStatement(expr);
  return false; // nasiel sa nacitany expression statement
}

bool AstfriClangVisitor::VisitStmt(clang::Stmt *Declaration) { return true; }

bool AstfriClangVisitor::VisitCompoundStmt(clang::CompoundStmt *Declaration) {

  auto &statementFac = lsff::StatementFactory::getInstance();
  auto *compoundStatement = statementFac.createCompoundStatement({});

  for (auto stmt : Declaration->body()) {
    TraverseStmt(stmt);
    compoundStatement->statements.push_back(
        popVisitedStatement<lsfs::Statement>());
  }

  visitedStatement = compoundStatement;

  return false;
}

bool AstfriClangVisitor::VisitReturnStmt(clang::ReturnStmt *Declaration) {
  auto &statementFac = lsff::StatementFactory::getInstance();

  VisitExpr(Declaration->getRetValue());
  visitedStatement = statementFac.createReturnStatement(
      popVisitedExpression<lsfs::Expression>());
  return false;
}

bool AstfriClangVisitor::VisitIfStmt(clang::IfStmt *Declaration) {
  auto &statementFac = lsff::StatementFactory::getInstance();
  auto &funFac = lsff::FunctionFactory::getInstance();

  TraverseStmt(Declaration->getThen());
  Declaration->getThen()->dump();
  auto *thenStmt = popVisitedStatement<lsfs::CompoundStatement>();

  TraverseStmt(Declaration->getElse());
  auto *elseStmt = popVisitedStatement<lsfs::Statement>();

  VisitExpr(Declaration->getCond());
  auto *condition = popVisitedExpression<lsfs::Expression>();

  visitedStatement =
      statementFac.createIfConditionalStatement(condition, thenStmt, elseStmt);
  return false;
}

bool AstfriClangVisitor::VisitWhileStmt(clang::WhileStmt *Declaration) {
  auto &statementFac = lsff::StatementFactory::getInstance();
  auto &funFac = lsff::FunctionFactory::getInstance();

  VisitStmt(Declaration->getBody());
  auto *body = popVisitedStatement<lsfs::Statement>();

  VisitExpr(Declaration->getCond());
  auto *condition = popVisitedExpression<lsfs::Expression>();

  visitedStatement = statementFac.createWhileLoopStatement(condition, body);
  return false;
}
} // namespace libastfri::cpp