#include <libastfri/factories/StatementFactory.hpp>

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Statement.hpp>

namespace libastfri::factories
{

StatementFactory& StatementFactory::getInstance()
{
    static StatementFactory instance;

    return instance;
}

StatementFactory::~StatementFactory()
{
    for (auto* statement : statements)
    {
        delete statement;
    }
    statements.clear();

    for (auto* translationUnit : translationUnits)
    {
        delete translationUnit;
    }
    translationUnits.clear();
}

lsfs::CompoundStatement* StatementFactory::tryGetCompoundStatement(
    lsfs::Statement* Statement
)
{
    if (Statement == nullptr)
    {
        return nullptr;
    }

    auto* compoundStatement = dynamic_cast<lsfs::CompoundStatement*>(Statement);
    if (compoundStatement == nullptr)
    {
        return createCompoundStatement({Statement});
    }

    return compoundStatement;
}

lsfs::TranslationUnit* StatementFactory::createTranslationUnit(
    std::vector<lsfs::FunctionDefinition*> functions
)
{
    auto* translationUnitStatement
        = new lsfs::TranslationUnit {std::move(functions)};
    translationUnits.emplace_back(translationUnitStatement);

    return translationUnitStatement;
}

lsfs::CompoundStatement* StatementFactory::createCompoundStatement(
    std::vector<lsfs::Statement*> statements
)
{
    auto* compoundStatement
        = new lsfs::CompoundStatement(std::move(statements));
    statements.emplace_back(compoundStatement);

    return compoundStatement;
}

lsfs::DeclarationStatement* StatementFactory::createDeclarationStatement(
    lsfs::Declaration* declaration
)
{
    auto* declarationStatement = new lsfs::DeclarationStatement(declaration);
    statements.emplace_back(declarationStatement);

    return declarationStatement;
}

lsfs::DeclarationAndAssigmentStatement* StatementFactory::
    createDeclarationAndAssigmentStatement(
        lsfs::Declaration* variable,
        lsfs::Expression* expression
    )
{
    auto* declarationAndAssigmentStatement
        = new lsfs::DeclarationAndAssigmentStatement(variable, expression);
    statements.emplace_back(declarationAndAssigmentStatement);

    return declarationAndAssigmentStatement;
}

lsfs::ReturnStatement* StatementFactory::createReturnStatement(
    lsfs::Expression* value
)
{
    auto* returnStatement = new lsfs::ReturnStatement(value);
    statements.emplace_back(returnStatement);

    return returnStatement;
}

lsfs::ExpressionStatement* StatementFactory::createExpressionStatement(
    lsfs::Expression* expression
)
{
    auto* expressionStatement = new lsfs::ExpressionStatement(expression);
    statements.emplace_back(expressionStatement);

    return expressionStatement;
}

lsfs::IfStatement* StatementFactory::createIfConditionalStatement(
    lsfs::Expression* condition,
    lsfs::CompoundStatement* thenBody,
    lsfs::CompoundStatement* elseBody
)
{
    auto* ifStatement = new lsfs::IfStatement(condition, thenBody, elseBody);
    statements.emplace_back(ifStatement);

    return ifStatement;
}

lsfs::IfStatement* StatementFactory::createIfConditionalStatement(
    lsfs::Expression* condition,
    lsfs::Statement* thenStatement,
    lsfs::Statement* elseStatement
)
{
    // try parse statements to compound statements
    auto* thenCompoundStatement = tryGetCompoundStatement(thenStatement);
    auto* elseCompoundStatement = tryGetCompoundStatement(elseStatement);

    return createIfConditionalStatement(
        condition,
        thenCompoundStatement,
        elseCompoundStatement
    );
}

lsfs::WhileLoopStatement* StatementFactory::createWhileLoopStatement(
    lsfs::Expression* condition,
    lsfs::CompoundStatement* body
)
{
    auto* whileLoopStatement = new lsfs::WhileLoopStatement(condition, body);
    statements.emplace_back(whileLoopStatement);

    return whileLoopStatement;
}

lsfs::WhileLoopStatement* StatementFactory::createWhileLoopStatement(
    lsfs::Expression* condition,
    lsfs::Statement* statement
)
{
    auto* body = tryGetCompoundStatement(statement);

    return createWhileLoopStatement(condition, body);
}

lsfs::DoWhileLoopStatement* StatementFactory::createDoWhileLoopStatement(
    lsfs::Expression* condition,
    lsfs::CompoundStatement* body
)
{
    auto* doWhileLoopStatement
        = new lsfs::DoWhileLoopStatement(condition, body);
    statements.emplace_back(doWhileLoopStatement);

    return doWhileLoopStatement;
}

lsfs::ForLoopStatement* StatementFactory::createForLoopStatement(
    lsfs::Statement* init,
    lsfs::Expression* condition,
    lsfs::Expression* step,
    lsfs::Statement* body
)
{
    lsfs::ForLoopStatement* forLoopStatement = new lsfs::ForLoopStatement(
        init,
        condition,
        step,
        tryGetCompoundStatement(body)
    );
    statements.emplace_back(forLoopStatement);

    return forLoopStatement;
}

lsfs::UnknownStatement* StatementFactory::createUnknownStatement(
    std::string message
)
{
    auto* unknownStatement = new lsfs::UnknownStatement(message);
    statements.emplace_back(unknownStatement);

    return unknownStatement;
}

} // namespace libastfri::factories
