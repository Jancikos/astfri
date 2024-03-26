#include <libastfri-output/CodeVisitor.hpp>

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

namespace lsfs = libastfri::structures;

namespace libastfri::output
{
CodeVisitor::CodeVisitor(std::ostream& outStream) : outStream(outStream)
{
}

void CodeVisitor::printEndl()
{
    this->outStream << ";" << std::endl;
}

// smtmt
void CodeVisitor::Visit(lsfs::TranslationUnit const& translationUnit)
{
    // declarations
    for (auto functionDef : translationUnit.functions)
    {
        functionDef->OutputVisitable::accept(*this);
    }
}

// decl
void CodeVisitor::Visit(lsfs::FunctionDefinition const& functionDef)
{
    // function signature
    functionDef.returnType->accept(*this);

    this->outStream << " " << functionDef.name << "(";
    for (int i = 0; i < functionDef.parameters.size(); i++)
    {
        functionDef.parameters[i]->accept(*this);
        if (i < functionDef.parameters.size() - 1)
        {
            this->outStream << ", ";
        }
    }
    this->outStream << ")\n";

    // function body
    // this->acceptCRTP(functionDef.body);
    functionDef.body->accept(*this);
    // functionDef->body->OutputVisitable::accept(*this);
}

void CodeVisitor::Visit(lsfs::ParameterDefinition const& decl)
{
    decl.type->accept(*this);
    this->outStream << " " << decl.name;
}

// type
void CodeVisitor::Visit(lsfs::IntType const& type)
{
    this->outStream << "int";
}



} // namespace libastfri::output