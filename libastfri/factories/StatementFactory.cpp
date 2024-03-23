#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Statement.hpp>

namespace libastfri::factories {

StatementFactory &StatementFactory::getInstance() {
    static StatementFactory instance;

    return instance;
}

StatementFactory::StatementFactory() {}

StatementFactory::~StatementFactory() {
    for (auto *statement : statements) {
        delete statement;
    }
    statements.clear();

    for (auto *translationUnit : translationUnits) {
        delete translationUnit;
    }
    translationUnits.clear();
}

TranslationUnit *StatementFactory::createTranslationUnit(
    std::vector<FunctionDefinition *> functions) {
    auto *translationUnitStatement = new TranslationUnit{std::move(functions)};
    translationUnits.emplace_back(translationUnitStatement);

    return translationUnitStatement;
}

CompoundStatement *
StatementFactory::createCompoundStatement(std::vector<Statement *> statements) {
    auto *compoundStatement = new CompoundStatement{{}, std::move(statements)};
    statements.emplace_back(compoundStatement);

    return compoundStatement;
}

DeclarationStatement *
StatementFactory::createDeclarationStatement(Declaration *declaration) {
    auto *declarationStatement = new DeclarationStatement{{}, declaration};
    statements.emplace_back(declarationStatement);

    declarationStatement->rnd = 600;

    return declarationStatement;
}

DeclarationAndAssigmentStatement *
StatementFactory::createDeclarationAndAssigmentStatement(
    Declaration *variable, Expression *expression) {
    auto *declarationAndAssigmentStatement =
        new DeclarationAndAssigmentStatement({{{}, variable}, expression});
    statements.emplace_back(declarationAndAssigmentStatement);

    declarationAndAssigmentStatement->rnd = 60001;

    return declarationAndAssigmentStatement;
}

ReturnStatement *StatementFactory::createReturnStatement(Expression *value) {
    auto *returnStatement = new ReturnStatement{{}, value};
    statements.emplace_back(returnStatement);

    returnStatement->rnd = 333;

    return returnStatement;
}

ExpressionStatement *
StatementFactory::createExpressionStatement(Expression *expression) {
    auto *expressionStatement = new ExpressionStatement{{}, expression};
    statements.emplace_back(expressionStatement);

    expressionStatement->rnd = 888;

    return expressionStatement;
}

IfStatement *
StatementFactory::createIfConditionalStatement(Expression *condition,
                                               CompoundStatement *thenBody,
                                               CompoundStatement *elseBody) {
    auto *ifStatement = new IfStatement{{{}, condition}, thenBody, elseBody};
    statements.emplace_back(ifStatement);

    return ifStatement;
}

IfStatement *StatementFactory::createIfConditionalStatement(
    Expression *condition, Statement *thenStatement, Statement *elseStatement) {
    auto *thenBody = createCompoundStatement({thenStatement});
    auto *elseBody = createCompoundStatement({elseStatement});

    return createIfConditionalStatement(condition, thenBody, elseBody);
}

WhileLoopStatement *
StatementFactory::createWhileLoopStatement(Expression *condition,
                                           CompoundStatement *body) {
    auto *whileLoopStatement = new WhileLoopStatement{{{}, condition, body}};
    statements.emplace_back(whileLoopStatement);

    return whileLoopStatement;
}

WhileLoopStatement *
StatementFactory::createWhileLoopStatement(Expression *condition,
                                           Statement *statement) {
    auto *body = createCompoundStatement({statement});

    return createWhileLoopStatement(condition, body);
}

DoWhileLoopStatement *
StatementFactory::createDoWhileLoopStatement(Expression *condition,
                                             CompoundStatement *body) {
    auto *doWhileLoopStatement =
        new DoWhileLoopStatement{{{}, condition, body}};
    statements.emplace_back(doWhileLoopStatement);

    return doWhileLoopStatement;
}

ForLoopStatement *StatementFactory::createForLoopStatement(
    ExpressionStatement *init, Expression *condition, ExpressionStatement *step,
    CompoundStatement *body) {
    ForLoopStatement *forLoopStatement =
        new ForLoopStatement{{{}, condition, body}, init, step};
    statements.emplace_back(forLoopStatement);

    return forLoopStatement;
}

UnknownStatement *StatementFactory::createUnknownStatement(std::string message) {
    auto *unknownStatement = new UnknownStatement(message);
    statements.emplace_back(unknownStatement);

    unknownStatement->rnd = 404;

    return unknownStatement;
}

} // namespace libastfri::factories
