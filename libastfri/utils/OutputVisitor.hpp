#pragma once

namespace libastfri::structures
{
    // stmt
    struct TranslationUnit;
    struct CompoundStatement;
    struct DeclarationStatement;
    struct DeclarationAndAssignmentStatement;
    struct ReturnStatement;
    struct ExpressionStatement;
    struct IfStatement;
    struct WhileLoopStatement;
    struct DoWhileLoopStatement;
    struct ForLoopStatement;
    struct UnknownStatement;

    // expr
    struct IntLiteral;
    struct FloatLiteral;
    struct CharLiteral;
    struct StringLiteral;
    struct BoolLiteral;
    struct ConstLiteral;
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
    struct IntType;
    struct FloatType;
    struct CharType;
    struct BoolType;
    struct VoidType;
    struct UserType;
}

namespace libastfri::utils
{
// sem definovat len hlavicky, prehliadku nechat na implementacii
class IOutputVisitor
{
    public:

    // stmt
    virtual void Visit(const structures::TranslationUnit& stmt) = 0;
    virtual void Visit(const structures::CompoundStatement& stmt) = 0;
    virtual void Visit(const structures::DeclarationStatement& stmt) = 0;
    virtual void Visit(const structures::DeclarationAndAssignmentStatement& stmt) = 0;
    virtual void Visit(const structures::ReturnStatement& stmt) = 0;
    virtual void Visit(const structures::ExpressionStatement& stmt) = 0;
    virtual void Visit(const structures::IfStatement& stmt) = 0;
    virtual void Visit(const structures::WhileLoopStatement& stmt) = 0;
    virtual void Visit(const structures::DoWhileLoopStatement& stmt) = 0;
    virtual void Visit(const structures::ForLoopStatement& stmt) = 0;
    virtual void Visit(const structures::UnknownStatement& stmt) = 0;

    // expr
    virtual void Visit(const structures::IntLiteral& expr) = 0;
    virtual void Visit(const structures::FloatLiteral& expr) = 0;
    virtual void Visit(const structures::CharLiteral& expr) = 0;
    virtual void Visit(const structures::StringLiteral& expr) = 0;
    virtual void Visit(const structures::BoolLiteral& expr) = 0;
    virtual void Visit(const structures::ConstLiteral& expr) = 0;
    virtual void Visit(const structures::BinaryExpression& expr) = 0;
    virtual void Visit(const structures::UnaryExpression& expr) = 0;
    virtual void Visit(const structures::ParamRefExpression& expr) = 0;
    virtual void Visit(const structures::VarRefExpression& expr) = 0;
    virtual void Visit(const structures::FunctionCallExpression& expr) = 0;
    virtual void Visit(const structures::UnknownExpression& expr) = 0;

    // decl
    virtual void Visit(const structures::VariableDefintion& decl) = 0;
    virtual void Visit(const structures::ParameterDefinition& decl) = 0;
    virtual void Visit(const structures::FunctionDefinition& decl) = 0;
    virtual void Visit(const structures::UknownDeclaration& decl) = 0;

    // type
    virtual void Visit(const structures::IntType& type) = 0;
    virtual void Visit(const structures::FloatType& type) = 0;
    virtual void Visit(const structures::CharType& type) = 0;
    virtual void Visit(const structures::BoolType& type) = 0;
    virtual void Visit(const structures::VoidType& type) = 0;
    virtual void Visit(const structures::UserType& type) = 0;
    
};

class IOutputVisitable
{

public:
    virtual void accept (IOutputVisitor* visitor) = 0;
    virtual ~IOutputVisitable()                   = default;
};

// trieda pre implementaciu CRTP patternu
template<typename VisitableStruct>
struct OutputVisitable : public IOutputVisitable
{
    void accept(IOutputVisitor* visitor) override
    {
        // TOOD - preco je prva moznost horsia? (const ?)
        // visitor->Visit(*static_cast<VisitableStruct*>(this));
        visitor->Visit(static_cast<VisitableStruct const&>(*this));
    }
};

} // namespace libastfri::utils