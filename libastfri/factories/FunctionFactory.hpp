#pragma once

#include "libastfri/factories/ExpressionFactory.hpp"
#include <string>

#include <libastfri/structures/Function.hpp>

using namespace libastfri::structures;

namespace libastfri::factories {
    class FunctionFactory
    {
        public:
            static FunctionFactory& getInstance();

        private:
            UsedList<BaseVariableDefintion*> variables;
            UsedList<FunctionDefinition> functions;

            FunctionFactory ();
            ~FunctionFactory ();
        public:
            VariableDefintion* createVariable (std::string name, Type* type, Expression* value=nullptr);
            ParameterDefinition* createParameter (std::string name, Type* type, Expression* value=nullptr);

            FunctionDefinition* createFunction (std::string name, std::vector<ParameterDefinition*> parameters, CompoundStatement* body, Type* returnType);


            FunctionFactory(FunctionFactory const&) = delete;
            void operator=(FunctionFactory const&) = delete;
    };
}

