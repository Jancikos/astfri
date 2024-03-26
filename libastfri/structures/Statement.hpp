#pragma once

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/utils/OutputVisitor.hpp>
#include <string>
#include <vector>

namespace libastfri::structures
{
/**
 * @brief pre reprazentaciu celeho vstupneho bloku kodu / suboru
 *
 */
struct TranslationUnit : utils::OutputVisitable<TranslationUnit>
{
    std::vector<FunctionDefinition*> functions;

    TranslationUnit(std::vector<FunctionDefinition*> functions = {});
};

// "riadok" v kode
struct Statement : virtual utils::IOutputVisitable
{
    int rnd; // TODO vymazat - teraz IBA PRE TRAPNY DEBUGGING

    // potom presunut do .cpp
    Statement()
    {
        static int rnd = 0;
        this->rnd      = rnd++;
    }

    std::string toString () const
    {
        return "Statement " + std::to_string(rnd) + "\n";
    }
};

struct CompoundStatement : Statement, utils::OutputVisitable<CompoundStatement>
{
    std::vector<Statement*> statements;

    CompoundStatement(std::vector<Statement*> statements = {});

    std::string toString () const
    {
        std::string result;
        for (auto const& statement : statements)
        {
            result += statement->toString();
        }
        return result;
    }
};

struct DeclarationStatement :
    Statement,
    utils::OutputVisitable<DeclarationStatement>
{
    Declaration* declaration;

    DeclarationStatement(Declaration* declaration);

    std::string toString () const
    {
        // Implement the toString() function for DeclarationStatement
        std::string result = "DeclarationStatement: ";
        // result += variable->toString();
        return result;
    }
};

struct DeclarationAndAssigmentStatement : Statement, utils::OutputVisitable<DeclarationAndAssigmentStatement>
{
    Declaration* declaration;
    Expression* expression;

    DeclarationAndAssigmentStatement(
        Declaration* declaration,
        Expression* expression
    );

    std::string toString () const
    {
        // Implement the toString() function for
        // DeclarationAndAssigmentStatement
        std::string result = "DeclarationAndAssigmentStatement: ";
        // result += variable->toString();
        result += " = ";
        // result += exp->toString();
        return result;
    }
};

struct ReturnStatement : Statement, utils::OutputVisitable<ReturnStatement>
{
    Expression* value;

    ReturnStatement(Expression* value);

    std::string toString () const
    {
        // Implement the toString() function for ReturnStatement
        std::string result = "ReturnStatement: ";
        // result += value->toString();
        return result;
    }
};

struct ExpressionStatement :
    Statement,
    utils::OutputVisitable<ExpressionStatement>
{
    Expression* expression;

    ExpressionStatement(Expression* expression);

    std::string toString () const
    {
        // Implement the toString() function for ExpressionStatement
        std::string result = "ExpressionStatement: ";
        // result += expression->toString();
        return result;
    }
};

// Conditional statement
struct ConditionalStatement : Statement
{
    Expression* condition;

    ConditionalStatement(Expression* condition);

    std::string toString () const
    {
        // Implement the toString() function for ConditionalStatement
        std::string result = "ConditionalStatement: ";
        // result += condition->toString();
        return result;
    }
};

struct IfStatement : ConditionalStatement, utils::OutputVisitable<IfStatement>
{
    CompoundStatement* thenBody;
    CompoundStatement* elseBody;

    IfStatement(
        Expression* condition,
        CompoundStatement* thenBody,
        CompoundStatement* elseBody = nullptr
    );

    std::string toString () const
    {
        // Implement the toString() function for IfStatement
        std::string result = "IfStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nThen Body: ";
        result += thenBody->toString();
        result += "\nElse Body: ";
        result += elseBody->toString();
        return result;
    }
};

// Loop statement
struct LoopStatement : Statement
{
    Expression* condition;
    CompoundStatement* body;

    LoopStatement(Expression* condition, CompoundStatement* body);

    std::string toString () const
    {
        // Implement the toString() function for LoopStatement
        std::string result = "LoopStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct WhileLoopStatement :
    LoopStatement,
    utils::OutputVisitable<WhileLoopStatement>
{

    WhileLoopStatement(Expression* condition, CompoundStatement* body);

    std::string toString () const
    {
        // Implement the toString() function for WhileLoopStatement
        std::string result = "WhileLoopStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct DoWhileLoopStatement :
    LoopStatement,
    utils::OutputVisitable<DoWhileLoopStatement>
{

    DoWhileLoopStatement(Expression* condition, CompoundStatement* body);

    std::string toString () const
    {
        // Implement the toString() function for DoWhileLoopStatement
        std::string result = "DoWhileLoopStatement: ";
        result += "Condition: ";
        // result += condition->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct ForLoopStatement :
    LoopStatement,
    utils::OutputVisitable<ForLoopStatement>
{
    ExpressionStatement* init;
    ExpressionStatement* step;

    ForLoopStatement(
        ExpressionStatement* init,
        Expression* condition,
        ExpressionStatement* step,
        CompoundStatement* body
    );

    std::string toString () const
    {
        // Implement the toString() function for ForLoopStatement
        std::string result = "ForLoopStatement: ";
        result += "Init: ";
        result += init->toString();
        result += "\nCondition: ";
        // result += condition->toString();
        result += "\nStep: ";
        result += step->toString();
        result += "\nBody: ";
        result += body->toString();
        return result;
    }
};

struct UnknownStatement : Statement, utils::OutputVisitable<UnknownStatement>
{
    std::string message;

    UnknownStatement(std::string message);
};
} // namespace libastfri::structures