#include "FunctionFactory.hpp"

namespace libastfri::factories {
    FunctionFactory& FunctionFactory::getInstance() 
    {
        static FunctionFactory instance;

        return instance;
    }

    FunctionFactory::FunctionFactory() 
    {
    }

    FunctionFactory::~FunctionFactory() 
    {
        for (auto* variable : variables) 
        {
            delete variable;
        }
        variables.clear();
    }

    VariableDefintion* FunctionFactory::createVariable(std::string name, Type* type, Expression* value) {
        auto* variable = new VariableDefintion{{name, type, value}};
        variables.emplace_back(variable);

        return variable;
    }

    ParameterDefinition* FunctionFactory::createParameter(std::string name, Type* type, Expression* value) {
        auto* parameter = new ParameterDefinition{{name, type, value}};
        variables.emplace_back(parameter);

        return parameter;
    }

    FunctionDefinition* FunctionFactory::createFunction(std::string name, std::vector<ParameterDefinition*> parameters, CompoundStatement* body, Type* returnType) {
        functions.emplace_back(FunctionDefinition{name, parameters, body, returnType});

        return &functions.back();
    }
}
