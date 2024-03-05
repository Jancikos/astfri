#include <iostream>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>
#include <libastfri/structures/Function.hpp>

using namespace libastfri::structures;
using namespace libastfri::factories;

int main() {
  auto &typeFac = TypeFactory::getInstance();
  auto &literalFac = LiteralFactory::getInstance();
  auto &statementFac = StatementFactory::getInstance();
  auto &expressionFac = ExpressionFactory::getInstance();

  std::vector<ParameterDefinition *> params;
  params.push_back(new ParameterDefinition("a", typeFac.getIntType()));
  params.push_back(new ParameterDefinition("b", typeFac.getIntType()));

  auto variableC = new VariableDefintion("c", typeFac.getIntType());
  auto variableRepMultiplier =
      new VariableDefintion("repMultiplier", typeFac.getIntType());
  auto variableRepCount = new VariableDefintion("repCount", typeFac.getIntType());

  auto body = statementFac.createCompoundStatement(
      {
        statementFac.createDeclarationAndAssigmentStatement(
           variableC,
           expressionFac.createBinaryExpression(
                                BinaryOperators::Add,
                                new VarRefExpression(params[0]->variable),
                                new VarRefExpression(params[1]->variable))),
       statementFac.createDeclarationAndAssigmentStatement(
            variableRepMultiplier,
            literalFac.getIntLiteral(1)),
       statementFac.createIfConditionalStatement(
            expressionFac.createBinaryExpression(
                BinaryOperators::Less,
                new VarRefExpression(variableC),
                literalFac.getIntLiteral(0)),
            statementFac.createCompoundStatement({
                statementFac.createAssigmentStatement(variableRepMultiplier, literalFac.getIntLiteral(-1))})
            ),
       statementFac.createDeclarationAndAssigmentStatement(
            variableRepCount,
            literalFac.getIntLiteral(0)
        ),
       statementFac.createWhileLoopStatement(
           expressionFac.createBinaryExpression(
               BinaryOperators::Less, 
               expressionFac.createBinaryExpression(
                                    BinaryOperators::Add,
                                    new VarRefExpression(variableC),
                                    new VarRefExpression(variableRepCount)),
               literalFac.getIntLiteral(0)),
           statementFac.createCompoundStatement({statementFac.createAssigmentStatement(
               variableRepCount,
               expressionFac.createBinaryExpression(
                   BinaryOperators::Add,
                   new VarRefExpression(variableRepCount),
                   new VarRefExpression(variableRepMultiplier)))})),
       statementFac.createFunctionCallStatement("std::cout", {
            literalFac.getStringLiteral("c is "),
            new VarRefExpression(variableC),
            literalFac.getStringLiteral(" and it was update "),
            new VarRefExpression(variableRepCount),
            literalFac.getStringLiteral(" times to have value 0"),
            literalFac.getConstLiteral("std::endl")}),
       statementFac.createReturnStatement(new VarRefExpression(variableC))});

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