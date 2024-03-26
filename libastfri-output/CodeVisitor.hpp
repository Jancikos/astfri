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

    // decl
    virtual void Visit(structures::FunctionDefinition const& functionDef) override;
    virtual void Visit(structures::ParameterDefinition const& decl) override;

    // type
    virtual void Visit(structures::IntType const& type) override;

    ~CodeVisitor() override = default;


protected:
    std::ostream& outStream;
    void printEndl ();
};
} // namespace libastfri::output