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
    virtual void Visit (structures::TranslationUnit const& stmt) override
    {
    }

    virtual void Visit (structures::CompoundStatement const& stmt) override
    {
    }

    virtual void Visit (structures::DeclarationStatement const& stmt) override
    {
    }

    virtual void Visit (structures::DeclarationAndAssigmentStatement const& stmt
    ) override
    {
    }

    virtual void Visit (structures::ReturnStatement const& stmt) override
    {
    }

    virtual void Visit (structures::ExpressionStatement const& stmt) override
    {
    }

    virtual void Visit (structures::IfStatement const& stmt) override
    {
    }

    virtual void Visit (structures::WhileStatement const& stmt) override
    {
    }

    virtual void Visit (structures::DoWhileStatement const& stmt) override
    {
    }

    virtual void Visit (structures::ForStatement const& stmt) override
    {
    }

    virtual void Visit (structures::UnknownStatement const& stmt) override
    {
    }

    // expr
    virtual void Visit (structures::IntLiteral const& expr) override
    {
    }

    virtual void Visit (structures::FloatLiteral const& expr) override
    {
    }

    virtual void Visit (structures::CharLiteral const& expr) override
    {
    }

    virtual void Visit (structures::StringLiteral const& expr) override
    {
    }

    virtual void Visit (structures::BoolLiteral const& expr) override
    {
    }

    virtual void Visit (structures::BinaryExpression const& expr) override
    {
    }

    virtual void Visit (structures::UnaryExpression const& expr) override
    {
    }

    virtual void Visit (structures::ParamRefExpression const& expr) override
    {
    }

    virtual void Visit (structures::VarRefExpression const& expr) override
    {
    }

    virtual void Visit (structures::FunctionCallExpression const& expr) override
    {
    }

    virtual void Visit (structures::UnknownExpression const& expr) override
    {
    }

    // decl
    virtual void Visit (structures::VariableDefintion const& decl) override
    {
    }

    virtual void Visit (structures::ParameterDefinition const& decl) override
    {
    }

    virtual void Visit (structures::FunctionDefinition const& decl) override
    {
    }

    virtual void Visit (structures::UknownDeclaration const& decl) override
    {
    }

    // type
    virtual void Visit (structures::Type const& type) override
    {
    }

    virtual void Visit (structures::IntType const& type) override
    {
    }

    virtual void Visit (structures::FloatType const& type) override
    {
    }

    virtual void Visit (structures::CharType const& type) override
    {
    }

    virtual void Visit (structures::BoolType const& type) override
    {
    }

    virtual void Visit (structures::VoidType const& type) override
    {
    }

    virtual void Visit (structures::UserType const& type) override
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