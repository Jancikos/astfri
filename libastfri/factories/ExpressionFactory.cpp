#include <libastfri/factories/ExpressionFactory.hpp>

#include <libastfri/utils/Helper.hpp>
using namespace libastfri::utils;

namespace libastfri::factories {

    //// LiteralFactory
    LiteralFactory& LiteralFactory::getInstance()
    {
        static LiteralFactory instance;

        return instance;
    }

    IntLiteral* LiteralFactory::getIntLiteral (int literal)
    {
        return &Helper::getValueFromMap(literal, this->intLiterals);
    }

    FloatLiteral* LiteralFactory::getFloatLiteral (float literal)
    {
        return &Helper::getValueFromMap(literal, this->floatLiterals);
    }

    CharLiteral* LiteralFactory::getCharLiteral (char literal)
    {
        return &Helper::getValueFromMap(literal, this->charLiterals);
    }

    StringLiteral* LiteralFactory::getStringLiteral (std::string literal)
    {
        return &Helper::getValueFromMap(literal, this->stringLiterals);
    }

    BoolLiteral* LiteralFactory::getBoolLiteral (bool literal)
    {
        return &Helper::getValueFromMap(literal, this->boolLiterals);
    }

    //// ExpressionFactory
    ExpressionFactory::ExpressionFactory ()
    {
        this->unaryExpressions = UsedList<UnaryExpression>();
        this->binaryExpressions = UsedList<BinaryExpression>();
    }

    ExpressionFactory& ExpressionFactory::getInstance()
    {
        static ExpressionFactory instance;

        return instance;
    }

    UnaryExpression* ExpressionFactory::createUnaryExpression (UnaryOperators op, Expression *operand)
    {
        UnaryExpression expr = UnaryExpression(op, operand);
        this->unaryExpressions.push_back(expr);

        return &this->unaryExpressions.back();
    }

    BinaryExpression* ExpressionFactory::createBinaryExpression (BinaryOperators op, Expression *left, Expression *right)
    {
        BinaryExpression expr = BinaryExpression(left, op, right);
        this->binaryExpressions.push_back(expr);

        return &this->binaryExpressions.back();
    }

    //// ReferenceFactory
    ReferenceFactory::ReferenceFactory ()
    {

    }

    ReferenceFactory& ReferenceFactory::getInstance()
    {
        static ReferenceFactory instance;

        return instance;
    }
}

