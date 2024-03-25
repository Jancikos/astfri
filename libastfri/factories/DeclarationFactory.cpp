#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/structures/Declaration.hpp>

namespace libastfri::factories
{
DeclarationFactory& DeclarationFactory::getInstance()
{
    static DeclarationFactory instance;

    return instance;
}

DeclarationFactory::~DeclarationFactory()
{
    for (auto* variable : variables)
    {
        delete variable;
    }
    variables.clear();

    for (auto* function : functions)
    {
        delete function;
    }
    functions.clear();
}

lsfs::VariableDefintion* DeclarationFactory::createVariable(
    std::string name,
    lsfs::Type* type,
    lsfs::Expression* value
)
{
    auto* variable = new lsfs::VariableDefintion(name, type, value);
    variables.emplace_back(variable);

    return variable;
}

lsfs::ParameterDefinition* DeclarationFactory::createParameter(
    std::string name,
    lsfs::Type* type,
    lsfs::Expression* value
)
{
    auto* parameter = new lsfs::ParameterDefinition(name, type, value);
    variables.emplace_back(parameter);

    return parameter;
}

lsfs::FunctionDefinition* DeclarationFactory::createFunction(
    std::string name,
    std::vector<lsfs::ParameterDefinition*> parameters,
    lsfs::CompoundStatement* body,
    lsfs::Type* returnType
)
{
    auto* function
        = new lsfs::FunctionDefinition(name, parameters, body, returnType);
    functions.emplace_back(function);

    return function;
}

lsfs::UknownDeclaration* DeclarationFactory::createUknownDeclaration(
    std::string message
)
{
    auto* declaration = new lsfs::UknownDeclaration(message);

    return declaration;
}

} // namespace libastfri::factories
