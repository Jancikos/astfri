#include <libastfri-cpp/test.hpp>

void FindClassConsumer::HandleTranslationUnit(clang::ASTContext& p_context) {
   FindNamedClassVisitor visitor;

   visitor.TraverseDecl(p_context.getTranslationUnitDecl());

}

std::unique_ptr<clang::ASTConsumer> FindClassAction::CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef) {
    return std::make_unique<FindClassConsumer>(compiler.getASTContext());
}



void testExample() {
    auto &expressionFac = libastfri::factories::ExpressionFactory::getInstance();
    auto& literalFac = libastfri::factories::LiteralFactory::getInstance();

    auto binaryExpression = expressionFac.createBinaryExpression(
        libastfri::structures::BinaryOperators::Add,
        literalFac.getIntLiteral(1),
        literalFac.getIntLiteral(2)
    );
}