
#include <string>

namespace libastfri::structures
{    
    // typ
    struct Type
    {
        std::string name;

        Type (std::string name) : name(name) {}
    };

    //// primitivne typy
    struct PrimitiveType : Type
    {
        PrimitiveType (std::string name) : Type(name) {}
    };

    struct IntType : PrimitiveType
    {
        IntType () : PrimitiveType("int") {}
    };
    struct FloatType : PrimitiveType
    {
        FloatType () : PrimitiveType("float") {}
    };
    struct CharType : PrimitiveType
    {
        CharType () : PrimitiveType("char") {}
    };
    struct BoolType : PrimitiveType
    {
        BoolType () : PrimitiveType("bool") {}
    };
    struct VoidType : PrimitiveType
    {
        VoidType () : PrimitiveType("void") {}
    };

    //// uzivatelske typy
    struct UserType : Type
    {
        UserType (std::string name) : Type(name) {}
    };
}