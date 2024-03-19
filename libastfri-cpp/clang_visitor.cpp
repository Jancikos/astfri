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
  lsfs::Type *returnType =
      Tools::convertType(Declaration->getReturnType());

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

  // The return value indicates whether we want the visitation to proceed.
  // Return false to stop the traversal of the AST.
  return false;
}

bool AstfriClangVisitor::VisitStmt(clang::Stmt *Declaration) {

  // visitedStatement => lsfs::AssigmentStatement
  // TODO - zistit kedy ma byt BinaryOperator pouzity ako expression a kedy ako
  // statement
  if (auto *assigmentStmt =
          llvm::dyn_cast<clang::BinaryOperator>(Declaration)) {
    auto &funFac = lsff::FunctionFactory::getInstance();
    auto &statementFac = lsff::StatementFactory::getInstance();

    if (assigmentStmt->getOpcode() != clang::BinaryOperatorKind::BO_Assign) {
      return false; // imeplementovat ine operatory
    }

    // TOOD - upravit na VisitExpr
    auto *lhs = static_cast<clang::DeclRefExpr *>(assigmentStmt->getLHS());
    auto *rhs = static_cast<clang::Expr *>(assigmentStmt->getRHS());

    VisitExpr(rhs);
    auto *right = popVisitedExpression<lsfs::Expression>();

    auto *left = funFac.createVariable(
        lhs->getNameInfo().getAsString(), Tools::convertType(lhs->getType()),
        nullptr); // todo - extrahovat do VisitDeclRefExpr

    visitedStatement = statementFac.createAssigmentStatement(left, right);
    return false;
  }

   return true;
}

bool AstfriClangVisitor::VisitCompoundStmt(clang::CompoundStmt *Declaration) {
  // For debugging, dumping the AST nodes will show which nodes are already
  // being visited.
  // Declaration->dump();

  auto &statementFac = lsff::StatementFactory::getInstance();
  auto *compoundStatement = statementFac.createCompoundStatement({});

  for (auto stmt : Declaration->body()) {
    TraverseStmt(stmt);
    compoundStatement->statements.push_back(popVisitedStatement<lsfs::Statement>());
  }

  visitedStatement = compoundStatement;

  return false;
}

bool AstfriClangVisitor::VisitVarDecl(clang::VarDecl *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &statementFac = lsff::StatementFactory::getInstance();

  auto *var = funFac.createVariable(
      Declaration->getNameAsString(), Tools::convertType(Declaration->getType()), nullptr);

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
  visitedStatement = statementFac.createReturnStatement(visitedExpression);
  return false;
}

bool AstfriClangVisitor::VisitParmVarDecl(clang::ParmVarDecl *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();

  lsfs::Expression *defValue = nullptr;
  if (Declaration->hasDefaultArg()) {
    VisitExpr(Declaration->getDefaultArg());
    defValue = visitedExpression;
  }

  visitedVariable = funFac.createParameter(
      Declaration->getNameAsString(),
      Tools::convertType(Declaration->getType()), defValue);

  return false;
}

// todo - overit preco sa zrejme nevolag
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

bool AstfriClangVisitor::VisitExpr(clang::Expr *Declaration) {
  if (Declaration == nullptr) {
    visitedExpression = nullptr;
    return false;
  }

  auto &exprFac = lsff::ExpressionFactory::getInstance();
  auto &literalFac = lsff::LiteralFactory::getInstance();
  auto &typeFac = lsff::TypeFactory::getInstance();

  // visitedExpression => lsfs::BinaryExpression
  if (auto *binaryExpr = llvm::dyn_cast<clang::BinaryOperator>(Declaration)) {
    VisitExpr(binaryExpr->getLHS());
    auto *left =
        popVisitedExpression<lsfs::Expression>();

    VisitExpr(binaryExpr->getRHS());
    auto *right =
        popVisitedExpression<lsfs::Expression>();

    visitedExpression = exprFac.createBinaryExpression(
        Tools::convertBinaryOperator(binaryExpr->getOpcode()), left, right);
    return false;
  }

  return true;
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
    args.push_back(visitedExpression);
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