#pragma once

#include <libastfri/factories/ExpressionFactory.hpp>

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>
#include <libastfri/utils/Helper.hpp>

namespace lsfs = libastfri::structures;

namespace libastfri::factories
{
class StatementFactory
{
public:
    static StatementFactory& getInstance ();

private:
    UsedList<lsfs::TranslationUnit*> translationUnits;
    UsedList<lsfs::Statement*> statements;

    StatementFactory() = default;
    ~StatementFactory();
    lsfs::CompoundStatement* tryGetCompoundStatement (lsfs::Statement* Statement
    );

public:
    StatementFactory(StatementFactory const&) = delete;
    void operator= (StatementFactory const&)  = delete;

    lsfs::TranslationUnit* createTranslationUnit (
        std::vector<lsfs::FunctionDefinition*> functions
    );
    lsfs::CompoundStatement* createCompoundStatement (
        std::vector<lsfs::Statement*> statements
    );
    lsfs::DeclarationStatement* createDeclarationStatement (
        lsfs::Declaration* declaration
    );
    lsfs::DeclarationAndAssigmentStatement*
        createDeclarationAndAssigmentStatement (
            lsfs::Declaration* declaration,
            lsfs::Expression* expression
        );

    lsfs::ReturnStatement* createReturnStatement (lsfs::Expression* value);

    lsfs::ExpressionStatement* createExpressionStatement (
        lsfs::Expression* expression
    );

    lsfs::IfStatement* createIfConditionalStatement (
        lsfs::Expression* condition,
        lsfs::CompoundStatement* ifTrue,
        lsfs::CompoundStatement* ifFalse = nullptr
    );
    lsfs::IfStatement* createIfConditionalStatement (
        lsfs::Expression* condition,
        lsfs::Statement* ifTrue,
        lsfs::Statement* ifFalse = nullptr
    );

    lsfs::WhileStatement* createWhileStatement (
        lsfs::Expression* condition,
        lsfs::CompoundStatement* body
    );
    lsfs::WhileStatement* createWhileStatement (
        lsfs::Expression* condition,
        lsfs::Statement* statement
    );

    lsfs::DoWhileStatement* createDoWhileStatement (
        lsfs::Expression* condition,
        lsfs::CompoundStatement* body
    );
    lsfs::ForStatement* createForStatement (
        lsfs::Statement* init,
        lsfs::Expression* condition,
        lsfs::Expression* step,
        lsfs::Statement* body
    );

    lsfs::UnknownStatement* createUnknownStatement (std::string message);
};
} // namespace libastfri::factories
