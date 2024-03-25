#include <libastfri/structures/Expression.hpp>

namespace libastfri::structures
{

IntLiteral::IntLiteral(int value) : value(value)
{
}

FloatLiteral::FloatLiteral(float value) : value(value)
{
}

CharLiteral::CharLiteral(char value) : value(value)
{
}

StringLiteral::StringLiteral(std::string value) : value(std::move(value))
{
}

BoolLiteral::BoolLiteral(bool value) : value(value)
{
}

ConstLiteral::ConstLiteral(std::string name) : name(std::move(name))
{
}

BinaryExpression::BinaryExpression(
    Expression* left,
    BinaryOperators op,
    Expression* right
) :
    left(left),
    op(op),
    right(right)
{
}

UnaryExpression::UnaryExpression(UnaryOperators op, Expression* arg) :
    op(op),
    arg(arg)
{
}

ParamRefExpression::ParamRefExpression(ParameterDefinition* parameter) :
    parameter(parameter)
{
}

VarRefExpression::VarRefExpression(VariableDefintion* variable) :
    variable(variable)
{
}

FunctionCallExpression::FunctionCallExpression(
    std::string functionName,
    std::vector<Expression*> arguments
) :
    functionName(std::move(functionName)),
    arguments(std::move(arguments))
{
}

UnknownExpression::UnknownExpression(std::string message) :
    message(std::move(message))
{
}

} // namespace libastfri::structures
