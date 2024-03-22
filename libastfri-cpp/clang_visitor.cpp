#include <clang/AST/Stmt.h>
#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri-cpp/clang_tools.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>
#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

namespace lsff = libastfri::factories;
namespace lsfs = libastfri::structures;

namespace libastfri::cpp {
AstfriClangVisitor::AstfriClangVisitor(
    lsfs::TranslationUnit &visitedTranslationUnit)
    : visitedTranslationUnit(&visitedTranslationUnit),
      visitedDeclaration(nullptr), visitedExpression(nullptr),
      visitedStatement(nullptr) {}

lsfs::Declaration *AstfriClangVisitor::getDeclaration(clang::Decl *Decl) {
    // skontroluj pociatocny stav
    assert(visitedDeclaration == nullptr);

    auto traversalFailed = TraverseDecl(Decl);
    if (traversalFailed) {
        throw std::runtime_error("Decl traversal failed");
        return nullptr; // prehliadka sa nepodarila
    }

    auto *declaration =
        Tools::popPointer<lsfs::Declaration>(visitedDeclaration);
    if (declaration != nullptr) {
        return declaration; // ak sa nasiel declaration, tak ho vrat
    }

    throw std::runtime_error("No declaration found");
    return nullptr; // nezachytili sme ziadny declaration
}

bool AstfriClangVisitor::VisitTranslationUnitDecl(
    clang::TranslationUnitDecl *Declaration) {

    for (auto *decl : Declaration->decls()) {
        if (auto *funDecl = llvm::dyn_cast<clang::FunctionDecl>(decl)) {
            visitedTranslationUnit->functions.push_back(
                getDeclaration<lsfs::FunctionDefinition>(funDecl));
        }
    }

    return false;
}

bool AstfriClangVisitor::VisitFunctionDecl(clang::FunctionDecl *Declaration) {
    // For debugging, dumping the AST nodes will show which nodes are already
    // being visited.
    Declaration->dump();

    auto &declFac = lsff::DeclarationFactory::getInstance();
    auto &literalFac = lsff::LiteralFactory::getInstance();
    auto &statementFac = lsff::StatementFactory::getInstance();

    // title
    std::string title = Declaration->getNameInfo().getAsString();

    // return type
    lsfs::Type *returnType = Tools::convertType(Declaration->getReturnType());

    // params
    std::vector<lsfs::ParameterDefinition *> params;
    for (auto paramDecl : Declaration->parameters()) {
        VisitParmVarDecl(paramDecl); // nemozem volat TRaverseDecl, lebo to odchyti VisitVarDecl
        params.push_back(popVisitedDeclaration<lsfs::ParameterDefinition>());
    }

    // body
    auto *body = getStatement<lsfs::CompoundStatement>(Declaration->getBody());

    visitedDeclaration = declFac.createFunction(title, params, body, returnType);
    return false;
}

// TOOD - premysliet, ci je spravne ze sa tu vytvara statement
bool AstfriClangVisitor::VisitVarDecl(clang::VarDecl *Declaration) {
    auto &declFac = lsff::DeclarationFactory::getInstance();
    auto &statementFac = lsff::StatementFactory::getInstance();

    auto *var = declFac.createVariable(
        Declaration->getNameAsString(),
        Tools::convertType(Declaration->getType()), nullptr);

    if (Declaration->hasInit()) {
        auto *init = getExpression(Declaration->getInit());
        visitedStatement =
            statementFac.createDeclarationAndAssigmentStatement(var, init);
        return false;
    }

    visitedStatement = statementFac.createDeclarationStatement(var);
    return false;
}

bool AstfriClangVisitor::VisitParmVarDecl(clang::ParmVarDecl *Declaration) {
    auto &declFac = lsff::DeclarationFactory::getInstance();

    lsfs::Expression *defValue = nullptr;
    if (Declaration->hasDefaultArg()) {
        defValue = getExpression(Declaration->getDefaultArg());
    }

    visitedDeclaration = declFac.createParameter(
        Declaration->getNameAsString(),
        Tools::convertType(Declaration->getType()), defValue);

    return false;
}
} // namespace libastfri::cpp