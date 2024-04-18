#pragma once
namespace libastfri::structures
{
// stmt
struct TranslationUnit;
struct CompoundStatement;
struct DeclarationStatement;
struct DeclarationAndAssigmentStatement;
struct ReturnStatement;
struct ExpressionStatement;
struct IfStatement;
struct WhileStatement;
struct DoWhileStatement;
struct ForStatement;
struct UnknownStatement;

// expr
struct IntLiteral;
struct FloatLiteral;
struct CharLiteral;
struct StringLiteral;
struct BoolLiteral;
struct BinaryExpression;
struct UnaryExpression;
struct ParamRefExpression;
struct VarRefExpression;
struct FunctionCallExpression;
struct UnknownExpression;

// decl
struct VariableDefintion;
struct ParameterDefinition;
struct FunctionDefinition;
struct UknownDeclaration;

// type
struct Type;
struct IntType;
struct FloatType;
struct CharType;
struct BoolType;
struct VoidType;
struct UserType;
} // namespace libastfri::structures

namespace libastfri::utils
{

class IOutputFormatter;
class IOutputWriter;


// sem definovat len hlavicky, prehliadku nechat na implementacii
class IOutputVisitor
{
public:
    // utils
    virtual IOutputFormatter& getFormatter () = 0;

    // stmt
    virtual void Visit (structures::TranslationUnit const& stmt)      = 0;
    virtual void Visit (structures::CompoundStatement const& stmt)    = 0;
    virtual void Visit (structures::DeclarationStatement const& stmt) = 0;
    virtual void Visit (structures::DeclarationAndAssigmentStatement const& stmt
    )                                                                 = 0;
    virtual void Visit (structures::ReturnStatement const& stmt)      = 0;
    virtual void Visit (structures::ExpressionStatement const& stmt)  = 0;
    virtual void Visit (structures::IfStatement const& stmt)          = 0;
    virtual void Visit (structures::WhileStatement const& stmt)   = 0;
    virtual void Visit (structures::DoWhileStatement const& stmt) = 0;
    virtual void Visit (structures::ForStatement const& stmt)     = 0;
    virtual void Visit (structures::UnknownStatement const& stmt)     = 0;

    // expr
    virtual void Visit (structures::IntLiteral const& expr)             = 0;
    virtual void Visit (structures::FloatLiteral const& expr)           = 0;
    virtual void Visit (structures::CharLiteral const& expr)            = 0;
    virtual void Visit (structures::StringLiteral const& expr)          = 0;
    virtual void Visit (structures::BoolLiteral const& expr)            = 0;
    virtual void Visit (structures::BinaryExpression const& expr)       = 0;
    virtual void Visit (structures::UnaryExpression const& expr)        = 0;
    virtual void Visit (structures::ParamRefExpression const& expr)     = 0;
    virtual void Visit (structures::VarRefExpression const& expr)       = 0;
    virtual void Visit (structures::FunctionCallExpression const& expr) = 0;
    virtual void Visit (structures::UnknownExpression const& expr)      = 0;

    // decl
    virtual void Visit (structures::VariableDefintion const& decl)   = 0;
    virtual void Visit (structures::ParameterDefinition const& decl) = 0;
    virtual void Visit (structures::FunctionDefinition const& decl)  = 0;
    virtual void Visit (structures::UknownDeclaration const& decl)   = 0;

    // type
    virtual void Visit (structures::Type const& type)      = 0;
    virtual void Visit (structures::IntType const& type)   = 0;
    virtual void Visit (structures::FloatType const& type) = 0;
    virtual void Visit (structures::CharType const& type)  = 0;
    virtual void Visit (structures::BoolType const& type)  = 0;
    virtual void Visit (structures::VoidType const& type)  = 0;
    virtual void Visit (structures::UserType const& type)  = 0;

    virtual ~IOutputVisitor()                              = default;
};

class OutputVisitorAdapter : public IOutputVisitor
{
public:
    OutputVisitorAdapter() = default;

    // stmt
    virtual void Visit (structures::TranslationUnit const&) override
    {
    }

    virtual void Visit (structures::CompoundStatement const&) override
    {
    }

    virtual void Visit (structures::DeclarationStatement const&) override
    {
    }

    virtual void Visit (structures::DeclarationAndAssigmentStatement const&
    ) override
    {
    }

    virtual void Visit (structures::ReturnStatement const&) override
    {
    }

    virtual void Visit (structures::ExpressionStatement const&) override
    {
    }

    virtual void Visit (structures::IfStatement const&) override
    {
    }

    virtual void Visit (structures::WhileStatement const&) override
    {
    }

    virtual void Visit (structures::DoWhileStatement const&) override
    {
    }

    virtual void Visit (structures::ForStatement const&) override
    {
    }

    virtual void Visit (structures::UnknownStatement const&) override
    {
    }

    // expr
    virtual void Visit (structures::IntLiteral const&) override
    {
    }

    virtual void Visit (structures::FloatLiteral const&) override
    {
    }

    virtual void Visit (structures::CharLiteral const&) override
    {
    }

    virtual void Visit (structures::StringLiteral const&) override
    {
    }

    virtual void Visit (structures::BoolLiteral const&) override
    {
    }

    virtual void Visit (structures::BinaryExpression const&) override
    {
    }

    virtual void Visit (structures::UnaryExpression const&) override
    {
    }

    virtual void Visit (structures::ParamRefExpression const&) override
    {
    }

    virtual void Visit (structures::VarRefExpression const&) override
    {
    }

    virtual void Visit (structures::FunctionCallExpression const&) override
    {
    }

    virtual void Visit (structures::UnknownExpression const&) override
    {
    }

    // decl
    virtual void Visit (structures::VariableDefintion const&) override
    {
    }

    virtual void Visit (structures::ParameterDefinition const&) override
    {
    }

    virtual void Visit (structures::FunctionDefinition const&) override
    {
    }

    virtual void Visit (structures::UknownDeclaration const&) override
    {
    }

    // type
    virtual void Visit (structures::Type const&) override
    {
    }

    virtual void Visit (structures::IntType const&) override
    {
    }

    virtual void Visit (structures::FloatType const&) override
    {
    }

    virtual void Visit (structures::CharType const&) override
    {
    }

    virtual void Visit (structures::BoolType const&) override
    {
    }

    virtual void Visit (structures::VoidType const&) override
    {
    }

    virtual void Visit (structures::UserType const&) override
    {
    }
};

class IOutputVisitable
{

public:
    virtual void accept (IOutputVisitor& visitor) = 0;
    virtual ~IOutputVisitable()                   = default;
};

// trieda pre implementaciu CRTP patternu
template<typename VisitableStruct>
struct OutputVisitable : virtual public IOutputVisitable
{
    void accept (IOutputVisitor& visitor) override
    {
        visitor.Visit(static_cast<VisitableStruct const&>(*this));
    }
};

} // namespace libastfri::utils