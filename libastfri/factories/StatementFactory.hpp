#pragma once

#include <libastfri/structures/Declaration.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>
#include <libastfri/utils/Helper.hpp>

using namespace libastfri::structures;
using namespace libastfri::utils;

namespace libastfri::factories {
class StatementFactory {
  public:
    static StatementFactory &getInstance();

  private:
    UsedList<TranslationUnit *> translationUnits;
    UsedList<Statement *> statements;

    StatementFactory();
    ~StatementFactory();

  public:
    StatementFactory(StatementFactory const &) = delete;
    void operator=(StatementFactory const &) = delete;

    TranslationUnit *
    createTranslationUnit(std::vector<FunctionDefinition *> functions);
    CompoundStatement *
    createCompoundStatement(std::vector<Statement *> statements);
    DeclarationStatement *createDeclarationStatement(Declaration *declaration);
    DeclarationAndAssigmentStatement *
    createDeclarationAndAssigmentStatement(Declaration *declaration,
                                           Expression *expression);

    ReturnStatement *createReturnStatement(Expression *value);

    ExpressionStatement *createExpressionStatement(Expression *expression);

    IfStatement *
    createIfConditionalStatement(Expression *condition,
                                 CompoundStatement *ifTrue,
                                 CompoundStatement *ifFalse = nullptr);
    IfStatement *createIfConditionalStatement(Expression *condition,
                                              Statement *ifTrue,
                                              Statement *ifFalse = nullptr);

    WhileLoopStatement *createWhileLoopStatement(Expression *condition,
                                                 CompoundStatement *body);
    WhileLoopStatement *createWhileLoopStatement(Expression *condition,
                                                 Statement *statement);

    DoWhileLoopStatement *createDoWhileLoopStatement(Expression *condition,
                                                     CompoundStatement *body);
    ForLoopStatement *createForLoopStatement(ExpressionStatement *init,
                                             Expression *condition,
                                             ExpressionStatement *step,
                                             CompoundStatement *body);
};
} // namespace libastfri::factories
