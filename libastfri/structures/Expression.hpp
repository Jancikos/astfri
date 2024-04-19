#pragma once

#include <libastfri/structures/Declaration.hpp>

#include <libastfri/utils/OutputVisitor.hpp>

#include <string>

namespace libastfri::structures
{
struct VariableDefintion;
struct ParameterDefinition;

// vyraz
struct Expression : virtual utils::IOutputVisitable
{
};

//// konstaty (literals) pouzivane v vyrazoch su vlastne tiez vyrazy
template<typename T>
struct Literal : Expression
{
    T value;

    Literal(T value) : value(value)
    {
    }
};

struct IntLiteral : Literal<int>, utils::OutputVisitable<IntLiteral>
{
    IntLiteral(int value);
};

struct FloatLiteral : Literal<float>, utils::OutputVisitable<FloatLiteral>
{
    FloatLiteral(float value);
};

struct CharLiteral : Literal<char>, utils::OutputVisitable<CharLiteral>
{
    CharLiteral(char value);
};

struct StringLiteral :
    Literal<std::string>,
    utils::OutputVisitable<StringLiteral>
{
    StringLiteral(std::string value);
};

struct BoolLiteral : Literal<bool>, utils::OutputVisitable<BoolLiteral>
{
    BoolLiteral(bool value);
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
