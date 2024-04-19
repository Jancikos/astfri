#include <cstddef>
#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

#include <libastfri/utils/Helper.hpp>

#include <libastfri-output/visitors/PseudocodeVisitor.hpp>

namespace lsfs = libastfri::structures;
namespace lsfu = libastfri::utils;

namespace libastfrioutput::visitors
{
PseudocodeVisitor::PseudocodeVisitor(lsfu::IOutputFormatter& formatter) :
    formatter(formatter)
{
}

void PseudocodeVisitor::Output(lsfs::TranslationUnit const& translationUnit)
{
    this->Visit(translationUnit);
}

lsfu::IOutputFormatter& PseudocodeVisitor::getFormatter()
{
    return this->formatter;
}

std::string PseudocodeVisitor::convertBinaryOperator(lsfs::BinaryOperators op)
{
    switch (op)
    {
    case lsfs::BinaryOperators::Assign:
        return "<=";
    default:
        return lsfu::Helper::convertBinaryOperator(op);
    }
}

// smtmt
void PseudocodeVisitor::Visit(lsfs::TranslationUnit const& translationUnit)
{
    // declarations
    for (auto functionDef : translationUnit.functions)
    {
        functionDef->OutputVisitable::accept(*this);
    }
}

void PseudocodeVisitor::Visit(lsfs::CompoundStatement const& stmt)
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

void PseudocodeVisitor::Visit(lsfs::DeclarationStatement const& stmt)
{
    this->getFormatter().printIndent();
    stmt.declaration->accept(*this);
    this->getFormatter().printEndl(false);
}

void PseudocodeVisitor::Visit(lsfs::DeclarationAndAssigmentStatement const& stmt
)
{
    this->getFormatter().printIndent();
    stmt.declaration->accept(*this);
    this->getFormatter().printOperator(" <= ");
    stmt.expression->accept(*this);
    this->getFormatter().printEndl(false);
}

void PseudocodeVisitor::Visit(lsfs::ReturnStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("Vráť ");
    stmt.value->accept(*this);
    this->getFormatter().printEndl(false);
}

void PseudocodeVisitor::Visit(lsfs::ExpressionStatement const& stmt)
{
    this->getFormatter().printIndent();
    stmt.expression->accept(*this);
    this->getFormatter().printEndl(false);
}

void PseudocodeVisitor::Visit(lsfs::UnknownStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printError("UNKNOW STATEMENT (" + stmt.message + ")");
    this->getFormatter().printEndl(false);
}

void PseudocodeVisitor::Visit(lsfs::IfStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("Ak");
    this->getFormatter().print(" (");
    stmt.condition->accept(*this);
    this->getFormatter().print(") ");
    this->getFormatter().printKeyword("potom");
    this->getFormatter().printEndl(false);
    stmt.thenBody->accept(*this);
    if (stmt.elseBody != nullptr)
    {
        this->getFormatter().printIndent();
        this->getFormatter().printKeyword("Inak");
        this->getFormatter().printEndl(false);
        stmt.elseBody->accept(*this);
    }
}

void PseudocodeVisitor::Visit(lsfs::WhileStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("Pokiaľ");
    this->getFormatter().print(" (");
    stmt.condition->accept(*this);
    this->getFormatter().print(")");
    this->getFormatter().printEndl(false);
    stmt.body->accept(*this);
}

void PseudocodeVisitor::Visit(lsfs::ForStatement const& stmt)
{
    this->getFormatter().printIndent();
    this->getFormatter().printKeyword("Pre");
    this->getFormatter().print(" (");

    // init
    this->getFormatter().startInlinePrinting();
    stmt.init->accept(*this);
    this->getFormatter().endInlinePrinting();
    this->getFormatter().print("; ");

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
void PseudocodeVisitor::Visit(lsfs::FunctionDefinition const& functionDef)
{
    // function signature
    this->getFormatter().printKeyword("operácia");
    this->getFormatter().print(" ");
    this->getFormatter().printIdentifier(functionDef.name);
    this->getFormatter().print("(");
    for (size_t i = 0; i < functionDef.parameters.size(); i++)
    {
        functionDef.parameters[i]->accept(*this);
        if (i < functionDef.parameters.size() - 1)
        {
            this->getFormatter().print(", ");
        }
    }

    // retur type
    this->getFormatter().print(") ");
    this->getFormatter().printKeyword(":");
    this->getFormatter().print(" ");
    functionDef.returnType->accept(*this);

    this->getFormatter().printEndl(false);

    // function body
    functionDef.body->accept(*this);
}

void PseudocodeVisitor::Visit(lsfs::ParameterDefinition const& decl)
{
    this->getFormatter().printIdentifier(decl.name);
    this->getFormatter().printKeyword(":");
    this->getFormatter().print(" ");

    decl.type->accept(*this);
}

void PseudocodeVisitor::Visit(lsfs::VariableDefintion const& decl)
{
    this->getFormatter().printKeyword("definuj premennú");
    this->getFormatter().print(" ");
    this->getFormatter().printIdentifier(decl.name);
    this->getFormatter().printKeyword(":");
    this->getFormatter().print(" ");
    decl.type->accept(*this);
}

// expr

void PseudocodeVisitor::Visit(lsfs::IntLiteral const& expr)
{
    this->getFormatter().printIntLiteral(std::to_string(expr.value));
}

void PseudocodeVisitor::Visit(lsfs::BinaryExpression const& expr)
{
    expr.left->accept(*this);
    this->getFormatter().print(" ");
    this->getFormatter().printOperator(
        lsfu::Helper::convertBinaryOperator(expr.op)
    );
    this->getFormatter().print(" ");
    expr.right->accept(*this);
}

void PseudocodeVisitor::Visit(lsfs::UnaryExpression const& expr)
{
    this->getFormatter().printOperator(
        lsfu::Helper::convertUnaryOperator(expr.op)
    );
    expr.arg->accept(*this);
}

void PseudocodeVisitor::Visit(lsfs::VarRefExpression const& expr)
{
    this->getFormatter().printIdentifier(expr.variable->name);
}

void PseudocodeVisitor::Visit(lsfs::ParamRefExpression const& expr)
{
    this->getFormatter().printIdentifier(expr.parameter->name);
}

void PseudocodeVisitor::Visit(lsfs::FunctionCallExpression const& expr)
{
    // this->getFormatter().print(expr.functionName + "(");
    this->getFormatter().printIdentifier(expr.functionName);
    this->getFormatter().print("(");
    for (size_t i = 0; i < expr.arguments.size(); i++)
    {
        expr.arguments[i]->accept(*this);
        if (i < expr.arguments.size() - 1)
        {
            this->getFormatter().print(", ");
        }
    }
    this->getFormatter().print(")");
}

void PseudocodeVisitor::Visit(lsfs::UnknownExpression const& expr)
{
    this->getFormatter().printError("UNKNOW EXPR (" + expr.message + ")");
}

// type
void PseudocodeVisitor::Visit(lsfs::IntType const& type)
{
    this->getFormatter().print(type.name);
}

} // namespace libastfrioutput::visitors