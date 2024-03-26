#pragma once

#include <libastfri/utils/OutputVisitor.hpp>
#include <string>

namespace libastfri::structures
{
// typ
struct Type
{
    std::string name;

    Type(std::string name);
};

//// primitivne typy
struct PrimitiveType : Type
{
    PrimitiveType(std::string name);
};

struct IntType : PrimitiveType, utils::OutputVisitable<IntType>
{
    IntType();
};

struct FloatType : PrimitiveType, utils::OutputVisitable<FloatType>
{
    FloatType();
};

struct CharType : PrimitiveType, utils::OutputVisitable<CharType>
{
    CharType();
};

struct BoolType : PrimitiveType, utils::OutputVisitable<BoolType>
{
    BoolType();
};

struct VoidType : PrimitiveType, utils::OutputVisitable<VoidType>
{
    VoidType();
};

//// uzivatelske typy
struct UserType : Type, utils::OutputVisitable<UserType>
{
    UserType(std::string name);
};
} // namespace libastfri::structures