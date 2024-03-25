#pragma once

#include <string>
#include <vector>

namespace libastfri::structures
{
struct Type;
struct Expression;
struct CompoundStatement;

struct Declaration
{
};

// zaklad, ktory sa pouziva pri definiciach premennych, parametrov, atributov,
// atd.
struct BaseVariableDefintion : Declaration
{
    std::string name;
    Type* type;
    Expression* value;

    BaseVariableDefintion(
        std::string name,
        Type* type,
        Expression* value = nullptr
    );
};

// premenna
struct VariableDefintion : BaseVariableDefintion
{
    VariableDefintion(
        std::string name,
        Type* type,
        Expression* value = nullptr
    );
};

// parameter
struct ParameterDefinition : BaseVariableDefintion
{
    ParameterDefinition(
        std::string name,
        Type* type,
        Expression* value = nullptr
    );
};

// funkcia
struct FunctionDefinition : Declaration
{
    std::string name;
    std::vector<ParameterDefinition*> parameters;
    CompoundStatement* body;
    Type* returnType;

    FunctionDefinition(
        std::string name,
        std::vector<ParameterDefinition*> parameters,
        CompoundStatement* body,
        Type* returnType
    );
};

struct UknownDeclaration : Declaration
{
    std::string message;

    UknownDeclaration(std::string message);
};

} // namespace libastfri::structures