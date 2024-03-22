#pragma once

#include <string>
#include <vector>

namespace libastfri::structures {
struct Type;
struct Expression;
struct CompoundStatement;

// zaklad, ktory sa pouziva pri definiciach premennych, parametrov, atributov,
// atd.
struct BaseVariableDefintion {
    std::string name;
    Type *type;
    Expression *value;
};

// premenna
struct VariableDefintion : BaseVariableDefintion {};

// parameter
struct ParameterDefinition : BaseVariableDefintion {};

// funkcia
struct FunctionDefinition {
    std::string name;
    std::vector<ParameterDefinition *> parameters;
    CompoundStatement *body;
    Type *returnType;
};
} // namespace libastfri::structures