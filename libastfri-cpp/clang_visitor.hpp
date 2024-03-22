#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Stmt.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <libastfri-cpp/clang_tools.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Function.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

namespace libastfri::cpp {
class AstfriClangVisitor
    : public clang::RecursiveASTVisitor<AstfriClangVisitor> {
    using Tools = AstfriClangTools;

  public:
    // clang_visitor.cpp
    AstfriClangVisitor(
        libastfri::structures::TranslationUnit &visitedTranslationUnit);
    bool VisitTranslationUnitDecl(clang::TranslationUnitDecl *Declaration);
    bool VisitFunctionDecl(clang::FunctionDecl *Declaration);
    bool VisitVarDecl(clang::VarDecl *Declaration);
    bool VisitParmVarDecl(clang::ParmVarDecl *Declaration);

    // clang_visitor_stmt.cpp
    structures::Statement *getStatement(clang::Stmt *Declaration);
    bool VisitStmt(clang::Stmt *Declaration);
    bool VisitCompoundStmt(clang::CompoundStmt *Declaration);
    bool VisitReturnStmt(clang::ReturnStmt *Declaration);
    bool VisitIfStmt(clang::IfStmt *Declaration);
    bool VisitWhileStmt(clang::WhileStmt *Declaration);

    // clang_visitor_expr.cpp
    structures::Expression *getExpression(clang::Expr *Declaration);
    bool VisitExpr(clang::Expr *Declaration);
    bool VisitBinaryOperator(clang::BinaryOperator *Declaration);
    bool VisitIntegerLiteral(clang::IntegerLiteral *Declaration);
    bool VisitDeclRefExpr(clang::DeclRefExpr *Declaration);
    bool VisitCallExpr(clang::CallExpr *Declaration);

    libastfri::structures::TranslationUnit *visitedTranslationUnit;

  private:
    libastfri::structures::Statement *visitedStatement;
    libastfri::structures::Expression *visitedExpression;
    libastfri::structures::BaseVariableDefintion *visitedVariable;
    libastfri::structures::FunctionDefinition *visitedFunction;

    template <typename T> T *popVisitedStatement() {
        return Tools::popPointer<T>(visitedStatement);
    }

    template <typename T> T *popVisitedExpression() {
        return Tools::popPointer<T>(visitedExpression);
    }

    template <typename T> T *popVisitedVariable() {
        return Tools::popPointer<T>(visitedVariable);
    }

    template <typename T> T *popVisitedFunction() {
        return Tools::popPointer<T>(visitedFunction);
    }
};
} // namespace libastfri::cpp
