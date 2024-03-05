#pragma once

#include "libastfri/structures/Function.hpp"
#include <string>

namespace libastfri::structures
{
    struct VariableDefintion;
    struct ParameterDefinition;

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
    // TODO - prehodnotit
    struct ConstLiteral : Literal
    {
        std::string name;
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
    };
    struct UnaryExpression : Expression
    {
        UnaryOperators op;
        Expression* arg;
    };

    //// referencie na premenne
    struct RefExpression : Expression
    {
    };
    struct ParamRefExpression : RefExpression
    {
        ParameterDefinition* parameter;
    };
    struct VarRefExpression : RefExpression
    {
        VariableDefintion* variable;
    };

    //// volanie funkcie
    struct FunctionCallExpression : Expression
    {
        FunctionDefinition* function;
    };
}
