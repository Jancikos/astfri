#pragma once

#include "libastfri/structures/Expression.hpp"
#include "libastfri/structures/Function.hpp"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

class AstfriClangVisitor
    : public clang::RecursiveASTVisitor<AstfriClangVisitor> {
public:
  bool VisitFunctionDecl(clang::FunctionDecl *Declaration);
  bool VisitCompoundStmt(clang::CompoundStmt *Declaration);

  bool VisitStmt(clang::Stmt *Declaration);

  bool VisitExpr(clang::Expr *Declaration);
  bool VisitIntegerLiteral(clang::IntegerLiteral *Declaration);

  bool VisitParmVarDecl(clang::ParmVarDecl *Declaration);
  bool VisitDeclRefExpr(clang::DeclRefExpr *Declaration);

private:
  libastfri::structures::Statement *visitedStatement;
  libastfri::structures::Expression *visitedExpression;
  libastfri::structures::BaseVariableDefintion *visitedVariable;
  libastfri::structures::FunctionDefinition *visitedFunction;

  libastfri::structures::Type *convertType(clang::QualType qt);
  libastfri::structures::BinaryOperators
  convertBinaryOperator(clang::BinaryOperator::Opcode op);
  libastfri::structures::UnaryOperators
  convertUnaryOperator(clang::UnaryOperator::Opcode op);
};
