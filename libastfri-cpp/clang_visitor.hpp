#pragma once

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
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
    AstfriClangVisitor(libastfri::structures::TranslationUnit &visitedTranslationUnit);
  bool VisitTranslationUnitDecl(clang::TranslationUnitDecl *Declaration);

  bool VisitFunctionDecl(clang::FunctionDecl *Declaration);

  bool VisitStmt(clang::Stmt *Declaration);
  bool VisitCompoundStmt(clang::CompoundStmt *Declaration);
  bool VisitDeclStmt(clang::DeclStmt *Declaration);
  bool VisitReturnStmt(clang::ReturnStmt *Declaration);
  bool VisitIfStmt(clang::IfStmt *Declaration);

  bool VisitExpr(clang::Expr *Declaration);
  bool VisitIntegerLiteral(clang::IntegerLiteral *Declaration);
  bool VisitParmVarDecl(clang::ParmVarDecl *Declaration);
  bool VisitDeclRefExpr(clang::DeclRefExpr *Declaration);

  libastfri::structures::TranslationUnit *visitedTranslationUnit;

private:
  libastfri::structures::Statement *visitedStatement;
  libastfri::structures::Expression *visitedExpression;
  libastfri::structures::BaseVariableDefintion *visitedVariable;
  libastfri::structures::FunctionDefinition *visitedFunction;
};
} // namespace libastfri::cpp
