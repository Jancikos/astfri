#pragma once

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

namespace libastfri::cpp
{
class ClangTools
{
public:
    static libastfri::structures::Type* convertType (clang::QualType qt);
    static libastfri::structures::BinaryOperators convertBinaryOperator (
        clang::BinaryOperator::Opcode op
    );
    static libastfri::structures::UnaryOperators convertUnaryOperator (
        clang::UnaryOperator::Opcode op
    );

    template<typename T, typename P>
    static T* popPointer (P*& pointer)
    {
        T* result = static_cast<T*>(pointer);
        pointer   = nullptr;
        return result;
    }

    static void BeginClangTreeVisit (
        std::string pathToCode,
        libastfri::structures::TranslationUnit& visitedTranslationUnit
    );
};
} // namespace libastfri::cpp