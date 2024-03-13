#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

class AstfriClangVisitor
    : public clang::RecursiveASTVisitor<AstfriClangVisitor> {
public:
  bool VisitFunctionDecl(clang::FunctionDecl *Declaration);
  bool VisitCompoundStmt(clang::CompoundStmt *Declaration);
};
