#include <iostream>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/FunctionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

using namespace libastfri::structures;
using namespace libastfri::factories;

int main() {
  auto &typeFac = TypeFactory::getInstance();
  auto &literalFac = LiteralFactory::getInstance();
  auto &statementFac = StatementFactory::getInstance();
  auto &expressionFac = ExpressionFactory::getInstance();
  auto &referenceFac = ReferenceFactory::getInstance();
  auto &functionFac = FunctionFactory::getInstance();

  std::vector<ParameterDefinition *> params;
  params.push_back(functionFac.createParameter("a", typeFac.getIntType()));
  params.push_back(functionFac.createParameter("b", typeFac.getIntType()));

  auto variableC = functionFac.createVariable("c", typeFac.getIntType());
  auto variableRepMultiplier =
      functionFac.createVariable("repMultiplier", typeFac.getIntType());
  auto variableRepCount =
      functionFac.createVariable("repCount", typeFac.getIntType());

  auto body = statementFac.createCompoundStatement(
      {statementFac.createDeclarationAndAssigmentStatement(
           variableC, expressionFac.createBinaryExpression(
                          BinaryOperators::Add,
                          referenceFac.createParamRefExpression(params[0]),
                          referenceFac.createParamRefExpression(params[1]))),
       statementFac.createDeclarationAndAssigmentStatement(
           variableRepMultiplier, literalFac.getIntLiteral(1)),
       statementFac.createIfConditionalStatement(
           expressionFac.createBinaryExpression(
               BinaryOperators::Less,
               referenceFac.createVarRefExpression(variableC),
               literalFac.getIntLiteral(0)),
           statementFac.createCompoundStatement(
               {statementFac.createAssigmentStatement(
                   variableRepMultiplier, literalFac.getIntLiteral(-1))})),
       statementFac.createDeclarationAndAssigmentStatement(
           variableRepCount, literalFac.getIntLiteral(0)),
       statementFac.createWhileLoopStatement(
           expressionFac.createBinaryExpression(
               BinaryOperators::Less,
               expressionFac.createBinaryExpression(
                   BinaryOperators::Add,
                   referenceFac.createVarRefExpression(variableC),
                   referenceFac.createVarRefExpression(variableRepCount)),
               literalFac.getIntLiteral(0)),
           statementFac.createCompoundStatement(
               {statementFac.createAssigmentStatement(
                   variableRepCount,
                   expressionFac.createBinaryExpression(
                       BinaryOperators::Add,
                       referenceFac.createVarRefExpression(variableRepCount),
                       referenceFac.createVarRefExpression(
                           variableRepMultiplier)))})),
       statementFac.createFunctionCallStatement(
           "std::cout", {literalFac.getStringLiteral("c is "),
                         referenceFac.createVarRefExpression(variableC),
                         literalFac.getStringLiteral(" and it was update "),
                         referenceFac.createVarRefExpression(variableRepCount),
                         literalFac.getStringLiteral(" times to have value 0"),
                         literalFac.getConstLiteral("std::endl")}),
       statementFac.createReturnStatement(
           referenceFac.createVarRefExpression(variableC))});

  auto retType = typeFac.getIntType();

  auto function =
      functionFac.createFunction("brutalAddition", params, body, retType);

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