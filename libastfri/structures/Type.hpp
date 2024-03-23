#pragma once

#include <string>

namespace libastfri::structures {
// typ
struct Type {
    std::string name;

    Type(std::string name);
};

//// primitivne typy
struct PrimitiveType : Type {
    PrimitiveType(std::string name);
};

struct IntType : PrimitiveType {
    IntType();
};
struct FloatType : PrimitiveType {
    FloatType();
};
struct CharType : PrimitiveType {
    CharType();
};
struct BoolType : PrimitiveType {
    BoolType();
};
struct VoidType : PrimitiveType {
    VoidType();
};

//// uzivatelske typy
struct UserType : Type {
    UserType(std::string name);
};
} // namespace libastfri::structures