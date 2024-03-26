#pragma once

#include <libastfri/utils/OutputVisitor.hpp>
#include <ostream>

namespace libastfri::output
{
class CodeVisitor : public libastfri::utils::OutputVisitorAdapter
{
public:
    CodeVisitor(std::ostream& outStream);

    // ovverridenut len tie funkcie ktore naozaj teraz chcem

    // stmt
    virtual void Visit(structures::TranslationUnit const& translationUnit) override;
    virtual void Visit(structures::CompoundStatement const& stmt) override;
    virtual void Visit(structures::DeclarationStatement const& stmt) override;
    virtual void Visit(structures::DeclarationAndAssigmentStatement const& stmt) override;
    virtual void Visit(structures::ReturnStatement const& stmt) override;
    virtual void Visit(structures::ExpressionStatement const& stmt) override;
    virtual void Visit(structures::UnknownStatement const& stmt) override;
    virtual void Visit(structures::IfStatement const& stmt) override;
    virtual void Visit(structures::WhileLoopStatement const& stmt) override;

    // decl
    virtual void Visit(structures::FunctionDefinition const& functionDef) override;
    virtual void Visit(structures::ParameterDefinition const& decl) override;
    virtual void Visit(structures::VariableDefintion const& decl) override;

    // expr
    virtual void Visit(structures::IntLiteral const& expr) override;
    virtual void Visit(structures::BinaryExpression const& expr) override;
    virtual void Visit(structures::VarRefExpression const& expr) override;
    virtual void Visit(structures::FunctionCallExpression const& expr) override;
    virtual void Visit(structures::UnknownExpression const& expr) override;

    // type
    virtual void Visit(structures::IntType const& type) override;

    

    ~CodeVisitor() override = default;


protected:
    std::ostream& outStream;
    int level = 0;
    void printIndent ();
    void printOnNewLine (std::string const& str, bool endLine = true);
    void printEndl (bool semicolon = true);
};
} // namespace libastfri::output