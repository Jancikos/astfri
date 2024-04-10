#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

#include <libastfri/utils/Helper.hpp>

#include <libastfri-output/visitors/CodeVisitor.hpp>

namespace lsfs = libastfri::structures;
namespace lsfu = libastfri::utils;

namespace libastfrioutput::visitors
{
CodeVisitor::CodeVisitor(lsfu::IOutputFormatter& formatter) :
    formatter(formatter)
{
}

void CodeVisitor::Output(lsfs::TranslationUnit const& translationUnit)
{
    this->Visit(translationUnit);
}

lsfu::IOutputFormatter& CodeVisitor::getFormatter()
{
    return this->formatter;
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

    this->getFormatter().printIndented("{");
    this->getFormatter().printEndl(false);
    this->getFormatter().indentIncrease();

    for (auto statement : stmt.statements)
    {
        statement->accept(*this);
    }
    this->getFormatter().indentDecrease();
    this->getFormatter().printIndented("}");
    this->getFormatter().printEndl(false);
}

void CodeVisitor::Visit(lsfs::DeclarationStatement const& stmt)
{
    this->getFormatter().printIndent();
    stmt.declaration->accept(*this);
    this->getFormatter().printEndl();
}

void CodeVisitor::Visit(lsfs::DeclarationAndAssigmentStatement const& stmt)
{
    this->getFormatter().printIndent();
    stmt.declaration->accept(*this);
    this->getFormatter().printOperator(" = ");
    stmt.expression->accept(*this);
    this->getFormatter().printEndl();
}

void CodeVisitor::Visit(lsfs::ReturnStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("return ");
    stmt.value->accept(*this);
    this->getFormatter().printEndl();
}

void CodeVisitor::Visit(lsfs::ExpressionStatement const& stmt)
{
    this->getFormatter().printIndent();
    stmt.expression->accept(*this);
    this->getFormatter().printEndl();
}

void CodeVisitor::Visit(lsfs::UnknownStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printError("UNKNOW STATEMNT (" + stmt.message + ")");
    this->getFormatter().printEndl();
}

void CodeVisitor::Visit(lsfs::IfStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("if");
    this->getFormatter().print(" (");
    stmt.condition->accept(*this);
    this->getFormatter().print(")");
    this->getFormatter().printEndl(false);
    stmt.thenBody->accept(*this);
    if (stmt.elseBody != nullptr)
    {
        this->getFormatter().printIndent();
        this->getFormatter().printKeyword("else");
        this->getFormatter().printEndl(false);
        stmt.elseBody->accept(*this);
    }
}

void CodeVisitor::Visit(lsfs::WhileStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("while");
    this->getFormatter().print(" (");
    stmt.condition->accept(*this);
    this->getFormatter().print(")");
    this->getFormatter().printEndl(false);
    stmt.body->accept(*this);
}

void CodeVisitor::Visit(lsfs::ForStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("for");
    this->getFormatter().print(" (");

    // init
    this->getFormatter().startInlinePrinting();
    stmt.init->accept(*this);
    this->getFormatter().endInlinePrinting();

    //  condition
    stmt.condition->accept(*this);
    this->getFormatter().print("; ");

    // step
    stmt.step->accept(*this);
    this->getFormatter().print(")");
    this->getFormatter().printEndl(false);

    // body
    stmt.body->accept(*this);
}

// decl
void CodeVisitor::Visit(lsfs::FunctionDefinition const& functionDef)
{
    // function signature
    functionDef.returnType->accept(*this);

    this->getFormatter().printIdentifier(" " + functionDef.name);
    this->getFormatter().print("(");
    for (int i = 0; i < functionDef.parameters.size(); i++)
    {
        functionDef.parameters[i]->accept(*this);
        if (i < functionDef.parameters.size() - 1)
        {
            this->getFormatter().print(", ");
        }
    }
    this->getFormatter().print(")");
    this->getFormatter().printEndl(false);

    // function body
    functionDef.body->accept(*this);
}

void CodeVisitor::Visit(lsfs::ParameterDefinition const& decl)
{
    decl.type->accept(*this);
    this->getFormatter().printIdentifier(" " + decl.name);
}

void CodeVisitor::Visit(lsfs::VariableDefintion const& decl)
{
    decl.type->accept(*this);
    this->getFormatter().printIdentifier(" " + decl.name);
}

// expr

void CodeVisitor::Visit(lsfs::IntLiteral const& expr)
{
    this->getFormatter().printIntLiteral(std::to_string(expr.value));
}

void CodeVisitor::Visit(lsfs::BinaryExpression const& expr)
{
    expr.left->accept(*this);
    this->getFormatter().printOperator(
        " " + lsfu::Helper::convertBinaryOperator(expr.op) + " "
    );

    expr.right->accept(*this);
}

void CodeVisitor::Visit(lsfs::UnaryExpression const& expr)
{
    this->getFormatter().printOperator(lsfu::Helper::convertUnaryOperator(expr.op));
    expr.arg->accept(*this);
}

void CodeVisitor::Visit(lsfs::VarRefExpression const& expr)
{
    this->getFormatter().printIdentifier(expr.variable->name);
}

void CodeVisitor::Visit(lsfs::FunctionCallExpression const& expr)
{
    this->getFormatter().printIdentifier(expr.functionName);
    this->getFormatter().print("(");
    for (int i = 0; i < expr.arguments.size(); i++)
    {
        expr.arguments[i]->accept(*this);
        if (i < expr.arguments.size() - 1)
        {
            this->getFormatter().print(", ");
        }
    }
    this->getFormatter().print(")");
}

void CodeVisitor::Visit(lsfs::UnknownExpression const& expr)
{
    this->getFormatter().printError("UNKNOW EXPR (" + expr.message + ")");
}

// type
void CodeVisitor::Visit(lsfs::IntType const& type)
{
    this->getFormatter().printKeyword(type.name);
}

} // namespace libastfrioutput::visitors