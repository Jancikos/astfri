#pragma once

#include <vector>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Variable.hpp>

namespace libastfri::structures
{    
    // "riadok" v kode
    struct Statement
    {

    };

    struct CompoundStatement : Statement
    {
        std::vector<Statement*> statements;

        CompoundStatement (std::vector<Statement*> statements) : statements(std::move(statements)) {}
        CompoundStatement () {}
    };
    
    struct AssigmentStatement : Statement
    {
        Variable* left;
        Expression* right;

        AssigmentStatement (Variable* left, Expression* right) : left(left), right(right) {}
    };

    struct ReturnStatement : Statement
    {
        Expression* value;

        ReturnStatement (Expression* value) : value(value) {}
    };

    struct ConditionalStatement : Statement
    {
        Expression* condition;
        
        ConditionalStatement (Expression* condition) : condition(condition) {}
    };

    struct IfStatement : ConditionalStatement
    {
        CompoundStatement* thenBody;
        CompoundStatement* elseBody;

        IfStatement (Expression* condition, CompoundStatement* thenBody, CompoundStatement* elseBody = nullptr) : ConditionalStatement(condition), thenBody(thenBody), elseBody(elseBody) {}
    };

    // FucntionCall statement
}
