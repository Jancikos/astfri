#pragma once

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>

#include <map>
#include <string>
#include <vector>

namespace lsfs = libastfri::structures;

namespace libastfri::factories
{
template<typename T>
using UsedList = std::vector<T>;

template<typename K, typename T>
using UsedMap = std::map<K, T>;

class BaseExpressionFactory
{
};

class LiteralFactory : BaseExpressionFactory
{
public:
    static LiteralFactory& getInstance ();

private:
    template<typename K, typename T>
    T* getLiteralFromMap (K literal, UsedMap<K, T>& map);

    UsedMap<int, lsfs::IntLiteral> intLiterals;
    UsedMap<float, lsfs::FloatLiteral> floatLiterals;
    UsedMap<char, lsfs::CharLiteral> charLiterals;
    UsedMap<std::string, lsfs::StringLiteral> stringLiterals;
    UsedMap<bool, lsfs::BoolLiteral> boolLiterals;

    LiteralFactory()  = default;
    ~LiteralFactory() = default;

public:
    lsfs::IntLiteral* getIntLiteral (int literal);
    lsfs::FloatLiteral* getFloatLiteral (float literal);
    lsfs::CharLiteral* getCharLiteral (char literal);
    lsfs::StringLiteral* getStringLiteral (std::string literal);
    lsfs::BoolLiteral* getBoolLiteral (bool literal);

    LiteralFactory(LiteralFactory const&)  = delete;
    void operator= (LiteralFactory const&) = delete;
};

class ExpressionFactory : BaseExpressionFactory
{
public:
    static ExpressionFactory& getInstance ();

private:
    UsedList<lsfs::Expression*> expressions;

    ExpressionFactory() = default;
    ~ExpressionFactory();

public:
    lsfs::UnaryExpression* createUnaryExpression (
        lsfs::UnaryOperators op,
        lsfs::Expression* operand
    );
    lsfs::BinaryExpression* createBinaryExpression (
        lsfs::BinaryOperators op,
        lsfs::Expression* left,
        lsfs::Expression* right
    );

    lsfs::UnknownExpression* createUnknownExpression (std::string message);

    ExpressionFactory(ExpressionFactory const&) = delete;
    void operator= (ExpressionFactory const&)   = delete;
};

// for VarRefExpression, FunctionCallExpression, ArrayRefExpression...
class ReferenceFactory : BaseExpressionFactory
{
public:
    static ReferenceFactory& getInstance ();

private:
    // FUTURE - vyriesit recyklaciu pomocou unikatnej kombinacie nazvu a typu
    UsedList<lsfs::RefExpression*> refExpressions;

    ReferenceFactory() = default;
    ~ReferenceFactory();

public:
    lsfs::VarRefExpression* createVarRefExpression (
        lsfs::VariableDefintion* variable
    );
    lsfs::ParamRefExpression* createParamRefExpression (
        lsfs::ParameterDefinition* variable
    );
    lsfs::FunctionCallExpression* createFunctionCallExpression (
        std::string functionName,
        std::vector<lsfs::Expression*> arguments
    );

    ReferenceFactory(ReferenceFactory const&) = delete;
    void operator= (ReferenceFactory const&)  = delete;
};
} // namespace libastfri::factories
