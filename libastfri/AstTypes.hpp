
#include <string>
#include <variant>
#include <vector>

namespace libastfri
{    
    // typ
    struct Type
    {
        // TODO - vytiahnut sem name
    };

    // vyraz
    struct Expression
    {

    };

    // premenna
    struct Variable
    {
        std::string name;
        Type* type;
        Expression* defaultValue;

        Variable (std::string name, Type* type) : name(name), type(type), defaultValue(nullptr) {}
        Variable (std::string name, Type* type , Expression* defaultValue) : name(name), type(type), defaultValue(defaultValue) {}
    };

    //// konstaty (literals) pouzivane v vyrazoch
    struct IntLiteral
    {
        int value;
    };

    //// operatory pouzivane v vyrazoch
    enum class BinaryOperators
    {
        Add, Subtract, Multiply, Divide, Modulo
    };
    enum class UnaryOperators
    {
        Not, Negative,
        GetValue
    };

    //// vyrazy
    struct BinaryExpression : Expression 
    {
        Expression* left;
        BinaryOperators op;
        Expression* right;

        BinaryExpression (Expression* left, BinaryOperators op, Expression* right) : left(left), op(op), right(right) {} 
    };
    struct UnaryExpression : Expression
    {
        using ArgVariant = std::variant<Expression*, Variable*>;
      
        UnaryOperators op;
        ArgVariant arg;

        UnaryExpression (UnaryOperators op, Expression* arg) : op(op), arg(arg) {}
        UnaryExpression (UnaryOperators op, Variable* arg) : op(op), arg(arg) {}
    };


    // "riadok" v kode
    struct Statement
    {

    };
    
    struct AssigmentStatement : Statement
    {
        Variable* left;
        Expression* right;

        AssigmentStatement (Variable* left, Expression* right) : left(left), right(right) {}
    };

    // FucntionCall statement


    // typy
    struct PrimitiveType : Type
    {
        std::string name;

        PrimitiveType (std::string name) : name(name) {}
    };
    struct UserType : Type
    {
        std::string name;

        UserType (std::string name) : name(name) {}
    };

    //// primitivne typy
    // vymenovat ich rucne ??
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

    //// navratovy typ
    struct ReturnType
    {
        Type* type;
        Expression* expression;

        ReturnType (Type* type, Expression* expression) : type(type), expression(expression) {}
    };

    // parameter
    struct ParameterDefinition
    {
        Variable* variable;
        
        ParameterDefinition (std::string name, Type* type) : variable(new Variable(name, type)) {}
        ParameterDefinition (std::string name, Type* type, Expression* defaultValue) : variable(new Variable(name, type, defaultValue)) {}
    };

    struct FunctionDefinition
    {
        std::string name;
        std::vector<ParameterDefinition*> parameters;
        std::vector<Statement*> body;
        ReturnType* returnType;

        FunctionDefinition (std::string name, std::vector<ParameterDefinition*> parameters, std::vector<Statement*> body, ReturnType* returnType) : name(name), parameters(parameters), body(body), returnType(returnType) {}
    };
}