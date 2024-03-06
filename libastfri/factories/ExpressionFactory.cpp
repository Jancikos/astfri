#include <libastfri/factories/ExpressionFactory.hpp>

#include <libastfri/utils/Helper.hpp>

using namespace libastfri::utils;

namespace libastfri::factories {

    //// LiteralFactory
    LiteralFactory& LiteralFactory::getInstance()
    {
        static LiteralFactory instance;

        return instance;
    }

    template<typename K, typename T>
    T* LiteralFactory::getLiteralFromMap (K key, UsedMap<K, T> &map)
    {
        return &Helper::getValueFromMap(
            key,
             map, 
            [] (auto& p_map, K p_key) {
                return p_map.emplace(p_key, T{{{}}, p_key});
            }
        );
    }

    IntLiteral* LiteralFactory::getIntLiteral (int literal)
    {
        return getLiteralFromMap(literal, this->intLiterals);
    }

    FloatLiteral* LiteralFactory::getFloatLiteral (float literal)
    {
        return getLiteralFromMap(literal, this->floatLiterals);
    }

    CharLiteral* LiteralFactory::getCharLiteral (char literal)
    {
        return getLiteralFromMap(literal, this->charLiterals);
    }

    StringLiteral* LiteralFactory::getStringLiteral (std::string literal)
    {
        return getLiteralFromMap(literal, this->stringLiterals);
    }

    BoolLiteral* LiteralFactory::getBoolLiteral (bool literal)
    {
        return getLiteralFromMap(literal, this->boolLiterals);
    }

    ConstLiteral* LiteralFactory::getConstLiteral (std::string literal)
    {
        return getLiteralFromMap(literal, this->constLiterals);
    }

    //// ExpressionFactory
    ExpressionFactory::ExpressionFactory ()
    {
        this->unaryExpressions = UsedList<UnaryExpression>();
        this->binaryExpressions = UsedList<BinaryExpression>();
    }

    ExpressionFactory& ExpressionFactory::getInstance()
    {
        static ExpressionFactory instance;

        return instance;
    }

    UnaryExpression* ExpressionFactory::createUnaryExpression (UnaryOperators op, Expression *operand)
    {
        UnaryExpression expr{{}, op, operand};
        this->unaryExpressions.push_back(expr);

        return &this->unaryExpressions.back();
    }

    BinaryExpression* ExpressionFactory::createBinaryExpression (BinaryOperators op, Expression *left, Expression *right)
    {
        BinaryExpression expr {{}, left, op, right};
        this->binaryExpressions.push_back(expr);

        return &this->binaryExpressions.back();
    }

    //// ReferenceFactory
    ReferenceFactory::ReferenceFactory ()
    {

    }

    ReferenceFactory::~ReferenceFactory ()
    {
        for (auto expr : this->refExpressions)
        {
            delete expr;
        }
    }

    ReferenceFactory& ReferenceFactory::getInstance()
    {
        static ReferenceFactory instance;

        return instance;
    }

    VarRefExpression* ReferenceFactory::createVarRefExpression (VariableDefintion* variable)
    {
        VarRefExpression* expr = new VarRefExpression {{}, variable};
        this->refExpressions.push_back(expr);

        return expr;
    }

    ParamRefExpression* ReferenceFactory::createParamRefExpression (ParameterDefinition* parameter)
    {
        ParamRefExpression* expr = new ParamRefExpression {{}, parameter};
        this->refExpressions.push_back(expr);

        return expr;
    }

    FunctionCallExpression* ReferenceFactory::createFunctionCallExpression (FunctionDefinition* function, std::vector<Expression*> arguments)
    {
        FunctionCallExpression* expr = new FunctionCallExpression {{}, function, std::move(arguments)};
        this->refExpressions.push_back(expr);

        return expr;
    }
    
}

