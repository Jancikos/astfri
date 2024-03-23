#pragma once

#include <string>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/structures/Declaration.hpp>


namespace lsfs = libastfri::structures;

namespace libastfri::factories {
class DeclarationFactory {
  public:
    static DeclarationFactory &getInstance();

  private:
    UsedList<lsfs::BaseVariableDefintion *> variables;
    UsedList<lsfs::FunctionDefinition *> functions;

    DeclarationFactory() = default;
    ~DeclarationFactory();

  public:
    lsfs::VariableDefintion *createVariable(std::string name, lsfs::Type *type,
                                      lsfs::Expression *value = nullptr);
    lsfs::ParameterDefinition *createParameter(std::string name, lsfs::Type *type,
                                         lsfs::Expression *value = nullptr);

    lsfs::FunctionDefinition *
    createFunction(std::string name,
                   std::vector<lsfs::ParameterDefinition *> parameters,
                   lsfs::CompoundStatement *body, lsfs::Type *returnType);

    lsfs::UknownDeclaration *createUknownDeclaration(std::string message);

    DeclarationFactory(DeclarationFactory const &) = delete;
    void operator=(DeclarationFactory const &) = delete;
};
} // namespace libastfri::factories
