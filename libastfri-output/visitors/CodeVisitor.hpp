#pragma once

#include <libastfri/utils/OutputFormatter.hpp>
#include <libastfri/utils/OutputVisitor.hpp>

namespace lsfs = libastfri::structures;
namespace lsfu = libastfri::utils;

namespace libastfrioutput::visitors
{
// Visitor for printing code in well known, but not specified language syntax
class CodeVisitor : public lsfu::OutputVisitorAdapter
{
public:
    CodeVisitor(libastfri::utils::IOutputFormatter& formatter);

    void Output (lsfs::TranslationUnit const& translationUnit);
    lsfu::IOutputFormatter& getFormatter () override;

    // stmt
    virtual void Visit (lsfs::TranslationUnit const& translationUnit) override;
    virtual void Visit (lsfs::CompoundStatement const& stmt) override;
    virtual void Visit (lsfs::DeclarationStatement const& stmt) override;
    virtual void Visit (lsfs::DeclarationAndAssigmentStatement const& stmt
    ) override;
    virtual void Visit (lsfs::ReturnStatement const& stmt) override;
    virtual void Visit (lsfs::ExpressionStatement const& stmt) override;
    virtual void Visit (lsfs::UnknownStatement const& stmt) override;
    virtual void Visit (lsfs::IfStatement const& stmt) override;
    virtual void Visit (lsfs::WhileStatement const& stmt) override;
    virtual void Visit (lsfs::ForStatement const& stmt) override;

    // decl
    virtual void Visit (lsfs::FunctionDefinition const& functionDef) override;
    virtual void Visit (lsfs::ParameterDefinition const& decl) override;
    virtual void Visit (lsfs::VariableDefintion const& decl) override;

    // expr
    virtual void Visit (lsfs::IntLiteral const& expr) override;
    virtual void Visit (lsfs::BinaryExpression const& expr) override;
    virtual void Visit (lsfs::UnaryExpression const& expr) override;
    virtual void Visit (lsfs::VarRefExpression const& expr) override;
    virtual void Visit (lsfs::ParamRefExpression const& expr) override;
    virtual void Visit (lsfs::FunctionCallExpression const& expr) override;
    virtual void Visit (lsfs::UnknownExpression const& expr) override;

    // type
    virtual void Visit (lsfs::IntType const& type) override;

    ~CodeVisitor() override = default;

protected:
    lsfu::IOutputFormatter& formatter;
};
} // namespace libastfrioutput::visitors