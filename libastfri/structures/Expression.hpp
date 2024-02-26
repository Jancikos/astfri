#pragma once

#include <string>

namespace libastfri::structures
{
    // vyraz
    struct Expression
    {

    };

    //// konstaty (literals) pouzivane v vyrazoch su vlastne tiez vyrazy
    struct Literal : Expression
    {
    };
    struct IntLiteral : Literal
    {
        int value;
    };
    struct FloatLiteral : Literal
    {
        float value;
    };
    struct CharLiteral : Literal
    {
        char value;
    };
    struct StringLiteral : Literal
    {
        std::string value;
    };
    struct BoolLiteral : Literal
    {
        bool value;
    };

    //// operatory pouzivane v vyrazoch
    enum class BinaryOperators
    {
        Add, Subtract, Multiply, Divide, Modulo
    };
    enum class UnaryOperators
    {
        Not, Negative,
        GetValue
    };

    //// vyrazy
    struct BinaryExpression : Expression 
    {
        Expression* left;
        BinaryOperators op;
        Expression* right;

        BinaryExpression (Expression* left, BinaryOperators op, Expression* right) : left(left), op(op), right(right) {} 
    };
    struct UnaryExpression : Expression
    {
        UnaryOperators op;
        Expression* arg;

        UnaryExpression (UnaryOperators op, Expression* arg) : op(op), arg(arg) {}
    };
    struct RefExpression : Expression
    {
    };
    // struct ParamRefExpression : RefExpression
    // {
    //     Parameter* variable;

    //     ParamRefExpression (Parameter* variable) : variable(variable) {}
    // };
}
