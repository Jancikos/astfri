
#include "libastfri/structures/Statement.hpp"
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

        return declarationStatement;
    }

    AssigmentStatement* StatementFactory::createAssigmentStatement (VariableDefintion* left, Expression* right)
    {
        auto* assigmentStatement = new AssigmentStatement{{}, left, right};
        statements.emplace_back(assigmentStatement);

        return assigmentStatement;
    }

    DeclarationAndAssigmentStatement* StatementFactory::createDeclarationAndAssigmentStatement (VariableDefintion* left, Expression* right)
    {
        auto* declarationAndAssigmentStatement = new DeclarationAndAssigmentStatement({{{}, left, right}});
        statements.emplace_back(declarationAndAssigmentStatement);
        
        return declarationAndAssigmentStatement;
    }

    ReturnStatement* StatementFactory::createReturnStatement (Expression* value)
    {
        auto* returnStatement = new ReturnStatement{{}, value};
        statements.emplace_back(returnStatement);
        
        return returnStatement;
    }

    FunctionCallStatement* StatementFactory::createFunctionCallStatement (std::string functionName, std::vector<Expression*> arguments)
    {
        auto* functionCallStatement = new FunctionCallStatement{{}, functionName, std::move(arguments)};
        statements.emplace_back(functionCallStatement);
        
        return functionCallStatement;
    }

    IfStatement* StatementFactory::createIfConditionalStatement (Expression* condition, CompoundStatement* thenBody, CompoundStatement* elseBody)
    {
        auto* ifStatement = new IfStatement{{{}, condition}, thenBody, elseBody};
        statements.emplace_back(ifStatement);
        
        return ifStatement;
    }

    WhileLoopStatement* StatementFactory::createWhileLoopStatement (Expression* condition, CompoundStatement* body)
    {
        auto* whileLoopStatement = new WhileLoopStatement{{{}, condition, body}};
        statements.emplace_back(whileLoopStatement);
        
        return whileLoopStatement;
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

