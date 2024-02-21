#include <iostream>

#include "../libastfri/AstNode.h"
#include "../libastfri/AstTypes.hpp"

using namespace libastrfi;

int main ()
{
    FunctionDefinition function;

    function.name = "addition";


    ParameterDefinction paramA;
    paramA.name = "a";
    paramA.type = (IntPrimitiveType)
    ParameterDefinction paramB;
    paramA.name = "b";
    paramA.type = (IntPrimitiveType)

    function.parameters.push(paramA);
    function.parameters.push(paramB);


    ReturnType<IntPrimitiveType> retType;
    retType.exp = // var value return expression



    return 0;
}

int addition(int a, int b)
{
    int c = a + b;

    return c;
}