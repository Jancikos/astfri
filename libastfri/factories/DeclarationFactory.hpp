#pragma once

#include <libastfri/factories/ExpressionFactory.hpp>
#include <string>

#include <libastfri/structures/Declaration.hpp>

using namespace libastfri::structures;

namespace libastfri::factories {
class DeclarationFactory {
  public:
    static DeclarationFactory &getInstance();

  private:
    UsedList<BaseVariableDefintion *> variables;
    UsedList<FunctionDefinition *> functions;

    DeclarationFactory();
    ~DeclarationFactory();

  public:
    VariableDefintion *createVariable(std::string name, Type *type,
                                      Expression *value = nullptr);
    ParameterDefinition *createParameter(std::string name, Type *type,
                                         Expression *value = nullptr);

    FunctionDefinition *
    createFunction(std::string name,
                   std::vector<ParameterDefinition *> parameters,
                   CompoundStatement *body, Type *returnType);

    DeclarationFactory(DeclarationFactory const &) = delete;
    void operator=(DeclarationFactory const &) = delete;
};
} // namespace libastfri::factories
