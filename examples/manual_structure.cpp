#include <iostream>
#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

namespace lsfs = libastfri::structures;
namespace lsff = libastfri::factories;

/**
 * @brief example, kde manualne vyuzivam vytvorene struktury z libastfri pre
 * reprezentovanie kodu funcki na konci suboru
 */
int main ()
{
    auto& typeFac        = lsff::TypeFactory::getInstance();
    auto& literalFac     = lsff::LiteralFactory::getInstance();
    auto& statementFac   = lsff::StatementFactory::getInstance();
    auto& expressionFac  = lsff::ExpressionFactory::getInstance();
    auto& referenceFac   = lsff::ReferenceFactory::getInstance();
    auto& declarationFac = lsff::DeclarationFactory::getInstance();

    // int simpleAddition(int a, int b)
    std::vector<lsfs::ParameterDefinition*> paramsSimpleAddition;
    paramsSimpleAddition.push_back(
        declarationFac.createParameter("a", typeFac.getIntType())
    );
    paramsSimpleAddition.push_back(
        declarationFac.createParameter("b", typeFac.getIntType())
    );

    auto bodySimpleAddition = statementFac.createCompoundStatement(
        {statementFac.createReturnStatement(
            expressionFac.createBinaryExpression(
                lsfs::BinaryOperators::Add,
                referenceFac.createParamRefExpression(paramsSimpleAddition[0]),
                referenceFac.createParamRefExpression(paramsSimpleAddition[1])
            )
        )}
    );
    auto retTypeSimpleAddition  = typeFac.getIntType();

    auto functionSimpleAddition = declarationFac.createFunction(
        "simpleAddition",
        paramsSimpleAddition,
        bodySimpleAddition,
        retTypeSimpleAddition
    );

    // int weirdAddition(int a, int b)
    std::vector<lsfs::ParameterDefinition*> params;
    params.push_back(declarationFac.createParameter("a", typeFac.getIntType()));
    params.push_back(declarationFac.createParameter("b", typeFac.getIntType()));
    auto variableC = declarationFac.createVariable("c", typeFac.getIntType());
    auto variableRepMultiplier
        = declarationFac.createVariable("repMultiplier", typeFac.getIntType());
    auto variableRepCount
        = declarationFac.createVariable("repCount", typeFac.getIntType());

    auto body = statementFac.createCompoundStatement(
        {statementFac.createDeclarationAndAssigmentStatement(
             variableC,
             expressionFac.createBinaryExpression(
                 lsfs::BinaryOperators::Add,
                 referenceFac.createParamRefExpression(params[0]),
                 referenceFac.createParamRefExpression(params[1])
             )
         ),
         statementFac.createDeclarationAndAssigmentStatement(
             variableRepMultiplier,
             literalFac.getIntLiteral(1)
         ),
         statementFac.createIfConditionalStatement(
             expressionFac.createBinaryExpression(
                 lsfs::BinaryOperators::Less,
                 referenceFac.createVarRefExpression(variableC),
                 literalFac.getIntLiteral(0)
             ),
             statementFac.createCompoundStatement(
                 {statementFac.createExpressionStatement(
                     expressionFac.createBinaryExpression(
                         lsfs::BinaryOperators::Assign,
                         referenceFac
                             .createVarRefExpression(variableRepMultiplier),
                         literalFac.getIntLiteral(-1)
                     )
                 )}
             )
         ),
         statementFac.createDeclarationAndAssigmentStatement(
             variableRepCount,
             literalFac.getIntLiteral(0)
         ),
         statementFac.createWhileStatement(
             expressionFac.createBinaryExpression(
                 lsfs::BinaryOperators::Less,
                 expressionFac.createBinaryExpression(
                     lsfs::BinaryOperators::Add,
                     referenceFac.createVarRefExpression(variableC),
                     referenceFac.createVarRefExpression(variableRepCount)
                 ),
                 literalFac.getIntLiteral(0)
             ),
             statementFac.createCompoundStatement(
                 {statementFac.createExpressionStatement(
                     expressionFac.createBinaryExpression(
                         lsfs::BinaryOperators::Assign,
                         referenceFac.createVarRefExpression(variableRepCount),
                         expressionFac.createBinaryExpression(
                             lsfs::BinaryOperators::Add,
                             referenceFac
                                 .createVarRefExpression(variableRepCount),
                             referenceFac
                                 .createVarRefExpression(variableRepMultiplier)
                         )
                     )
                 )}
             )
         ),
         statementFac.createExpressionStatement(
             referenceFac.createFunctionCallExpression(
                 functionSimpleAddition->name,
                 {referenceFac.createParamRefExpression(params[0]),
                  referenceFac.createParamRefExpression(params[1])}
             )
         ),
         statementFac.createReturnStatement(
             referenceFac.createFunctionCallExpression(
                 functionSimpleAddition->name,
                 {referenceFac.createParamRefExpression(params[0]),
                  referenceFac.createParamRefExpression(params[1])}
             )
         )}
    );

    auto retType = typeFac.getIntType();

    auto* weirdAddition = declarationFac.createFunction("weirdAddition", params, body, retType);

    std::cout << "Nacitanie funkcie: " << weirdAddition->name << ", " << functionSimpleAddition->name << std::endl;

    return 0;
}

int simpleAddition (int a, int b)
{
    return a + b;
}

int weirdAddition (int a, int b)
{
    int c             = a + b;
    int repMultiplier = 1;

    if (c < 0)
    {
        repMultiplier = -1;
    }

    int repCount = 0;
    while (c + repCount < 0)
    {
        repCount += repMultiplier;
    }

    return simpleAddition(a, b);
}