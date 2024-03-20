#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri-cpp/clang_tools.hpp>
#include <libastfri/factories/FunctionFactory.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Function.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

namespace lsff = libastfri::factories;
namespace lsfs = libastfri::structures;

namespace libastfri::cpp {
AstfriClangVisitor::AstfriClangVisitor(
    lsfs::TranslationUnit &visitedTranslationUnit)
    : visitedTranslationUnit(&visitedTranslationUnit) {}

bool AstfriClangVisitor::VisitTranslationUnitDecl(
    clang::TranslationUnitDecl *Declaration) {

  for (auto *decl : Declaration->decls()) {
    if (auto *funDecl = llvm::dyn_cast<clang::FunctionDecl>(decl)) {
      VisitFunctionDecl(funDecl);
      // visitedTranslationUnit->functions.push_back(visitedFunction);
    }
  }

  return false;
}

bool AstfriClangVisitor::VisitFunctionDecl(clang::FunctionDecl *Declaration) {
  // For debugging, dumping the AST nodes will show which nodes are already
  // being visited.
  Declaration->dump();

  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &literalFac = lsff::LiteralFactory::getInstance();
  auto &statementFac = lsff::StatementFactory::getInstance();

  // title
  std::string title = Declaration->getNameInfo().getAsString();

  // return type
  lsfs::Type *returnType = Tools::convertType(Declaration->getReturnType());

  // params
  std::vector<lsfs::ParameterDefinition *> params;
  for (auto param : Declaration->parameters()) {
    // param->dump();

    VisitParmVarDecl(param);
    params.emplace_back(popVisitedVariable<lsfs::ParameterDefinition>());
  }

  // body
  VisitCompoundStmt(static_cast<clang::CompoundStmt *>(Declaration->getBody()));
  auto *body = popVisitedStatement<lsfs::CompoundStatement>();

  visitedTranslationUnit->functions.push_back(
      funFac.createFunction(title, params, body, returnType));
  //   visitedFunction = visitedTranslationUnit->functions.back();

  return false;
}

bool AstfriClangVisitor::VisitVarDecl(clang::VarDecl *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();
  auto &statementFac = lsff::StatementFactory::getInstance();

  auto *var = funFac.createVariable(Declaration->getNameAsString(),
                                    Tools::convertType(Declaration->getType()),
                                    nullptr);

  if (Declaration->hasInit()) {
    VisitExpr(Declaration->getInit());
    auto *init = popVisitedExpression<lsfs::Expression>();
    visitedStatement =
        statementFac.createDeclarationAndAssigmentStatement(var, init);
    return false;
  }

  visitedStatement = statementFac.createDeclarationStatement(var);
  return false;
}

bool AstfriClangVisitor::VisitParmVarDecl(clang::ParmVarDecl *Declaration) {
  auto &funFac = lsff::FunctionFactory::getInstance();

  lsfs::Expression *defValue = nullptr;
  if (Declaration->hasDefaultArg()) {
    VisitExpr(Declaration->getDefaultArg());
    defValue = popVisitedExpression<lsfs::Expression>();
  }

  visitedVariable = funFac.createParameter(
      Declaration->getNameAsString(),
      Tools::convertType(Declaration->getType()), defValue);

  return false;
}
} // namespace libastfri::cpp