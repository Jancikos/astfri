#pragma once

#include <map>
#include <string>
#include <vector>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Declaration.hpp>

using namespace libastfri::structures;

namespace libastfri::factories {
template <typename T> using UsedList = std::vector<T>;

template <typename K, typename T> using UsedMap = std::map<K, T>;

class BaseExpressionFactory {};

class LiteralFactory : BaseExpressionFactory {
  public:
    static LiteralFactory &getInstance();

  private:
    template <typename K, typename T>
    T *getLiteralFromMap(K literal, UsedMap<K, T> &map);

    UsedMap<int, IntLiteral> intLiterals;
    UsedMap<float, FloatLiteral> floatLiterals;
    UsedMap<char, CharLiteral> charLiterals;
    UsedMap<std::string, StringLiteral> stringLiterals;
    UsedMap<bool, BoolLiteral> boolLiterals;
    UsedMap<std::string, ConstLiteral> constLiterals;

    LiteralFactory() {};

  public:
    IntLiteral *getIntLiteral(int literal);
    FloatLiteral *getFloatLiteral(float literal);
    CharLiteral *getCharLiteral(char literal);
    StringLiteral *getStringLiteral(std::string literal);
    BoolLiteral *getBoolLiteral(bool literal);
    ConstLiteral *getConstLiteral(std::string literal);

    LiteralFactory(LiteralFactory const &) = delete;
    void operator=(LiteralFactory const &) = delete;
};

class ExpressionFactory : BaseExpressionFactory {
  public:
    static ExpressionFactory &getInstance();

  private:
    UsedList<Expression*> expressions;

    ExpressionFactory();

  public:
    UnaryExpression *createUnaryExpression(UnaryOperators op,
                                           Expression *operand);
    BinaryExpression *createBinaryExpression(BinaryOperators op,
                                             Expression *left,
                                             Expression *right);

    UnknownExpression *createUnknownExpression(std::string message);

    ExpressionFactory(ExpressionFactory const &) = delete;
    void operator=(ExpressionFactory const &) = delete;
};

// for VarRefExpression, FunctionCallExpression, ArrayRefExpression...
class ReferenceFactory : BaseExpressionFactory {
  public:
    static ReferenceFactory &getInstance();

  private:
    // TODO - prekonzultovat recyklaciu
    UsedList<RefExpression *> refExpressions;

    ReferenceFactory();
    ~ReferenceFactory();

  public:
    VarRefExpression *createVarRefExpression(VariableDefintion *variable);
    ParamRefExpression *createParamRefExpression(ParameterDefinition *variable);
    FunctionCallExpression *
    createFunctionCallExpression(std::string functionName,
                                 std::vector<Expression *> arguments);

    ReferenceFactory(ReferenceFactory const &) = delete;
    void operator=(ReferenceFactory const &) = delete;
};
} // namespace libastfri::factories
