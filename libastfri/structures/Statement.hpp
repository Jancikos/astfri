#pragma once

#include <vector>

#include <libastfri/structures/Expression.hpp>

namespace libastfri::structures
{    
    // "riadok" v kode
    struct Statement
    {
    };

    struct CompoundStatement : Statement
    {
        std::vector<Statement*> statements;
    };
    
    struct DeclarationStatement : Statement
    {
        VariableDefintion* variable;
    };
    struct AssigmentStatement : Statement
    {
        VariableDefintion* left;
        Expression* right;
    };

    struct DeclarationAndAssigmentStatement : AssigmentStatement
    {
    };

    struct ReturnStatement : Statement
    {
        Expression* value;
    };

    // FucntionCall statement
    struct FunctionCallStatement : Statement
    {
        std::string functionName;
        std::vector<Expression*> arguments;
    };

    // Conditional statement
    struct ConditionalStatement : Statement
    {
        Expression* condition;
    };

    struct IfStatement : ConditionalStatement
    {
        CompoundStatement* thenBody;
        CompoundStatement* elseBody;
    };

    // Loop statement
    struct LoopStatement : Statement
    {
        Expression* condition;
        CompoundStatement* body;
    };
    struct WhileLoopStatement : LoopStatement
    {
    };
    struct DoWhileLoopStatement : LoopStatement
    {
    };
    struct ForLoopStatement : LoopStatement
    {
        AssigmentStatement* init;
        AssigmentStatement* step;
    };
}
