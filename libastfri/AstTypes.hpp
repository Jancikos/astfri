

namespace libastfri
{    
    // "riadok" v kode
    struct Statement
    {

    };
    
    struct AssigmentStatement 
    {
        Variable left;
        expression right;
    };


    // vyraz
    struct Expression
    {

    };

    // typ
    struct Type<T>
    {
        T value;
    };
    struct PrimitiveType<T> : Type<T>
    {
        std::string name;
    };
    struct UserType<T> : Type<T>
    {
        std::string name;
    };

    //// primitivne typy
    struct IntPrimitiveType : PrimitiveType<int>
    {
        int value;
    }
    
    //// navratovy typ
    struct ReturnType<T>
    {
        T type;
        Expression exp;
    }

    // parameter
    struct ParameterDefinition
    {
        std::string name;
        Type type;
        std::string defaultValue;
        bool nullable;
    };

    
    struct FunctionDefinition
    {
        std::string name;
        std::vector<ParameterDefinition> parameters;
        std::vector<Statement> body;
        Type returnType;
    };
}