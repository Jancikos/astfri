#include <libastfri/structures/Expression.hpp>
#include <libastfri/utils/Helper.hpp>

namespace libastfri::utils
{

std::string Helper::convertBinaryOperator(structures::BinaryOperators op)
{
    switch (op)
    {
    case structures::BinaryOperators::Assign:
        return "=";
    case structures::BinaryOperators::Add:
        return "+";
    case structures::BinaryOperators::Subtract:
        return "-";
    case structures::BinaryOperators::Multiply:
        return "*";
    case structures::BinaryOperators::Divide:
        return "/";
    case structures::BinaryOperators::Modulo:
        return "%";
    case structures::BinaryOperators::Less:
        return "<";
    case structures::BinaryOperators::LessEqual:
        return "<=";
    case structures::BinaryOperators::Greater:
        return ">";
    case structures::BinaryOperators::GreaterEqual:
        return ">=";
    case structures::BinaryOperators::Equal:
        return "==";
    case structures::BinaryOperators::NotEqual:
        return "!=";
    default:
        return "";
    }
}

std::string Helper::convertUnaryOperator(structures::UnaryOperators op)
{
    switch (op)
    {
    case structures::UnaryOperators::Negative:
        return "-";
    case structures::UnaryOperators::Not:
        return "!";
    default:
        return "";
    }
}

} // namespace libastfri::utils
