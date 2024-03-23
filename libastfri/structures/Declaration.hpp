#pragma once

#include <string>
#include <vector>

namespace libastfri::structures {
struct Type;
struct Expression;
struct CompoundStatement;

struct Declaration {};

// zaklad, ktory sa pouziva pri definiciach premennych, parametrov, atributov,
// atd.
struct BaseVariableDefintion : Declaration {
    std::string name;
    Type *type;
    Expression *value;
};

// premenna
struct VariableDefintion : BaseVariableDefintion {};

// parameter
struct ParameterDefinition : BaseVariableDefintion {};

// funkcia
struct FunctionDefinition : Declaration {
    std::string name;
    std::vector<ParameterDefinition *> parameters;
    CompoundStatement *body;
    Type *returnType;
};


struct UknownDeclaration : Declaration {
    std::string message;
};

} // namespace libastfri::structures