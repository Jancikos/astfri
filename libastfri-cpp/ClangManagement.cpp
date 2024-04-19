#include <libastfri/factories/ExpressionFactory.hpp>

#include <libastfri-cpp/ClangManagement.hpp>

namespace libastfri::cpp
{
ClangConsumer::ClangConsumer(
    clang::ASTContext& context,
    libastfri::structures::TranslationUnit& visitedTranslationUnit
) :
    context(&context),
    visitedTranslationUnit(&visitedTranslationUnit)
{
}

void ClangConsumer::HandleTranslationUnit(clang::ASTContext& p_context)
{
    ClangVisitor visitor(*visitedTranslationUnit);

    visitor.TraverseDecl(p_context.getTranslationUnitDecl());
}

ClangTraverseAction::ClangTraverseAction(
    libastfri::structures::TranslationUnit& visitedTranslationUnit
) :
    visitedTranslationUnit(&visitedTranslationUnit)
{
}

std::unique_ptr<clang::ASTConsumer> ClangTraverseAction::CreateASTConsumer(
    clang::CompilerInstance& compiler,
    llvm::StringRef
)
{
    return std::make_unique<ClangConsumer>(
        compiler.getASTContext(),
        *visitedTranslationUnit
    );
}
} // namespace libastfri::cpp