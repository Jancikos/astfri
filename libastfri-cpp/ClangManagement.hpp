#pragma once

#include <libastfri/structures/Statement.hpp>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>
#include <libastfri-cpp/ClangVisitor.hpp>
#include <memory>

namespace libastfri::cpp
{
class ClangConsumer : public clang::ASTConsumer
{
public:
    clang::ASTContext* context;
    libastfri::structures::TranslationUnit* visitedTranslationUnit;

    ClangConsumer(
        clang::ASTContext& context,
        libastfri::structures::TranslationUnit& visitedTranslationUnit
    );
    void HandleTranslationUnit (clang::ASTContext& p_context);
};

class ClangTraverseAction : public clang::ASTFrontendAction
{
    using TUnit = libastfri::structures::TranslationUnit;
    TUnit* visitedTranslationUnit;

public:
    ClangTraverseAction(TUnit& visitedTranslationUnit);
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer (
        clang::CompilerInstance& compiler,
        llvm::StringRef
    );
};
} // namespace libastfri::cpp