#pragma once

#include <string>

#include <libastfri/structures/Statement.hpp>

namespace libastfri::structures
{
    struct FunctionDefinition
    {
        std::string name;
        std::vector<ParameterDefinition*> parameters;
        CompoundStatement* body;
        Type* returnType;

        FunctionDefinition (std::string name, std::vector<ParameterDefinition*> parameters, CompoundStatement* body, Type* returnType) : name(name), parameters(parameters), body(body), returnType(returnType) {}
    };
}