#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include "libastfri-cpp/clang_tools.hpp"
#include "libastfri/factories/FunctionFactory.hpp"
#include "libastfri/structures/Expression.hpp"
#include "libastfri/structures/Function.hpp"
#include "libastfri/structures/Statement.hpp"
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;
namespace lsfs = libastfri::structures;

namespace libastfri::cpp {
AstfriClangVisitor::AstfriClangVisitor(
    lsfs::TranslationUnit &visitedTranslationUnit)
    : visitedTranslationUnit(&visitedTranslationUnit) {}

bool AstfriClangVisitor::VisitTranslationUnitDecl(
    clang::TranslationUnitDecl *Declaration) {

  for (auto *decl : Declaration->decls()) {
    if (auto *funDecl = llvm::dyn_cast<clang::FunctionDecl>(decl)) {
      VisitFunctionDecl(funDecl);
      // visitedTranslationUnit->functions.push_back(visitedFunction);
    }
  }

  return false;
}

bool AstfriClangVisitor::VisitFunctionDecl(clang::FunctionDecl *Declaration) {
  // For debugging, dumping the AST nodes will show which nodes are already
  // being visited.
  Declaration->dump();

  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &literalFac = lsff::LiteralFactory::getInstance();
  auto &statementFac = lsff::StatementFactory::getInstance();

  // title
  std::string title = Declaration->getNameInfo().getAsString();

  // return type
  lsfs::Type *returnType = Tools::convertType(Declaration->getReturnType());

  // params
  std::vector<lsfs::ParameterDefinition *> params;
  for (auto param : Declaration->parameters()) {
    // param->dump();

    VisitParmVarDecl(param);
    params.emplace_back(popVisitedVariable<lsfs::ParameterDefinition>());
  }

  // body
  VisitCompoundStmt(static_cast<clang::CompoundStmt *>(Declaration->getBody()));
  auto *body = popVisitedStatement<lsfs::CompoundStatement>();

  visitedTranslationUnit->functions.push_back(
      funFac.createFunction(title, params, body, returnType));
  //   visitedFunction = visitedTranslationUnit->functions.back();

  return false;
}

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

bool AstfriClangVisitor::VisitVarDecl(clang::VarDecl *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &statementFac = lsff::StatementFactory::getInstance();

  auto *var = funFac.createVariable(Declaration->getNameAsString(),
                                    Tools::convertType(Declaration->getType()),
                                    nullptr);

  if (Declaration->hasInit()) {
    VisitExpr(Declaration->getInit());
    auto *init = popVisitedExpression<lsfs::Expression>();
    visitedStatement =
        statementFac.createDeclarationAndAssigmentStatement(var, init);
    return false;
  }

  visitedStatement = statementFac.createDeclarationStatement(var);
  return false;
}

bool AstfriClangVisitor::VisitReturnStmt(clang::ReturnStmt *Declaration) {
  auto &statementFac = lsff::StatementFactory::getInstance();

  VisitExpr(Declaration->getRetValue());
  visitedStatement = statementFac.createReturnStatement(
      popVisitedExpression<lsfs::Expression>());
  return false;
}

bool AstfriClangVisitor::VisitParmVarDecl(clang::ParmVarDecl *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();

  lsfs::Expression *defValue = nullptr;
  if (Declaration->hasDefaultArg()) {
    VisitExpr(Declaration->getDefaultArg());
    defValue = popVisitedExpression<lsfs::Expression>();
  }

  visitedVariable = funFac.createParameter(
      Declaration->getNameAsString(),
      Tools::convertType(Declaration->getType()), defValue);

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

template <typename T> T *AstfriClangVisitor::popVisitedStatement() {
  return AstfriClangTools::popPointer<T>(visitedStatement);
}

template <typename T> T *AstfriClangVisitor::popVisitedExpression() {
  return AstfriClangTools::popPointer<T>(visitedExpression);
}

template <typename T> T *AstfriClangVisitor::popVisitedVariable() {
  return AstfriClangTools::popPointer<T>(visitedVariable);
}

template <typename T> T *AstfriClangVisitor::popVisitedFunction() {
  return AstfriClangTools::popPointer<T>(visitedFunction);
}

} // namespace libastfri::cpp