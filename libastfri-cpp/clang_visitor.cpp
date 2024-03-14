#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include "libastfri/factories/FunctionFactory.hpp"
#include "libastfri/structures/Expression.hpp"
#include "libastfri/structures/Function.hpp"
#include "libastfri/structures/Statement.hpp"
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

bool AstfriClangVisitor::VisitTranslationUnitDecl(
    clang::TranslationUnitDecl *Declaration) {
  visitedTranslationUnit = libastfri::factories::StatementFactory::getInstance()
                               .createTranslationUnitStatement({});

  for (auto *decl : Declaration->decls()) {
    if (auto *funDecl = llvm::dyn_cast<clang::FunctionDecl>(decl)) {
      VisitFunctionDecl(funDecl);
      visitedTranslationUnit->functions.push_back(visitedFunction);
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
      convertType(Declaration->getReturnType());

  // params
  std::vector<libastfri::structures::ParameterDefinition *> params;
  for (auto param : Declaration->parameters()) {
    // param->dump();

    VisitParmVarDecl(param);
    params.push_back(static_cast<libastfri::structures::ParameterDefinition *>(
        visitedVariable));
  }

  // body
  VisitCompoundStmt(static_cast<clang::CompoundStmt *>(Declaration->getBody()));
  auto *body =
      static_cast<libastfri::structures::CompoundStatement *>(visitedStatement);

  visitedFunction = funFac.createFunction(title, params, body, returnType);

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
        lhs->getNameInfo().getAsString(), convertType(lhs->getType()),
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

  auto *var = funFac.createVariable(decl->getNameAsString(),
                                    convertType(decl->getType()), nullptr);

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

  visitedVariable =
      funFac.createParameter(Declaration->getNameAsString(),
                             convertType(Declaration->getType()), defValue);

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
        convertBinaryOperator(binaryExpr->getOpcode()), left, right);
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

  auto *var =
      funFac.createVariable(Declaration->getNameInfo().getAsString(),
                            convertType(Declaration->getType()), nullptr);
  visitedExpression = refFac.createVarRefExpression(var);
  return false;
}

// TOOD - premysliet kam toto vytiahnut
Type *AstfriClangVisitor::convertType(clang::QualType qt) {
  auto &typeFac = libastfri::factories::TypeFactory::getInstance();

  if (qt->isIntegerType()) {
    return typeFac.getIntType();
  }

  if (qt->isFloatingType()) {
    return typeFac.getFloatType();
  }

  if (qt->isCharType()) {
    return typeFac.getCharType();
  }

  if (qt->isBooleanType()) {
    return typeFac.getBoolType();
  }

  if (qt->isVoidType()) {
    return typeFac.getVoidType();
  }

  return typeFac.getUserType(qt.getAsString());
}

libastfri::structures::BinaryOperators
AstfriClangVisitor::convertBinaryOperator(clang::BinaryOperator::Opcode op) {
  switch (op) {
  case clang::BinaryOperator::Opcode::BO_Add:
    return libastfri::structures::BinaryOperators::Add;
  case clang::BinaryOperator::Opcode::BO_Sub:
    return libastfri::structures::BinaryOperators::Subtract;
  case clang::BinaryOperator::Opcode::BO_Mul:
    return libastfri::structures::BinaryOperators::Multiply;
  case clang::BinaryOperator::Opcode::BO_Div:
    return libastfri::structures::BinaryOperators::Divide;
  case clang::BinaryOperator::Opcode::BO_Rem:
    return libastfri::structures::BinaryOperators::Modulo;
  case clang::BinaryOperator::Opcode::BO_LT:
    return libastfri::structures::BinaryOperators::Less;
  case clang::BinaryOperator::Opcode::BO_GT:
    return libastfri::structures::BinaryOperators::Greater;
  case clang::BinaryOperator::Opcode::BO_LE:
    return libastfri::structures::BinaryOperators::LessEqual;
  case clang::BinaryOperator::Opcode::BO_GE:
    return libastfri::structures::BinaryOperators::GreaterEqual;
  case clang::BinaryOperator::Opcode::BO_EQ:
    return libastfri::structures::BinaryOperators::Equal;
  case clang::BinaryOperator::Opcode::BO_NE:
    return libastfri::structures::BinaryOperators::NotEqual;
    //   case clang::BinaryOperator::Opcode::BO_And:
    //     return libastfri::structures::BinaryOperators::AND;
    //   case clang::BinaryOperator::Opcode::BO_Or:
    //     return libastfri::structures::BinaryOperators::OR;
  }

  throw std::runtime_error("Unknown binary operator");
}

libastfri::structures::UnaryOperators
AstfriClangVisitor::convertUnaryOperator(clang::UnaryOperator::Opcode op) {
  switch (op) {
  case clang::UnaryOperator::Opcode::UO_Minus:
    return libastfri::structures::UnaryOperators::Negative;
  case clang::UnaryOperator::Opcode::UO_Not:
    return libastfri::structures::UnaryOperators::Not;
  }

  throw std::runtime_error("Unknown unary operator");
}