#pragma once

#include <string>

#include <libastfri/structures/Type.hpp>
#include <libastfri/structures/Expression.hpp>

namespace libastfri::structures
{    
    // premenna
    struct Variable
    {
        std::string name;
        Type* type;
        Expression* value;

        Variable (std::string name, Type* type) : name(name), type(type), value(nullptr) {}
        Variable (std::string name, Type* type , Expression* value) : name(name), type(type), value(value) {}
    };


    // parameter
    struct ParameterDefinition
    {
        Variable* variable;
        
        ParameterDefinition (std::string name, Type* type) : variable(new Variable(name, type)) {}
        ParameterDefinition (std::string name, Type* type, Expression* defaultValue) : variable(new Variable(name, type, defaultValue)) {}
    };

}