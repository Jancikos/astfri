#include <iostream>

#include "../libastfri/AstNode.h"

using namespace libastrfi;

int main ()
{
    // expression: 5 + 10

    AstNode val5(AstNodeType::Constant, "5");
    AstNode val10(AstNodeType::Constant, "10");

    AstNode plus(AstNodeType::Expression, "+", &val5, &val10);

    std::cout << plus.getLeft()->getValue() << " " << plus.getValue() << " " << plus.getRight()->getValue() << std::endl;

    return 0;
}