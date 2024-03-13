#pragma once

#include <vector>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Function.hpp>

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
    struct DeclarationAndAssigmentStatement : DeclarationStatement
    {
        Expression* exp;
    };

    struct AssigmentStatement : Statement
    {
        VariableDefintion* left;
        Expression* right;
    };

    struct ReturnStatement : Statement
    {
        Expression* value;
    };

    // FucntionCall statement
    struct FunctionCallStatement : Statement
    {
        FunctionDefinition* functionName;
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
