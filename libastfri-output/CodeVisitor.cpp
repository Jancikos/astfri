#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

#include <libastfri-output/CodeVisitor.hpp>

#include <libastfri/utils/Helper.hpp>

namespace lsfs = libastfri::structures;

namespace libastfri::output
{
CodeVisitor::CodeVisitor(libastfri::utils::IOutputWriter& writer)
    : writer(writer)
{
}

void CodeVisitor::Output(structures::TranslationUnit const& translationUnit)
{
    this->Visit(translationUnit);
}

utils::IOutputWriter& CodeVisitor::getWriter()
{
    return this->writer;
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
    this->writer.printOnNewLine("{", false);
    this->writer.printEndl(false);
    this->writer.indentIncress();
    for (auto statement : stmt.statements)
    {
        statement->accept(*this);
    }
    this->writer.indentDecress();
    this->writer.printOnNewLine("}", false);
    this->writer.printEndl(false);
}

void CodeVisitor::Visit(lsfs::DeclarationStatement const& stmt)
{
    this->writer.printIndent();
    stmt.declaration->accept(*this);
    this->writer.printEndl();
}

void CodeVisitor::Visit(lsfs::DeclarationAndAssigmentStatement const& stmt)
{
    this->writer.printIndent();
    stmt.declaration->accept(*this);
    this->writer.print(" = ");
    stmt.expression->accept(*this);
    this->writer.printEndl();
}

void CodeVisitor::Visit(lsfs::ReturnStatement const& stmt)
{
    this->writer.printIndent();
    this->writer.print("return ");
    stmt.value->accept(*this);
    this->writer.printEndl();
}

void CodeVisitor::Visit(lsfs::ExpressionStatement const& stmt)
{
    this->writer.printIndent();
    stmt.expression->accept(*this);
    this->writer.printEndl();
}

void CodeVisitor::Visit(lsfs::UnknownStatement const& stmt)
{
    this->writer.printIndent();
    this->writer.print("UNKNOW STATEMNT (" + stmt.message + ")");
    this->writer.printEndl();
}

void CodeVisitor::Visit(lsfs::IfStatement const& stmt)
{
    this->writer.printIndent();
    this->writer.print("if (");
    stmt.condition->accept(*this);
    this->writer.print(")");
    this->writer.printEndl(false);
    stmt.thenBody->accept(*this);
    if (stmt.elseBody != nullptr)
    {
        this->writer.printIndent();
        this->writer.print("else");
        this->writer.printEndl(false);
        stmt.elseBody->accept(*this);
    }
}

void CodeVisitor::Visit(lsfs::WhileLoopStatement const& stmt)
{
    this->writer.printIndent();
    this->writer.print("while (");
    stmt.condition->accept(*this);
    this->writer.print(")\n");
    stmt.body->accept(*this);
}

void CodeVisitor::Visit(lsfs::ForLoopStatement const& stmt)
{
    this->writer.printIndent();
    this->writer.print("for (");

    // init
    this->writer.startInlinePrinting();
    stmt.init->accept(*this);
    this->writer.endInlinePrinting();

    //  condition
    stmt.condition->accept(*this);
    this->writer.print("; ");

    // step
    stmt.step->accept(*this);
    this->writer.print(")");
    this->writer.printEndl(false);

    // body
    stmt.body->accept(*this);
}

// decl
void CodeVisitor::Visit(lsfs::FunctionDefinition const& functionDef)
{
    // function signature
    functionDef.returnType->accept(*this);

    this->writer.print(" " + functionDef.name + "(");
    for (int i = 0; i < functionDef.parameters.size(); i++)
    {
        functionDef.parameters[i]->accept(*this);
        if (i < functionDef.parameters.size() - 1)
        {
            this->writer.print(", ");
        }
    }
    this->writer.print(")\n");

    // function body
    functionDef.body->accept(*this);
}

void CodeVisitor::Visit(lsfs::ParameterDefinition const& decl)
{
    decl.type->accept(*this);
    this->writer.print(" " + decl.name);
}

void CodeVisitor::Visit(lsfs::VariableDefintion const& decl)
{
    decl.type->accept(*this);
    this->writer.print(" " + decl.name);
}

// expr

void CodeVisitor::Visit(lsfs::IntLiteral const& expr)
{
    this->writer.print(std::to_string(expr.value));
}

void CodeVisitor::Visit(lsfs::BinaryExpression const& expr)
{
    expr.left->accept(*this);
    this->writer.print(" " + utils::Helper::convertBinaryOperator(expr.op)
                    + " ");
    expr.right->accept(*this);
}

void CodeVisitor::Visit(lsfs::UnaryExpression const& expr)
{
    this->writer.print(utils::Helper::convertUnaryOperator(expr.op));
    expr.arg->accept(*this);
}

void CodeVisitor::Visit(lsfs::VarRefExpression const& expr)
{
    this->writer.print(expr.variable->name);
}

void CodeVisitor::Visit(lsfs::FunctionCallExpression const& expr)
{
    this->writer.print(expr.functionName + "(");
    for (int i = 0; i < expr.arguments.size(); i++)
    {
        expr.arguments[i]->accept(*this);
        if (i < expr.arguments.size() - 1)
        {
            this->writer.print(", ");
        }
    }
    this->writer.print(")");
}

void CodeVisitor::Visit(lsfs::UnknownExpression const& expr)
{
    this->writer.print("UNKNOW EXPR (" + expr.message + ")");
}

// type
void CodeVisitor::Visit(lsfs::IntType const& type)
{
    this->writer.print(type.name);
}

} // namespace libastfri::output