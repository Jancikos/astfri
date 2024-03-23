#pragma once

#include <libastfri/factories/ExpressionFactory.hpp>

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>
#include <libastfri/utils/Helper.hpp>

namespace lsfs = libastfri::structures;

namespace libastfri::factories {
class StatementFactory {
  public:
    static StatementFactory &getInstance();

  private:
    UsedList<lsfs::TranslationUnit *> translationUnits;
    UsedList<lsfs::Statement *> statements;

    StatementFactory() = default;
    ~StatementFactory();

  public:
    StatementFactory(StatementFactory const &) = delete;
    void operator=(StatementFactory const &) = delete;

    lsfs::TranslationUnit *
    createTranslationUnit(std::vector<lsfs::FunctionDefinition *> functions);
    lsfs::CompoundStatement *
    createCompoundStatement(std::vector<lsfs::Statement *> statements);
    lsfs::DeclarationStatement *createDeclarationStatement(lsfs::Declaration *declaration);
    lsfs::DeclarationAndAssigmentStatement *
    createDeclarationAndAssigmentStatement(lsfs::Declaration *declaration,
                                           lsfs::Expression *expression);

    lsfs::ReturnStatement *createReturnStatement(lsfs::Expression *value);

    lsfs::ExpressionStatement *createExpressionStatement(lsfs::Expression *expression);

    lsfs::IfStatement *
    createIfConditionalStatement(lsfs::Expression *condition,
                                 lsfs::CompoundStatement *ifTrue,
                                 lsfs::CompoundStatement *ifFalse = nullptr);
    lsfs::IfStatement *createIfConditionalStatement(lsfs::Expression *condition,
                                              lsfs::Statement *ifTrue,
                                              lsfs::Statement *ifFalse = nullptr);

    lsfs::WhileLoopStatement *createWhileLoopStatement(lsfs::Expression *condition,
                                                 lsfs::CompoundStatement *body);
    lsfs::WhileLoopStatement *createWhileLoopStatement(lsfs::Expression *condition,
                                                 lsfs::Statement *statement);

    lsfs::DoWhileLoopStatement *createDoWhileLoopStatement(lsfs::Expression *condition,
                                                     lsfs::CompoundStatement *body);
    lsfs::ForLoopStatement *createForLoopStatement(lsfs::ExpressionStatement *init,
                                             lsfs::Expression *condition,
                                             lsfs::ExpressionStatement *step,
                                             lsfs::CompoundStatement *body);

    lsfs::UnknownStatement *createUnknownStatement(std::string message);
};
} // namespace libastfri::factories
