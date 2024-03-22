#pragma once

#include <map>
#include <string>

#include <libastfri/structures/Type.hpp>

using namespace libastfri::structures;

namespace libastfri::factories {
class TypeFactory {
  public:
    static TypeFactory &getInstance();

  private:
    IntType intType;
    FloatType floatType;
    CharType charType;
    BoolType boolType;
    VoidType voidType;

    std::map<std::string, UserType> userTypes;
    TypeFactory();

  public:
    IntType *getIntType();
    FloatType *getFloatType();
    CharType *getCharType();
    BoolType *getBoolType();
    VoidType *getVoidType();

    UserType *getUserType(std::string name);

    TypeFactory(TypeFactory const &) = delete;
    void operator=(TypeFactory const &) = delete;
};
} // namespace libastfri::factories
