#include <libastfri/factories/DeclarationFactory.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

#include <libastfri-cpp/ClangVisitor.hpp>

#include <cassert>

namespace lsff = libastfri::factories;

namespace libastfri::cpp
{
lsfs::Declaration* ClangVisitor::getDeclaration(clang::Decl* Decl)
{
    // skontroluj pociatocny stav
    assert(visitedDeclaration == nullptr);

    try
    {
        auto traversalFailed = TraverseDecl(Decl);
        if (traversalFailed)
        {
            // prehliadka sa nepodarila
            throw std::runtime_error("Decl traversal failed");
        }

        auto* declaration
            = Tools::popPointer<lsfs::Declaration>(visitedDeclaration);
        if (declaration != nullptr)
        {
            return declaration; // ak sa nasiel declaration, tak ho vrat
        }

        // nezachytili sme ziadny declaration
        throw std::runtime_error("No declaration found");
    }
    catch (std::exception& e)
    {
        auto* declFac = &lsff::DeclarationFactory::getInstance();

        clearVisited(); // WARN - skontrolovat ci neovplyvni predosle prehliadky

        return declFac->createUknownDeclaration(e.what());
    }
}

bool ClangVisitor::VisitTranslationUnitDecl(clang::TranslationUnitDecl* Decl)
{
    for (auto* decl : Decl->decls())
    {
        if (auto* funDecl = llvm::dyn_cast<clang::FunctionDecl>(decl))
        {
            visitedTranslationUnit->functions.push_back(
                getDeclaration<lsfs::FunctionDefinition>(funDecl)
            );
        }
    }
    return false;
}

bool ClangVisitor::VisitFunctionDecl(clang::FunctionDecl* Decl)
{
    // For debugging, dumping the AST nodes will show which nodes are already
    // being visited.
    // Decl->dump();

    auto& declFac      = lsff::DeclarationFactory::getInstance();

    // title
    std::string title = Decl->getNameInfo().getAsString();

    // return type
    lsfs::Type* returnType = Tools::convertType(Decl->getReturnType());

    // params
    std::vector<lsfs::ParameterDefinition*> params;
    for (auto paramDecl : Decl->parameters())
    {
        VisitParmVarDecl(paramDecl); // nemozem volat TRaverseDecl, lebo to
                                     // odchyti VisitVarDecl
        params.push_back(popVisitedDeclaration<lsfs::ParameterDefinition>());
    }

    // body
    auto* body = getStatement<lsfs::CompoundStatement>(Decl->getBody());

    visitedDeclaration
        = declFac.createFunction(title, params, body, returnType);
    return false;
}

bool ClangVisitor::VisitVarDecl(clang::VarDecl* Decl)
{
    auto& declFac      = lsff::DeclarationFactory::getInstance();

    visitedDeclaration = declFac.createVariable(
        Decl->getNameAsString(),
        Tools::convertType(Decl->getType()),
        nullptr
    );

    if (Decl->hasInit())
    {
        visitedExpression = getExpression(Decl->getInit());
    }

    return false;
}

bool ClangVisitor::VisitParmVarDecl(clang::ParmVarDecl* Decl)
{
    auto& declFac              = lsff::DeclarationFactory::getInstance();

    lsfs::Expression* defValue = nullptr;
    if (Decl->hasDefaultArg())
    {
        defValue = getExpression(Decl->getDefaultArg());
    }

    visitedDeclaration = declFac.createParameter(
        Decl->getNameAsString(),
        Tools::convertType(Decl->getType()),
        defValue
    );

    return false;
}
} // namespace libastfri::cpp