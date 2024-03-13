#include <libastfri-cpp/clang_visitor.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include "iostream"

bool AstfriClangVisitor::VisitFunctionDecl(
    clang::FunctionDecl *Declaration) {
  // For debugging, dumping the AST nodes will show which nodes are already
  // being visited.
  Declaration->dump();

  std::cout << std::endl << "Declaration: " << Declaration->getNameInfo().getAsString()
            << std::endl;

  // Declaration->getParamDecl
  // Declaration->getBody()

  // myFunc.body = this->VisitrCompoundStmt(Declaration->getBody());

  // The return value indicates whether we want the visitation to proceed.
  // Return false to stop the traversal of the AST.
  return false;
}

// TODO - preriesit nejakym spossobm ako dostat navraty typ z funkcie (atribut
// visitoru, ?? out parameter)
bool AstfriClangVisitor::VisitCompoundStmt(
    clang::CompoundStmt *Declaration) {
  // For debugging, dumping the AST nodes will show which nodes are already
  // being visited.
  // Declaration->dump();

  std::cout << "Declaration: " << Declaration->getStmtClassName() << std::endl;
  return false;
}