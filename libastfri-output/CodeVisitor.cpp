#include <libastfri-output/CodeVisitor.hpp>
#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

#include "libastfri/utils/Helper.hpp"

namespace lsfs = libastfri::structures;

namespace libastfri::output
{
CodeVisitor::CodeVisitor(std::ostream& outStream) : outStream(outStream)
{
}

void CodeVisitor::printEndl(bool semicolon)
{
    if (semicolon)
    {
        this->outStream << ";";
    }
    this->outStream << std::endl;
}

void CodeVisitor::printIndent()
{
    for (int i = 0; i < this->level; i++)
    {
        this->outStream << "    ";
    }
}

void CodeVisitor::printOnNewLine(std::string const& str, bool endLine)
{
    this->printIndent();
    this->outStream << str;

    if (endLine)
    {
        this->printEndl();
    }
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

void CodeVisitor::Visit(lsfs::CompoundStatement const& stmt)
{
    this->printOnNewLine("{", false);
    this->printEndl(false);
    this->level++;
    for (auto statement : stmt.statements)
    {
        statement->accept(*this);
    }
    this->level--;
    this->printOnNewLine("}", false);
    this->printEndl(false);
}

void CodeVisitor::Visit(lsfs::DeclarationStatement const& stmt)
{
    this->printIndent();
    stmt.declaration->accept(*this);
    this->printEndl();
}

void CodeVisitor::Visit(lsfs::DeclarationAndAssigmentStatement const& stmt)
{
    this->printIndent();
    stmt.declaration->accept(*this);
    this->outStream << " = ";
    stmt.expression->accept(*this);
    this->printEndl();
}

void CodeVisitor::Visit(lsfs::ReturnStatement const& stmt)
{
    this->printIndent();
    this->outStream << "return ";
    stmt.value->accept(*this);
    this->printEndl();
}

void CodeVisitor::Visit(lsfs::ExpressionStatement const& stmt)
{
    this->printIndent();
    stmt.expression->accept(*this);
    this->printEndl();
}

void CodeVisitor::Visit(lsfs::UnknownStatement const& stmt)
{
    this->printIndent();
    this->outStream << "UNKNOW STATEMNT (" << stmt.message << ")";
    this->printEndl();
}

void CodeVisitor::Visit(lsfs::IfStatement const& stmt)
{
    this->printIndent();
    this->outStream << "if (";
    stmt.condition->accept(*this);
    this->outStream << ")";
    this->printEndl(false);
    stmt.thenBody->accept(*this);
    if (stmt.elseBody != nullptr)
    {
        this->printIndent();
        this->outStream << "else";
        this->printEndl(false);
        stmt.elseBody->accept(*this);
    }
}

void CodeVisitor::Visit(lsfs::WhileLoopStatement const& stmt)
{
    this->printIndent();
    this->outStream << "while (";
    stmt.condition->accept(*this);
    this->outStream << ")\n";
    stmt.body->accept(*this);
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
    functionDef.body->accept(*this);
}

void CodeVisitor::Visit(lsfs::ParameterDefinition const& decl)
{
    decl.type->accept(*this);
    this->outStream << " " << decl.name;
}

void CodeVisitor::Visit(lsfs::VariableDefintion const& decl)
{
    decl.type->accept(*this);
    this->outStream << " " << decl.name;
}

// expr

void CodeVisitor::Visit(lsfs::IntLiteral const& expr)
{
    this->outStream << expr.value;
}

void CodeVisitor::Visit(lsfs::BinaryExpression const& expr)
{
    expr.left->accept(*this);
    this->outStream << " " << utils::Helper::convertBinaryOperator(expr.op)
                    << " ";
    expr.right->accept(*this);
}

void CodeVisitor::Visit(lsfs::VarRefExpression const& expr)
{
    this->outStream << expr.variable->name;
}

void CodeVisitor::Visit(lsfs::FunctionCallExpression const& expr)
{
    this->outStream << expr.functionName << "(";
    for (int i = 0; i < expr.arguments.size(); i++)
    {
        expr.arguments[i]->accept(*this);
        if (i < expr.arguments.size() - 1)
        {
            this->outStream << ", ";
        }
    }
    this->outStream << ")";
}

void CodeVisitor::Visit(lsfs::UnknownExpression const& expr)
{
    this->outStream << "UNKNOW EXPR (" << expr.message << ")";
}

// type
void CodeVisitor::Visit(lsfs::IntType const& type)
{
    this->outStream << type.name;
}

} // namespace libastfri::output