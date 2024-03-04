#pragma once

#include <string>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>
#include <libastfri/utils/Helper.hpp>

using namespace libastfri::structures;
using namespace libastfri::utils;

namespace libastfri::factories {
    class StatementFactory
    {
        public:
            static StatementFactory& getInstance();

        private:
            UsedList<CompoundStatement> compoundStatements;
            UsedList<DeclarationStatement> declarationStatements;
            UsedList<AssigmentStatement> assigmentStatements;
            UsedList<DeclarationAndAssigmentStatement> declarationAndAssigmentStatements;

            UsedList<ReturnStatement> returnStatements;
            UsedList<FunctionCallStatement> functionCallStatements;

            UsedList<IfStatement> ifStatements;

            UsedList<WhileLoopStatement> whileLoopStatements;
            UsedList<DoWhileLoopStatement> doWhileLoopStatements;
            UsedList<ForLoopStatement> forLoopStatements;

            StatementFactory () {};
        public:
            StatementFactory(StatementFactory const&) = delete;
            void operator=(StatementFactory const&) = delete;

            CompoundStatement* createCompoundStatement (std::vector<Statement*> statements);
            DeclarationStatement* createDeclarationStatement (Variable* variable);
            AssigmentStatement* createAssigmentStatement (Variable* left, Expression* right);
            DeclarationAndAssigmentStatement* createDeclarationAndAssigmentStatement (Variable* left, Expression* right);
            ReturnStatement* createReturnStatement (Expression* value);

            FunctionCallStatement* createFunctionCallStatement (std::string functionName, std::vector<Expression*> arguments);

            IfStatement* createConditionalStatement (Expression* condition, CompoundStatement* ifTrue, CompoundStatement* ifFalse);
            
            WhileLoopStatement* createWhileLoopStatement (Expression* condition, CompoundStatement* body);
            DoWhileLoopStatement* createDoWhileLoopStatement (Expression* condition, CompoundStatement* body);
            ForLoopStatement* createForLoopStatement (AssigmentStatement* init, Expression* condition, AssigmentStatement* step, CompoundStatement* body);
    };
}

