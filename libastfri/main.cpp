#include "libastfri/structures/Expression.hpp"
#include <iostream>
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
    body->statements.push_back(
        new IfStatement(
            new BinaryExpression(
                new VarRefExpression(variableC),
                BinaryOperators::Less,
                new IntLiteral(0)
            ),
            new CompoundStatement(
                {
                    new FunctionCallStatement(
                        "std::cout",
                        {
                            new StringLiteral("c is less than 0"),
                            new ConstLiteral("std::endl")
                        }
                    ),
                    new AssigmentStatement(
                        variableC,
                        new IntLiteral(0)
                    )
                }
            )
        )
    );

    auto retType = new IntType();

    auto function = new FunctionDefinition("addition", params, body, retType);

    return 0;
}

int addition(int a, int b)
{
    int c = a + b;

    if (c < 0)
    {
        std::cout << "c is less than 0" << std::endl;
        c = 0;
    }

    // pridat while

    return c;
}