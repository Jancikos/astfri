#pragma once

#include <libastfri/utils/OutputVisitor.hpp>
#include <libastfri/utils/OutputWriter.hpp>

namespace libastfri::output
{
class CodeVisitor : public libastfri::utils::OutputVisitorAdapter
{
public:
    CodeVisitor(libastfri::utils::IOutputWriter& writer);

    void Output(structures::TranslationUnit const& translationUnit);
    utils::IOutputWriter& getWriter() override;

    // stmt
    virtual void Visit (structures::TranslationUnit const& translationUnit
    ) override;
    virtual void Visit (structures::CompoundStatement const& stmt) override;
    virtual void Visit (structures::DeclarationStatement const& stmt) override;
    virtual void Visit (structures::DeclarationAndAssigmentStatement const& stmt
    ) override;
    virtual void Visit (structures::ReturnStatement const& stmt) override;
    virtual void Visit (structures::ExpressionStatement const& stmt) override;
    virtual void Visit (structures::UnknownStatement const& stmt) override;
    virtual void Visit (structures::IfStatement const& stmt) override;
    virtual void Visit (structures::WhileLoopStatement const& stmt) override;
    virtual void Visit (structures::ForLoopStatement const& stmt) override;

    // decl
    virtual void Visit (structures::FunctionDefinition const& functionDef
    ) override;
    virtual void Visit (structures::ParameterDefinition const& decl) override;
    virtual void Visit (structures::VariableDefintion const& decl) override;

    // expr
    virtual void Visit (structures::IntLiteral const& expr) override;
    virtual void Visit (structures::BinaryExpression const& expr) override;
    virtual void Visit (structures::UnaryExpression const& expr) override;
    virtual void Visit (structures::VarRefExpression const& expr) override;
    virtual void Visit (structures::FunctionCallExpression const& expr
    ) override;
    virtual void Visit (structures::UnknownExpression const& expr) override;

    // type
    virtual void Visit (structures::IntType const& type) override;

    ~CodeVisitor() override = default;

protected:
    libastfri::utils::IOutputWriter& writer;
    
};
} // namespace libastfri::output