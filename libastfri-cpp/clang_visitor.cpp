#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include "iostream"
#include "libastfri/factories/FunctionFactory.hpp"
#include "libastfri/structures/Expression.hpp"
#include "libastfri/structures/Statement.hpp"
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

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
      qualTypeToType(Declaration->getReturnType());

  // params
  std::vector<libastfri::structures::ParameterDefinition *> params;
  for (auto param : Declaration->parameters()) {
    param->dump();

    libastfri::structures::Expression *defValue = nullptr;
    if (param->hasDefaultArg()) {
      // TODO - doimplementovat ked budem vediet spracovat expressions
      // defValue = literalFac.createLiteral(param->getDefaultArg());
      std::cout << "has default arg" << std::endl;
    }

    params.push_back(funFac.createParameter(
        param->getNameAsString(), qualTypeToType(param->getType()), defValue));
  }

  // body
  libastfri::structures::CompoundStatement *body =
      statementFac.createCompoundStatement({});
  VisitCompoundStmt(static_cast<clang::CompoundStmt *>(Declaration->getBody()),
                    body);

  // Declaration->getParamDecl
  // Declaration->getBody()

  // myFunc.body = this->VisitrCompoundStmt(Declaration->getBody());

  // The return value indicates whether we want the visitation to proceed.
  // Return false to stop the traversal of the AST.
  return false;
}

// TODO - preriesit nejakym spossobm ako dostat navraty typ z funkcie (atribut
// visitoru, ?? out parameter)
bool AstfriClangVisitor::VisitCompoundStmt(
    clang::CompoundStmt *Declaration,
    libastfri::structures::CompoundStatement *outCompoundStatement) {
  if (outCompoundStatement == nullptr) {
    return false;
  }

  // For debugging, dumping the AST nodes will show which nodes are already
  // being visited.
  // Declaration->dump();

  auto &statementFac = libastfri::factories::StatementFactory::getInstance();

  for (auto stmt : Declaration->body()) {
    std::cout << std::endl << "stmt" << std::endl;
    stmt->dump();
    // TODO - pridat podporu pre vsetky statementy


    if (auto expr = clang::dyn_cast<clang::Expr>(stmt)) {
      libastfri::structures::Statement *outStatement = nullptr;
      VisitS(expr, outStatement);
      outCompoundStatement->statements.push_back(outStatement);
    }
  }

  return false;
}

bool AstfriClangVisitor::VisitStmt(
    clang::Stmt *Declaration,
    libastfri::structures::Statement *outCompoundStatement) {
  return false;
}


bool AstfriClangVisitor::VisitExpr(
    clang::Expr *Declaration,
    libastfri::structures::Statement *outCompoundStatement) {
  return false;
}

Type *AstfriClangVisitor::qualTypeToType(clang::QualType qt) {
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