#include <libastfri/structures/Function.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/factories/StatementFactory.hpp>

namespace libastfri::factories {

    StatementFactory& StatementFactory::getInstance()
    {
        static StatementFactory instance;

        return instance;
    }

    StatementFactory::StatementFactory ()
    {
    }

    StatementFactory::~StatementFactory ()
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

    TranslationUnit* StatementFactory::createTranslationUnit (std::vector<FunctionDefinition*> functions)
    {
        auto* translationUnitStatement = new TranslationUnit{std::move(functions)};
        translationUnits.emplace_back(translationUnitStatement);
        
        return translationUnitStatement;
    }

    CompoundStatement* StatementFactory::createCompoundStatement (std::vector<Statement*> statements)
    {
        auto* compoundStatement = new CompoundStatement{{}, std::move(statements)};
        statements.emplace_back(compoundStatement);
        
        return compoundStatement;
    }

    DeclarationStatement* StatementFactory::createDeclarationStatement (VariableDefintion* variable)
    {
        auto* declarationStatement = new DeclarationStatement{{}, variable};
        statements.emplace_back(declarationStatement);

        declarationStatement->rnd = 600;

        return declarationStatement;
    }

    AssigmentStatement* StatementFactory::createAssigmentStatement (VariableDefintion* left, Expression* right)
    {
        auto* assigmentStatement = new AssigmentStatement{{}, left, right};
        statements.emplace_back(assigmentStatement);

        assigmentStatement->rnd = 601;

        return assigmentStatement;
    }

    DeclarationAndAssigmentStatement* StatementFactory::createDeclarationAndAssigmentStatement (VariableDefintion* var, Expression* exp)
    {
        auto* declarationAndAssigmentStatement = new DeclarationAndAssigmentStatement({{{}, var}, exp});
        statements.emplace_back(declarationAndAssigmentStatement);
        
        declarationAndAssigmentStatement->rnd = 60001;
        
        return declarationAndAssigmentStatement;
    }

    ReturnStatement* StatementFactory::createReturnStatement (Expression* value)
    {
        auto* returnStatement = new ReturnStatement{{}, value};
        statements.emplace_back(returnStatement);

        returnStatement->rnd = 333;
        
        return returnStatement;
    }

    ExpressionStatement* StatementFactory::createExpressionStatement (Expression* expression)
    {
        auto* expressionStatement = new ExpressionStatement{{}, expression};
        statements.emplace_back(expressionStatement);

        expressionStatement->rnd = 888;
        
        return expressionStatement;
    }

    IfStatement* StatementFactory::createIfConditionalStatement (Expression* condition, CompoundStatement* thenBody, CompoundStatement* elseBody)
    {
        auto* ifStatement = new IfStatement{{{}, condition}, thenBody, elseBody};
        statements.emplace_back(ifStatement);
        
        return ifStatement;
    }

    IfStatement* StatementFactory::createIfConditionalStatement (Expression* condition, Statement* thenStatement, Statement* elseStatement)
    {
        auto* thenBody = createCompoundStatement({thenStatement});
        auto* elseBody = createCompoundStatement({elseStatement});

        return createIfConditionalStatement(condition, thenBody, elseBody);
    }

    WhileLoopStatement* StatementFactory::createWhileLoopStatement (Expression* condition, CompoundStatement* body)
    {
        auto* whileLoopStatement = new WhileLoopStatement{{{}, condition, body}};
        statements.emplace_back(whileLoopStatement);
        
        return whileLoopStatement;
    }

    WhileLoopStatement* StatementFactory::createWhileLoopStatement (Expression* condition, Statement* statement)
    {
        auto* body = createCompoundStatement({statement});

        return createWhileLoopStatement(condition, body);
    }

    DoWhileLoopStatement* StatementFactory::createDoWhileLoopStatement (Expression* condition, CompoundStatement* body)
    {
        auto* doWhileLoopStatement = new DoWhileLoopStatement{{{}, condition, body}};
        statements.emplace_back(doWhileLoopStatement);
        
        return doWhileLoopStatement;
    }

    ForLoopStatement* StatementFactory::createForLoopStatement(AssigmentStatement* init, Expression* condition, AssigmentStatement* step, CompoundStatement* body)
    {
        ForLoopStatement* forLoopStatement = new ForLoopStatement{{{}, condition, body}, init, step};
        statements.emplace_back(forLoopStatement);
        
        return forLoopStatement;
    }
}

