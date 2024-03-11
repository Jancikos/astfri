#include <libastfri-cpp/test.hpp>

void testExample() {
    auto &expressionFac = libastfri::factories::ExpressionFactory::getInstance();
    auto& literalFac = libastfri::factories::LiteralFactory::getInstance();

    auto binaryExpression = expressionFac.createBinaryExpression(
        libastfri::structures::BinaryOperators::Add,
        literalFac.getIntLiteral(1),
        literalFac.getIntLiteral(2)
    );
}