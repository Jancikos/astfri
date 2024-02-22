// #include <libastfri/AstTypes.hpp> // - nejde m to takto includnut 
#include "AstTypes.hpp"

using namespace libastfri;

int main ()
{
    
    std::vector<ParameterDefinition*> params;
    params.push_back(new ParameterDefinition("a", new PrimitiveType("int")));
    params.push_back(new ParameterDefinition("b", new PrimitiveType("int")));


    auto variableC = new Variable("c", new PrimitiveType("int"));

    std::vector<Statement*> body;
    body.push_back(
        new AssigmentStatement(
            variableC, 
            new BinaryExpression(
                new UnaryExpression(UnaryOperators::GetValue, params[0]->variable), 
                BinaryOperators::Add, 
                new UnaryExpression(UnaryOperators::GetValue, params[1]->variable)
            )
        )
    );

    auto retType = new ExpressionReturnType(new PrimitiveType("int"), new UnaryExpression(UnaryOperators::GetValue, variableC));

    auto function = new FunctionDefinition("addition", params, body, retType);

    return 0;
}

int addition(int a, int b)
{
    int c = a + b;

    return c;
}