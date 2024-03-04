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
    
    struct DeclarationStatement : Statement
    {
        Variable* variable;

        DeclarationStatement (Variable* variable) : variable(variable) {}
    };
    struct AssigmentStatement : Statement
    {
        Variable* left;
        Expression* right;

        AssigmentStatement (Variable* left, Expression* right) : left(left), right(right) {}
    };

    struct DeclarationAndAssigmentStatement : AssigmentStatement
    {
        DeclarationAndAssigmentStatement (Variable* left, Expression* right) : AssigmentStatement(left, right) {}
    };

    struct ReturnStatement : Statement
    {
        Expression* value;

        ReturnStatement (Expression* value) : value(value) {}
    };

    // FucntionCall statement
    struct FunctionCallStatement : Statement
    {
        std::string functionName;
        std::vector<Expression*> arguments;

        FunctionCallStatement (std::string functionName, std::vector<Expression*> arguments) : functionName(functionName), arguments(std::move(arguments)) {}
    };

    // TODO - presunute z Expression.hpp kvoli cyklickej zavislosti
    struct FunctionCallExpression : Expression
    {
        FunctionCallStatement* call;

        FunctionCallExpression (FunctionCallStatement* call) : call(call) {}
    };

    // Conditional statement
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

    // Loop statement
    struct LoopStatement : Statement
    {
        Expression* condition;
        CompoundStatement* body;

        LoopStatement (Expression* condition, CompoundStatement* body) : condition(condition), body(body) {}
    };
    struct WhileLoopStatement : LoopStatement
    {
        WhileLoopStatement (Expression* condition, CompoundStatement* body) : LoopStatement(condition, body) {}
    };
    struct DoWhileLoopStatement : LoopStatement
    {
        DoWhileLoopStatement (Expression* condition, CompoundStatement* body) : LoopStatement(condition, body) {}
    };
    struct ForLoopStatement : LoopStatement
    {
        AssigmentStatement* init;
        AssigmentStatement* step;

        ForLoopStatement (AssigmentStatement* init, Expression* condition, AssigmentStatement* step, CompoundStatement* body) : LoopStatement(condition, body), init(init), step(step) {}
    };
}
