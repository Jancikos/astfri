#include <memory>
#include <libastfri-cpp/test.hpp>
#include <fstream>
#include <sstream>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/FunctionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

using namespace libastfri::structures;
using namespace libastfri::factories;

int main() {
    auto ifst = std::ifstream("examples/input/addition.cpp");
    auto ist = std::stringstream();
    ist << ifst.rdbuf();
    std::string code = ist.str();

    clang::tooling::runToolOnCodeWithArgs(std::make_unique<FindClassAction>(), code, {""});

    return 0;


  auto &typeFac = TypeFactory::getInstance();
  auto &literalFac = LiteralFactory::getInstance();
  auto &statementFac = StatementFactory::getInstance();
  auto &expressionFac = ExpressionFactory::getInstance();
  auto &referenceFac = ReferenceFactory::getInstance();
  auto &functionFac = FunctionFactory::getInstance();

  // int simpleAddition(int a, int b)
    std::vector<ParameterDefinition *> paramsSimpleAddition;
    paramsSimpleAddition.push_back(functionFac.createParameter("a", typeFac.getIntType()));
    paramsSimpleAddition.push_back(functionFac.createParameter("b", typeFac.getIntType()));

    auto bodySimpleAddition = statementFac.createCompoundStatement(
        {statementFac.createReturnStatement(
            expressionFac.createBinaryExpression(
                BinaryOperators::Add,
                referenceFac.createParamRefExpression(paramsSimpleAddition[0]),
                referenceFac.createParamRefExpression(paramsSimpleAddition[1])
                )
            )
        }
    );
    auto retTypeSimpleAddition = typeFac.getIntType();

    auto functionSimpleAddition =
        functionFac.createFunction("simpleAddition", paramsSimpleAddition, bodySimpleAddition, retTypeSimpleAddition);

  // int brutalAddition(int a, int b)
  std::vector<ParameterDefinition *> params;
  params.push_back(functionFac.createParameter("a", typeFac.getIntType()));
  params.push_back(functionFac.createParameter("b", typeFac.getIntType()));
  auto variableC = functionFac.createVariable("c", typeFac.getIntType());
  auto variableRepMultiplier =
      functionFac.createVariable("repMultiplier", typeFac.getIntType());
  auto variableRepCount =
      functionFac.createVariable("repCount", typeFac.getIntType());

  auto body = statementFac.createCompoundStatement({
       statementFac.createDeclarationAndAssigmentStatement(
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
                           variableRepMultiplier)))})
        ),
        statementFac.createFunctionCallStatement(
            functionSimpleAddition, {
                referenceFac.createParamRefExpression(params[0]),
                referenceFac.createParamRefExpression(params[1])
            }),
        statementFac.createReturnStatement(
           referenceFac.createFunctionCallExpression(
            functionSimpleAddition, {
                referenceFac.createParamRefExpression(params[0]),
                referenceFac.createParamRefExpression(params[1])
            })
        )
    }
  );

  auto retType = typeFac.getIntType();

  auto functionBrutalAddition =
      functionFac.createFunction("brutalAddition", params, body, retType);

  return 0;
}

int simpleAddition(int a, int b)
{
    return a + b;
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

  return simpleAddition(a, b);
}