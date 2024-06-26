#pragma once

#include <libastfri/structures/Type.hpp>

#include <map>
#include <string>

namespace lsfs = libastfri::structures;

namespace libastfri::factories
{
class TypeFactory
{
public:
    static TypeFactory& getInstance ();

private:
    lsfs::IntType intType;
    lsfs::FloatType floatType;
    lsfs::CharType charType;
    lsfs::BoolType boolType;
    lsfs::VoidType voidType;

    std::map<std::string, lsfs::UserType> userTypes;

    TypeFactory()  = default;
    ~TypeFactory() = default;

public:
    lsfs::IntType* getIntType ();
    lsfs::FloatType* getFloatType ();
    lsfs::CharType* getCharType ();
    lsfs::BoolType* getBoolType ();
    lsfs::VoidType* getVoidType ();

    lsfs::UserType* getUserType (std::string name);

    TypeFactory(TypeFactory const&)     = delete;
    void operator= (TypeFactory const&) = delete;
};
} // namespace libastfri::factories
