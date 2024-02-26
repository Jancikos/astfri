#include <libastfri/structures/Function.hpp>

using namespace libastfri::structures;

int main ()
{
    
    std::vector<ParameterDefinition*> params;
    params.push_back(new ParameterDefinition("a", new IntType()));
    params.push_back(new ParameterDefinition("b", new IntType()));

    auto variableC = new Variable("c", new IntType());

    auto body = new CompoundStatement();
    body->statements.push_back(
        new AssigmentStatement(
            variableC, 
            new BinaryExpression(
                new VarRefExpression(params[0]->variable), 
                BinaryOperators::Add, 
                new VarRefExpression(params[1]->variable)
            )
        )
    );
    body->statements.push_back(
        new ReturnStatement(
            new VarRefExpression(variableC)
        )
    );

    auto retType = new IntType();

    auto function = new FunctionDefinition("addition", params, body, retType);

    return 0;
}

int addition(int a, int b)
{
    int c = a + b;

    // pirdat if

    // pridat while

    // volanie funkcie

    return c;
}