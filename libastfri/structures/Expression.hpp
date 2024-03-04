#pragma once

#include <string>

namespace libastfri::structures
{
    struct Variable;

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

        IntLiteral (int value) : value(value) {}
    };
    struct FloatLiteral : Literal
    {
        float value;

        FloatLiteral (float value) : value(value) {}
    };
    struct CharLiteral : Literal
    {
        char value;

        CharLiteral (char value) : value(value) {}
    };
    struct StringLiteral : Literal
    {
        std::string value;

        StringLiteral (std::string value) : value(value) {}
    };
    struct BoolLiteral : Literal
    {
        bool value;

        BoolLiteral (bool value) : value(value) {}
    };
    // TODO - prehodnotit
    struct ConstLiteral : Literal
    {
        std::string name;

        ConstLiteral (std::string value) : name(value) {}
        ConstLiteral() : name("constant") {}
    };

    //// operatory pouzivane v vyrazoch
    enum class BinaryOperators
    {
        Add, Subtract, Multiply, Divide, Modulo,
        Equal, NotEqual, Less, LessEqual, Greater, GreaterEqual
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

    // refencia na premennu
    struct VarRefExpression : RefExpression
    {
        Variable* variable;

        VarRefExpression (Variable* variable) : variable(variable) {}
    };
}
