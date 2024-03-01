#include <iostream>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>
#include <libastfri/structures/Function.hpp>

using namespace libastfri::structures;
using namespace libastfri::factories;

int main() {
  auto &typeFac = TypeFactory::getInstance();
  auto &literalFac = LiteralFactory::getInstance();

  std::vector<ParameterDefinition *> params;
  params.push_back(new ParameterDefinition("a", typeFac.getIntType()));
  params.push_back(new ParameterDefinition("b", typeFac.getIntType()));

  auto variableC = new Variable("c", typeFac.getIntType());
  auto variableRepMultiplier =
      new Variable("repMultiplier", typeFac.getIntType());
  auto variableRepCount = new Variable("repCount", typeFac.getIntType());

  auto body = new CompoundStatement(
      {new DeclarationAndAssigmentStatement(
           variableC,
           new BinaryExpression(new VarRefExpression(params[0]->variable),
                                BinaryOperators::Add,
                                new VarRefExpression(params[1]->variable))),
       new DeclarationAndAssigmentStatement(variableRepMultiplier,
                                            literalFac.getIntLiteral(1)),
       new IfStatement(
           new BinaryExpression(new VarRefExpression(variableC),
                                BinaryOperators::Less,
                                literalFac.getIntLiteral(0)),
           new CompoundStatement({new AssigmentStatement(
               variableRepMultiplier, literalFac.getIntLiteral(-1))})),
       new DeclarationAndAssigmentStatement(variableRepCount,
                                            literalFac.getIntLiteral(0)),
       new WhileLoopStatement(
           new BinaryExpression(
               new BinaryExpression(new VarRefExpression(variableC),
                                    BinaryOperators::Add,
                                    new VarRefExpression(variableRepCount)),
               BinaryOperators::Less, literalFac.getIntLiteral(0)),
           new CompoundStatement({new AssigmentStatement(
               variableRepCount,
               new BinaryExpression(
                   new VarRefExpression(variableRepCount), BinaryOperators::Add,
                   new VarRefExpression(variableRepMultiplier)))})),
       new FunctionCallStatement("std::cout",
                                 {new StringLiteral("c is "),
                                  new VarRefExpression(variableC),
                                  new StringLiteral(" and it was update "),
                                  new VarRefExpression(variableRepCount),
                                  new StringLiteral(" times to have value 0"),
                                  new ConstLiteral("std::endl")}),
       new ReturnStatement(new VarRefExpression(variableC))});

  auto retType = typeFac.getIntType();

  auto function =
      new FunctionDefinition("brutalAddition", params, body, retType);

  return 0;
}

int brutalAddition(int a, int b) {
  int c = a + b;
  int repMultiplier = 1;

  if (c < 0) {
    repMultiplier = -1;
  }

  int repCount = 0;
  while (c + repCount < 0) {
    repCount += repMultiplier;
  }

  std::cout << "c is " << c << " and it was update " << repCount
            << " times to have value 0" << std::endl;

  return c;
}