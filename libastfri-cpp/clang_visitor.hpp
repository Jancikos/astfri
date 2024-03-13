#pragma once

#include "libastfri/structures/Expression.hpp"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <libastfri/structures/Type.hpp>
#include <libastfri/structures/Statement.hpp>

class AstfriClangVisitor
    : public clang::RecursiveASTVisitor<AstfriClangVisitor> {
public:
  bool VisitFunctionDecl(clang::FunctionDecl *Declaration);
  bool VisitCompoundStmt(clang::CompoundStmt *Declaration, libastfri::structures::CompoundStatement *outCompoundStatement=nullptr);

  bool VisitStmt(clang::Stmt *Declaration, libastfri::structures::Statement *outStatement=nullptr);
  bool VisitExpr(clang::Expr *Declaration, libastfri::structures::Expression *outExpression=nullptr);

private:
    libastfri::structures::Type* qualTypeToType(clang::QualType qt);
};
