
#include <libastfri/factories/StatementFactory.hpp>

namespace libastfri::factories {
    
    StatementFactory& StatementFactory::getInstance()
    {
        static StatementFactory instance;

        return instance;
    }

    CompoundStatement* StatementFactory::createCompoundStatement (std::vector<Statement*> statements)
    {
        compoundStatements.emplace_back(CompoundStatement(std::move(statements)));
        
        return &compoundStatements.back();
    }

    DeclarationStatement* StatementFactory::createDeclarationStatement (Variable* variable)
    {
        declarationStatements.emplace_back(DeclarationStatement(variable));
        
        return &declarationStatements.back();
    }

    AssigmentStatement* StatementFactory::createAssigmentStatement (Variable* left, Expression* right)
    {
        assigmentStatements.emplace_back(AssigmentStatement(left, right));
        
        return &assigmentStatements.back();
    }

    DeclarationAndAssigmentStatement* StatementFactory::createDeclarationAndAssigmentStatement (Variable* left, Expression* right)
    {
        declarationAndAssigmentStatements.emplace_back(DeclarationAndAssigmentStatement(left, right));
        
        return &declarationAndAssigmentStatements.back();
    }

    ReturnStatement* StatementFactory::createReturnStatement (Expression* value)
    {
        returnStatements.emplace_back(ReturnStatement(value));
        
        return &returnStatements.back();
    }

    FunctionCallStatement* StatementFactory::createFunctionCallStatement (std::string functionName, std::vector<Expression*> arguments)
    {
        functionCallStatements.emplace_back(FunctionCallStatement(functionName, std::move(arguments)));
        
        return &functionCallStatements.back();
    }

    IfStatement* StatementFactory::createConditionalStatement (Expression* condition, CompoundStatement* thenBody, CompoundStatement* elseBody)
    {
        ifStatements.emplace_back(IfStatement(condition, thenBody, elseBody));
        
        return &ifStatements.back();
    }

    WhileLoopStatement* StatementFactory::createWhileLoopStatement (Expression* condition, CompoundStatement* body)
    {
        whileLoopStatements.emplace_back(WhileLoopStatement(condition, body));
        
        return &whileLoopStatements.back();
    }

    DoWhileLoopStatement* StatementFactory::createDoWhileLoopStatement (Expression* condition, CompoundStatement* body)
    {
        doWhileLoopStatements.emplace_back(DoWhileLoopStatement(condition, body));
        
        return &doWhileLoopStatements.back();
    }

    ForLoopStatement* StatementFactory::createForLoopStatement(AssigmentStatement* init, Expression* condition, AssigmentStatement* step, CompoundStatement* body)
    {
        forLoopStatements.emplace_back(ForLoopStatement(init, condition, step, body));
        
        return &forLoopStatements.back();
    }
}

