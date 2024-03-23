#include <libastfri/factories/ExpressionFactory.hpp>

#include <libastfri/utils/Helper.hpp>

namespace lsfu = libastfri::utils;

namespace libastfri::factories {

//// LiteralFactory
LiteralFactory &LiteralFactory::getInstance() {
    static LiteralFactory instance;

    return instance;
}

template <typename K, typename T>
T *LiteralFactory::getLiteralFromMap(K key, UsedMap<K, T> &map) {
    return &lsfu::Helper::getValueFromMap(key, map, [](auto &p_map, K p_key) {
        return p_map.emplace(p_key, T{{{}}, p_key});
    });
}

lsfs::IntLiteral *LiteralFactory::getIntLiteral(int literal) {
    return getLiteralFromMap(literal, this->intLiterals);
}

lsfs::FloatLiteral *LiteralFactory::getFloatLiteral(float literal) {
    return getLiteralFromMap(literal, this->floatLiterals);
}

lsfs::CharLiteral *LiteralFactory::getCharLiteral(char literal) {
    return getLiteralFromMap(literal, this->charLiterals);
}

lsfs::StringLiteral *LiteralFactory::getStringLiteral(std::string literal) {
    return getLiteralFromMap(literal, this->stringLiterals);
}

lsfs::BoolLiteral *LiteralFactory::getBoolLiteral(bool literal) {
    return getLiteralFromMap(literal, this->boolLiterals);
}

lsfs::ConstLiteral *LiteralFactory::getConstLiteral(std::string literal) {
    return getLiteralFromMap(literal, this->constLiterals);
}

//// ExpressionFactory
ExpressionFactory &ExpressionFactory::getInstance() {
    static ExpressionFactory instance;

    return instance;
}

ExpressionFactory::~ExpressionFactory() {
    for (auto expr : this->expressions) {
        delete expr;
    }
    expressions.clear();
}

lsfs::UnaryExpression *ExpressionFactory::createUnaryExpression(lsfs::UnaryOperators op,
                                                          lsfs::Expression *operand) {
    auto* expr = new lsfs::UnaryExpression{{}, op, operand};
    this->expressions.emplace_back(expr);

    return expr;
}

lsfs::BinaryExpression *ExpressionFactory::createBinaryExpression(lsfs::BinaryOperators op,
                                                            lsfs::Expression *left,
                                                            lsfs::Expression *right) {
    auto* expr = new lsfs::BinaryExpression{{}, left, op, right};
    this->expressions.emplace_back(expr);

    return expr;
}

lsfs::UnknownExpression *ExpressionFactory::createUnknownExpression(
    std::string message) {
    auto* expr = new lsfs::UnknownExpression{{}, message};

    return expr;
}

//// ReferenceFactory
ReferenceFactory &ReferenceFactory::getInstance() {
    static ReferenceFactory instance;

    return instance;
}

ReferenceFactory::~ReferenceFactory() {
    for (auto expr : this->refExpressions) {
        delete expr;
    }
    refExpressions.clear();
}

lsfs::VarRefExpression *
ReferenceFactory::createVarRefExpression(lsfs::VariableDefintion *variable) {
    lsfs::VarRefExpression *expr = new lsfs::VarRefExpression{{}, variable};
    this->refExpressions.push_back(expr);

    return expr;
}

lsfs::ParamRefExpression *
ReferenceFactory::createParamRefExpression(lsfs::ParameterDefinition *parameter) {
    lsfs::ParamRefExpression *expr = new lsfs::ParamRefExpression{{}, parameter};
    this->refExpressions.push_back(expr);

    return expr;
}

lsfs::FunctionCallExpression *ReferenceFactory::createFunctionCallExpression(
    std::string functionName, std::vector<lsfs::Expression *> arguments) {
    lsfs::FunctionCallExpression *expr =
        new lsfs::FunctionCallExpression{{}, functionName, std::move(arguments)};
    this->refExpressions.push_back(expr);

    return expr;
}

} // namespace libastfri::factories
