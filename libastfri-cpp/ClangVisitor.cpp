#include <libastfri-cpp/ClangVisitor.hpp>

namespace libastfri::cpp
{
ClangVisitor::ClangVisitor(lsfs::TranslationUnit& visitedTranslationUnit) :
    visitedTranslationUnit(&visitedTranslationUnit),
    visitedDeclaration(nullptr),
    visitedStatement(nullptr),
    visitedExpression(nullptr)
{
}

void ClangVisitor::clearVisited()
{
    visitedDeclaration = nullptr;
    visitedExpression  = nullptr;
    visitedStatement   = nullptr;
}

} // namespace libastfri::cpp