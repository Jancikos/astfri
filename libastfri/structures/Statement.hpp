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
    Statement() = default;
};

struct CompoundStatement : Statement, utils::OutputVisitable<CompoundStatement>
{
    std::vector<Statement*> statements;

    CompoundStatement(std::vector<Statement*> statements = {});
};

struct DeclarationStatement :
    Statement,
    utils::OutputVisitable<DeclarationStatement>
{
    Declaration* declaration;

    DeclarationStatement(Declaration* declaration);
};

struct DeclarationAndAssigmentStatement :
    Statement,
    utils::OutputVisitable<DeclarationAndAssigmentStatement>
{
    Declaration* declaration;
    Expression* expression;

    DeclarationAndAssigmentStatement(
        Declaration* declaration,
        Expression* expression
    );
};

struct ReturnStatement : Statement, utils::OutputVisitable<ReturnStatement>
{
    Expression* value;

    ReturnStatement(Expression* value);
};

struct ExpressionStatement :
    Statement,
    utils::OutputVisitable<ExpressionStatement>
{
    Expression* expression;

    ExpressionStatement(Expression* expression);
};

// Conditional statement
struct ConditionalStatement : Statement
{
    Expression* condition;

    ConditionalStatement(Expression* condition);
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
};

// Loop statement
struct LoopStatement : Statement
{
    Expression* condition;
    CompoundStatement* body;

    LoopStatement(Expression* condition, CompoundStatement* body);
};

struct WhileStatement :
    LoopStatement,
    utils::OutputVisitable<WhileStatement>
{
    WhileStatement(Expression* condition, CompoundStatement* body);
};

struct DoWhileStatement :
    LoopStatement,
    utils::OutputVisitable<DoWhileStatement>
{
    DoWhileStatement(Expression* condition, CompoundStatement* body);
};

struct ForStatement :
    LoopStatement,
    utils::OutputVisitable<ForStatement>
{
    Statement* init;
    Expression* step;

    ForStatement(
        Statement* init,
        Expression* condition,
        Expression* step,
        CompoundStatement* body
    );
};

struct UnknownStatement : Statement, utils::OutputVisitable<UnknownStatement>
{
    std::string message;

    UnknownStatement(std::string message);
};
} // namespace libastfri::structures