#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/structures/Declaration.hpp>

namespace libastfri::factories {
DeclarationFactory &DeclarationFactory::getInstance() {
    static DeclarationFactory instance;

    return instance;
}

DeclarationFactory::DeclarationFactory() {}

DeclarationFactory::~DeclarationFactory() {
    for (auto *variable : variables) {
        delete variable;
    }
    variables.clear();
}

VariableDefintion *DeclarationFactory::createVariable(std::string name, Type *type,
                                                   Expression *value) {
    auto *variable = new VariableDefintion{{{}, name, type, value}};
    variables.emplace_back(variable);

    return variable;
}

ParameterDefinition *DeclarationFactory::createParameter(std::string name,
                                                      Type *type,
                                                      Expression *value) {
    auto *parameter = new ParameterDefinition{{{}, name, type, value}};
    variables.emplace_back(parameter);

    return parameter;
}

FunctionDefinition *
DeclarationFactory::createFunction(std::string name,
                                std::vector<ParameterDefinition *> parameters,
                                CompoundStatement *body, Type *returnType) {
    auto *function =
        new FunctionDefinition{{}, name, parameters, body, returnType};
    functions.emplace_back(function);

    return function;
}

UknownDeclaration *DeclarationFactory::createUknownDeclaration(std::string message) {
    auto *declaration = new UknownDeclaration{{}, message};

    return declaration;
}

} // namespace libastfri::factories
