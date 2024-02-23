// #include <libastfri/AstTypes.hpp> // - nejde m to takto includnut 
#include "AstTypes.hpp"

using namespace libastfri;

int main ()
{
    
    std::vector<ParameterDefinition*> params;
    params.push_back(new ParameterDefinition("a", new IntType()));
    params.push_back(new ParameterDefinition("b", new IntType()));

    auto variableC = new Variable("c", new IntType());

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

    auto retType = new ReturnType(new IntType(), new UnaryExpression(UnaryOperators::GetValue, variableC));

    auto function = new FunctionDefinition("addition", params, body, retType);

    return 0;
}

int addition(int a, int b)
{
    int c = a + b;

    int d = 4;

    return c;
}