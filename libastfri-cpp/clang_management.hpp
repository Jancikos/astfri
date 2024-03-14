#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <libastfri-cpp/clang_visitor.hpp>
#include <memory>

class AstfriClangConsumer : public clang::ASTConsumer {
public:
  clang::ASTContext *context;
  libastfri::structures::TranslationUnitStatement *visitedTranslationUnit;

  AstfriClangConsumer(clang::ASTContext &context);
  void HandleTranslationUnit(clang::ASTContext &p_context);
};

class AstfriClangTraverseAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef);
};
