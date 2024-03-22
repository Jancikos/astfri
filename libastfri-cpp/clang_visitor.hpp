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
#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>


namespace lsfs = libastfri::structures;
namespace libastfri::cpp {
class AstfriClangVisitor
    : public clang::RecursiveASTVisitor<AstfriClangVisitor> {
    using Tools = AstfriClangTools;

  public:
    // clang_visitor.cpp
    AstfriClangVisitor(
        lsfs::TranslationUnit &visitedTranslationUnit);

    // clang_visitor.cpp
    lsfs::Declaration *getDeclaration(clang::Decl *Decl);
    bool VisitTranslationUnitDecl(clang::TranslationUnitDecl *Decl);
    bool VisitFunctionDecl(clang::FunctionDecl *Decl);
    bool VisitVarDecl(clang::VarDecl *Decl);
    bool VisitParmVarDecl(clang::ParmVarDecl *Decl);

    // clang_visitor_stmt.cpp
    lsfs::Statement *getStatement(clang::Stmt *Stmt);
    bool VisitStmt(clang::Stmt *Stmt);
    bool VisitCompoundStmt(clang::CompoundStmt *Stmt);
    bool VisitReturnStmt(clang::ReturnStmt *Stmt);
    bool VisitIfStmt(clang::IfStmt *Stmt);
    bool VisitWhileStmt(clang::WhileStmt *Stmt);

    // clang_visitor_expr.cpp
    lsfs::Expression *getExpression(clang::Expr *Expr);
    bool VisitExpr(clang::Expr *Expr);
    bool VisitBinaryOperator(clang::BinaryOperator *Expr);
    bool VisitIntegerLiteral(clang::IntegerLiteral *Expr);
    bool VisitDeclRefExpr(clang::DeclRefExpr *Expr);
    bool VisitCallExpr(clang::CallExpr *Expr);

    lsfs::TranslationUnit *visitedTranslationUnit;
  private:
    lsfs::Declaration *visitedDeclaration;
    lsfs::Statement *visitedStatement;
    lsfs::Expression *visitedExpression;

    // temaplate methods

    template <typename T> T *popVisitedDeclaration() {
        return Tools::popPointer<T>(visitedDeclaration);
    }
    template<typename T> T *getDeclaration(clang::Decl *Decl) {
        auto* declaration = getDeclaration(Decl);
        if (declaration == nullptr) {
            return nullptr;
        }

        // TOOD - preco tu nemoze byt dynamic_cast?
        // return dynamic_cast<T*>(declaration);
        return static_cast<T*>(declaration);
    }

    template <typename T> T *popVisitedStatement() {
        return Tools::popPointer<T>(visitedStatement);
    }
    template <typename T> T *getStatement(clang::Stmt *Stmt) {
        auto* statement = getStatement(Stmt);
        if (statement == nullptr) {
            return nullptr;
        }

        return static_cast<T*>(statement);
    }

    template <typename T> T *popVisitedExpression() {
        return Tools::popPointer<T>(visitedExpression);
    }
    template <typename T> T *getExpression(clang::Expr *Expr) {
        auto* expression = getExpression(Expr);
        if (expression == nullptr) {
            return nullptr;
        }

        return static_cast<T*>(expression);
    }
};
} // namespace libastfri::cpp
