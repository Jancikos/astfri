#pragma once

#include <map>

#include <libastfri/structures/Expression.hpp>
#include <vector>

using namespace libastfri::structures;

namespace libastfri::factories {
    class BaseExpressionFactory
    {
        public:
            template <typename T>
            using UsedList = std::vector<T>;

            template<typename K, typename T>
            using UsedMap = std::map<K, T>;
    };

    class LiteralFactory : BaseExpressionFactory
    {
        public:
            static LiteralFactory& getInstance();

        private:
            UsedMap<int, IntLiteral> intLiterals;
            UsedMap<float, FloatLiteral> floatLiterals;
            UsedMap<char, CharLiteral> charLiterals;
            UsedMap<std::string, StringLiteral> stringLiterals;
            UsedMap<bool, BoolLiteral> boolLiterals;

            LiteralFactory();
        public:
            
            IntLiteral* getIntLiteral (int literal);
            FloatLiteral* getFloatLiteral (float literal);
            CharLiteral* getCharLiteral (char literal);
            StringLiteral* getStringLiteral (std::string literal);
            BoolLiteral* getBoolLiteral (bool literal);

            LiteralFactory(LiteralFactory const&) = delete;
            void operator=(LiteralFactory const&) = delete;
    };

    class ExpressionFactory : BaseExpressionFactory
    {
        public:
            static ExpressionFactory& getInstance();

        private:
            UsedList<UnaryExpression> unaryExpressions;
            UsedList<BinaryExpression> binaryExpressions;

            ExpressionFactory();
        public:
            UnaryExpression* createUnaryExpression (UnaryOperators op, Expression *operand);
            BinaryExpression* createBinaryExpression (BinaryOperators op, Expression *left, Expression *right);
            
            ExpressionFactory(ExpressionFactory const&) = delete;
            void operator=(ExpressionFactory const&) = delete;
    };

    // for VarRefExpression, FunctionCallExpression, ArrayRefExpression...
    class ReferenceFactory : BaseExpressionFactory
    {
        public:
            static ReferenceFactory& getInstance();

        private:
            ReferenceFactory();
        public:
            ReferenceFactory(ReferenceFactory const&) = delete;
            void operator=(ReferenceFactory const&) = delete;
    };
}

