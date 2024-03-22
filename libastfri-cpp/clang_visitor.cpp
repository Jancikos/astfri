#include <libastfri-cpp/clang_visitor.hpp>
namespace libastfri::cpp {
AstfriClangVisitor::AstfriClangVisitor(
    lsfs::TranslationUnit &visitedTranslationUnit)
    : visitedTranslationUnit(&visitedTranslationUnit),
      visitedDeclaration(nullptr), visitedExpression(nullptr),
      visitedStatement(nullptr) {}
} // namespace libastfri::cpp