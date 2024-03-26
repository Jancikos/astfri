#pragma once

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/utils/OutputVisitor.hpp>
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

struct IntLiteral : Literal, utils::OutputVisitable<IntLiteral>
{
    int value;

    IntLiteral(int value);
};

struct FloatLiteral : Literal, utils::OutputVisitable<FloatLiteral>
{
    float value;

    FloatLiteral(float value);
};

struct CharLiteral : Literal, utils::OutputVisitable<CharLiteral>
{
    char value;

    CharLiteral(char value);
};

struct StringLiteral : Literal, utils::OutputVisitable<StringLiteral>
{
    std::string value;

    StringLiteral(std::string value);
};

struct BoolLiteral : Literal, utils::OutputVisitable<BoolLiteral>
{
    bool value;

    BoolLiteral(bool value);
};

// TODO - prehodnotit
struct ConstLiteral : Literal, utils::OutputVisitable<ConstLiteral>
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
struct BinaryExpression : Expression, utils::OutputVisitable<BinaryExpression>
{
    Expression* left;
    BinaryOperators op;
    Expression* right;

    BinaryExpression(Expression* left, BinaryOperators op, Expression* right);
};

struct UnaryExpression : Expression, utils::OutputVisitable<UnaryExpression>
{
    UnaryOperators op;
    Expression* arg;

    UnaryExpression(UnaryOperators op, Expression* arg);
};

//// referencie na premenne
struct RefExpression : Expression
{
};

struct ParamRefExpression :
    RefExpression,
    utils::OutputVisitable<ParamRefExpression>
{
    ParameterDefinition* parameter;

    ParamRefExpression(ParameterDefinition* parameter);
};

struct VarRefExpression :
    RefExpression,
    utils::OutputVisitable<VarRefExpression>
{
    VariableDefintion* variable;

    VarRefExpression(VariableDefintion* variable);
};

// volanie funkcie
struct FunctionCallExpression :
    RefExpression,
    utils::OutputVisitable<FunctionCallExpression>
{
    // FunctionDefinition* function;
    std::string functionName;
    std::vector<Expression*> arguments;

    FunctionCallExpression(
        std::string functionName,
        std::vector<Expression*> arguments = {}
    );
};

struct UnknownExpression : Expression, utils::OutputVisitable<UnknownExpression>
{
    std::string message;

    UnknownExpression(std::string message);
};

} // namespace libastfri::structures
