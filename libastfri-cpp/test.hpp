#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include "iostream"


#include <libastfri/factories/ExpressionFactory.hpp>

class FindClassConsumer : public clang::ASTConsumer
{
public:
clang::ASTContext *context;

explicit FindClassConsumer ( clang::ASTContext& context) : context(&context) {}; // todo presunut do cpp
virtual auto HandleTranslationUnit (clang::ASTContext& p_context) -> void;
};

class FindClassAction : public clang::ASTFrontendAction
{
public:
    virtual auto CreateASTConsumer (clang::CompilerInstance& compiler, llvm::StringRef) -> std::unique_ptr<clang::ASTConsumer>;
};

class FindNamedClassVisitor
  : public clang::RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  bool VisitFunctionDecl(clang::FunctionDecl *Declaration) {
    // For debugging, dumping the AST nodes will show which nodes are already
    // being visited.
    // Declaration->dump();

    std::cout << "Declaration: " << Declaration->getNameInfo().getAsString() << std::endl;



    // Declaration->getParamDecl
    // Declaration->getBody()

    myFunc.body = this->VisitrCompoundStmt(Declaration->getBody());

    // The return value indicates whether we want the visitation to proceed.
    // Return false to stop the traversal of the AST.
    return false;
  }

    // TODO - preriesit nejakym spossobm ako dostat navraty typ z funkcie (atribut visitoru, ?? out parameter)
  bool VisitrCompoundStmt(clang::CompoundStmt *Declaration) {
    // For debugging, dumping the AST nodes will show which nodes are already
    // being visited.
    // Declaration->dump();

    std::cout << "Declaration: " << Declaration->getStmtClassName() << std::endl;
    return false;
  }
};



void testExample();