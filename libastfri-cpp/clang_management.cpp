#include <libastfri-cpp/clang_management.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>

AstfriClangConsumer::AstfriClangConsumer(clang::ASTContext &context)
    : context(&context) {}

void AstfriClangConsumer::HandleTranslationUnit(clang::ASTContext &p_context) {
  AstfriClangVisitor visitor;

  visitor.TraverseDecl(p_context.getTranslationUnitDecl());
}

std::unique_ptr<clang::ASTConsumer>
AstfriClangTraverseAction::CreateASTConsumer(clang::CompilerInstance &compiler,
                                   llvm::StringRef) {
  return std::make_unique<AstfriClangConsumer>(compiler.getASTContext());
}
