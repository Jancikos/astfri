#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <libastfri-cpp/clang_visitor.hpp>
#include <libastfri/structures/Statement.hpp>
#include <memory>

namespace libastfri::cpp {
class AstfriClangConsumer : public clang::ASTConsumer {
public:
  clang::ASTContext *context;
  libastfri::structures::TranslationUnitStatement *visitedTranslationUnit;

  AstfriClangConsumer(
      clang::ASTContext &context,
      libastfri::structures::TranslationUnitStatement &visitedTranslationUnit);
  void HandleTranslationUnit(clang::ASTContext &p_context);
};

class AstfriClangTraverseAction : public clang::ASTFrontendAction {
  using TUnit = libastfri::structures::TranslationUnitStatement;
  TUnit *visitedTranslationUnit;

public:
  AstfriClangTraverseAction(TUnit &visitedTranslationUnit);
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &compiler, llvm::StringRef);
};
} // namespace libastfri::cpp