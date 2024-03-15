#pragma once

#include "libastfri/structures/Expression.hpp"
#include "libastfri/structures/Function.hpp"
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>
#include <clang/AST/Decl.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include <libastfri/structures/Statement.hpp>
#include <libastfri/structures/Type.hpp>

class AstfriClangTools {
public:
  static libastfri::structures::Type *convertType(clang::QualType qt);
  static libastfri::structures::BinaryOperators
  convertBinaryOperator(clang::BinaryOperator::Opcode op);
  static libastfri::structures::UnaryOperators
  convertUnaryOperator(clang::UnaryOperator::Opcode op);
};
