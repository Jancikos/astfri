#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include "libastfri/factories/FunctionFactory.hpp"
#include "libastfri/structures/Expression.hpp"
#include "libastfri/structures/Function.hpp"
#include "libastfri/structures/Statement.hpp"
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace libastfri::cpp {
AstfriClangVisitor::AstfriClangVisitor(
    libastfri::structures::TranslationUnitStatement &visitedTranslationUnit)
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

  auto &funFac = libastfri::factories::FunctionFactory::getInstance();
  auto &literalFac = libastfri::factories::LiteralFactory::getInstance();
  auto &statementFac = libastfri::factories::StatementFactory::getInstance();

  // title
  std::string title = Declaration->getNameInfo().getAsString();

  // return type
  libastfri::structures::Type *returnType =
      Tools::convertType(Declaration->getReturnType());

  // params
  std::vector<libastfri::structures::ParameterDefinition *> params;
  for (auto param : Declaration->parameters()) {
    // param->dump();

    VisitParmVarDecl(param);
    params.emplace_back(
        static_cast<libastfri::structures::ParameterDefinition *>(
            visitedVariable));
  }

  // body
  VisitCompoundStmt(static_cast<clang::CompoundStmt *>(Declaration->getBody()));
  auto *body =
      static_cast<libastfri::structures::CompoundStatement *>(visitedStatement);

  visitedTranslationUnit->functions.push_back(funFac.createFunction(title, params, body, returnType));
  //   visitedFunction = visitedTranslationUnit->functions.back();

  // The return value indicates whether we want the visitation to proceed.
  // Return false to stop the traversal of the AST.
  return false;
}

bool AstfriClangVisitor::VisitStmt(clang::Stmt *Declaration) {

  // visitedStatement => libastfri::structures::AssigmentStatement
  // TODO - zistit kedy ma byt BinaryOperator pouzity ako expression a kedy ako
  // statement
  if (auto *assigmentStmt =
          llvm::dyn_cast<clang::BinaryOperator>(Declaration)) {
    auto &funFac = libastfri::factories::FunctionFactory::getInstance();
    auto &statementFac = libastfri::factories::StatementFactory::getInstance();

    if (assigmentStmt->getOpcode() != clang::BinaryOperatorKind::BO_Assign) {
      return false; // imeplementovat ine operatory
    }

    auto *lhs = static_cast<clang::DeclRefExpr *>(assigmentStmt->getLHS());
    auto *rhs = static_cast<clang::Expr *>(assigmentStmt->getRHS());

    VisitExpr(rhs);
    auto *right =
        static_cast<libastfri::structures::Expression *>(visitedExpression);

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

  auto &statementFac = libastfri::factories::StatementFactory::getInstance();
  auto *compoundStatement = statementFac.createCompoundStatement({});

  for (auto stmt : Declaration->body()) {
    VisitStmt(stmt);
    compoundStatement->statements.push_back(visitedStatement);
  }

  visitedStatement = compoundStatement;

  return false;
}

bool AstfriClangVisitor::VisitDeclStmt(clang::DeclStmt *Declaration) {
  auto &funFac = libastfri::factories::FunctionFactory::getInstance();
  auto &statementFac = libastfri::factories::StatementFactory::getInstance();

  auto *decl = static_cast<clang::VarDecl *>(Declaration->getSingleDecl());

  auto *var = funFac.createVariable(
      decl->getNameAsString(), Tools::convertType(decl->getType()), nullptr);

  if (decl->hasInit()) {
    VisitExpr(decl->getInit());
    auto *init =
        static_cast<libastfri::structures::Expression *>(visitedExpression);
    visitedStatement =
        statementFac.createDeclarationAndAssigmentStatement(var, init);
    return false;
  }

  visitedStatement = statementFac.createDeclarationStatement(var);
  return false;
}

bool AstfriClangVisitor::VisitReturnStmt(clang::ReturnStmt *Declaration) {
  auto &statementFac = libastfri::factories::StatementFactory::getInstance();

  VisitExpr(Declaration->getRetValue());
  visitedStatement = statementFac.createReturnStatement(visitedExpression);
  return false;
}

bool AstfriClangVisitor::VisitParmVarDecl(clang::ParmVarDecl *Declaration) {
  auto &funFac = libastfri::factories::FunctionFactory::getInstance();

  libastfri::structures::Expression *defValue = nullptr;
  if (Declaration->hasDefaultArg()) {
    VisitExpr(Declaration->getDefaultArg());
    defValue = visitedExpression;
  }

  visitedVariable = funFac.createParameter(
      Declaration->getNameAsString(),
      Tools::convertType(Declaration->getType()), defValue);

  return false;
}

bool AstfriClangVisitor::VisitExpr(clang::Expr *Declaration) {
  if (Declaration == nullptr) {
    visitedExpression = nullptr;
    return false;
  }

  auto &exprFac = libastfri::factories::ExpressionFactory::getInstance();
  auto &literalFac = libastfri::factories::LiteralFactory::getInstance();
  auto &typeFac = libastfri::factories::TypeFactory::getInstance();

  // visitedExpression => libastfri::structures::BinaryExpression
  if (auto *binaryExpr = llvm::dyn_cast<clang::BinaryOperator>(Declaration)) {
    VisitExpr(binaryExpr->getLHS());
    auto *left =
        static_cast<libastfri::structures::Expression *>(visitedExpression);

    VisitExpr(binaryExpr->getRHS());
    auto *right =
        static_cast<libastfri::structures::Expression *>(visitedExpression);

    visitedExpression = exprFac.createBinaryExpression(
        Tools::convertBinaryOperator(binaryExpr->getOpcode()), left, right);
    return false;
  }

  return true;
}

bool AstfriClangVisitor::VisitIntegerLiteral(
    clang::IntegerLiteral *Declaration) {
  auto &literalFac = libastfri::factories::LiteralFactory::getInstance();

  visitedExpression =
      literalFac.getIntLiteral(Declaration->getValue().getSExtValue());
  return false;
}

bool AstfriClangVisitor::VisitDeclRefExpr(clang::DeclRefExpr *Declaration) {
  auto &funFac = libastfri::factories::FunctionFactory::getInstance();
  auto &refFac = libastfri::factories::ReferenceFactory::getInstance();

  auto *var = funFac.createVariable(Declaration->getNameInfo().getAsString(),
                                    Tools::convertType(Declaration->getType()),
                                    nullptr);
  visitedExpression = refFac.createVarRefExpression(var);
  return false;
}
} // namespace libastfri::cpp