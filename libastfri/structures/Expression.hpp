#pragma once

#include <libastfri/structures/Declaration.hpp>
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

    IntLiteral(int value);
};

struct FloatLiteral : Literal
{
    float value;

    FloatLiteral(float value);
};

struct CharLiteral : Literal
{
    char value;

    CharLiteral(char value);
};

struct StringLiteral : Literal
{
    std::string value;

    StringLiteral(std::string value);
};

struct BoolLiteral : Literal
{
    bool value;

    BoolLiteral(bool value);
};

// TODO - prehodnotit
struct ConstLiteral : Literal
{
    std::string name;

    ConstLiteral(std::string name);
};

//// operatory pouzivane v vyrazoch
enum class BinaryOperators
{
    Assign,
    Add,
    Subtract,
    Multiply,
    Divide,
    Modulo,
    Equal,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual
};
enum class UnaryOperators
{
    Not,
    Negative,
    GetValue
};

//// vyrazy
struct BinaryExpression : Expression
{
    Expression* left;
    BinaryOperators op;
    Expression* right;

    BinaryExpression(Expression* left, BinaryOperators op, Expression* right);
};

struct UnaryExpression : Expression
{
    UnaryOperators op;
    Expression* arg;

    UnaryExpression(UnaryOperators op, Expression* arg);
};

//// referencie na premenne
struct RefExpression : Expression
{
};

struct ParamRefExpression : RefExpression
{
    ParameterDefinition* parameter;

    ParamRefExpression(ParameterDefinition* parameter);
};

struct VarRefExpression : RefExpression
{
    VariableDefintion* variable;

    VarRefExpression(VariableDefintion* variable);
};

// volanie funkcie
struct FunctionCallExpression : RefExpression
{
    // FunctionDefinition* function;
    std::string functionName;
    std::vector<Expression*> arguments;

    FunctionCallExpression(
        std::string functionName,
        std::vector<Expression*> arguments = {}
    );
};

struct UnknownExpression : Expression
{
    std::string message;

    UnknownExpression(std::string message);
};

} // namespace libastfri::structures
