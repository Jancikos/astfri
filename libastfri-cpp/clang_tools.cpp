#include <clang/AST/Stmt.h>
#include <fstream>
#include <memory>
#include <sstream>

#include <libastfri-cpp/clang_management.hpp>
#include <libastfri-cpp/clang_tools.hpp>
#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>
#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Function.hpp>

namespace libastfri::cpp {
Type *AstfriClangTools::convertType(clang::QualType qt) {
  auto &typeFac = libastfri::factories::TypeFactory::getInstance();

  if (qt->isIntegerType()) {
    return typeFac.getIntType();
  }

  if (qt->isFloatingType()) {
    return typeFac.getFloatType();
  }

  if (qt->isCharType()) {
    return typeFac.getCharType();
  }

  if (qt->isBooleanType()) {
    return typeFac.getBoolType();
  }

  if (qt->isVoidType()) {
    return typeFac.getVoidType();
  }

  return typeFac.getUserType(qt.getAsString());
}

libastfri::structures::BinaryOperators
AstfriClangTools::convertBinaryOperator(clang::BinaryOperator::Opcode op) {
  switch (op) {
  case clang::BinaryOperator::Opcode::BO_Add:
    return libastfri::structures::BinaryOperators::Add;
  case clang::BinaryOperator::Opcode::BO_Sub:
    return libastfri::structures::BinaryOperators::Subtract;
  case clang::BinaryOperator::Opcode::BO_Mul:
    return libastfri::structures::BinaryOperators::Multiply;
  case clang::BinaryOperator::Opcode::BO_Div:
    return libastfri::structures::BinaryOperators::Divide;
  case clang::BinaryOperator::Opcode::BO_Rem:
    return libastfri::structures::BinaryOperators::Modulo;
  case clang::BinaryOperator::Opcode::BO_LT:
    return libastfri::structures::BinaryOperators::Less;
  case clang::BinaryOperator::Opcode::BO_GT:
    return libastfri::structures::BinaryOperators::Greater;
  case clang::BinaryOperator::Opcode::BO_LE:
    return libastfri::structures::BinaryOperators::LessEqual;
  case clang::BinaryOperator::Opcode::BO_GE:
    return libastfri::structures::BinaryOperators::GreaterEqual;
  case clang::BinaryOperator::Opcode::BO_EQ:
    return libastfri::structures::BinaryOperators::Equal;
  case clang::BinaryOperator::Opcode::BO_NE:
    return libastfri::structures::BinaryOperators::NotEqual;
    //   case clang::BinaryOperator::Opcode::BO_And:
    //     return libastfri::structures::BinaryOperators::AND;
    //   case clang::BinaryOperator::Opcode::BO_Or:
    //     return libastfri::structures::BinaryOperators::OR;
  }

  throw std::runtime_error("Unknown binary operator");
}

libastfri::structures::UnaryOperators
AstfriClangTools::convertUnaryOperator(clang::UnaryOperator::Opcode op) {
  switch (op) {
  case clang::UnaryOperator::Opcode::UO_Minus:
    return libastfri::structures::UnaryOperators::Negative;
  case clang::UnaryOperator::Opcode::UO_Not:
    return libastfri::structures::UnaryOperators::Not;
  }

  throw std::runtime_error("Unknown unary operator");
}

void AstfriClangTools::BeginClangTreeVisit(
    std::string pathToCode,
    libastfri::structures::TranslationUnit &visitedTranslationUnit) {
  auto ifst = std::ifstream(pathToCode);
  auto ist = std::stringstream();
  ist << ifst.rdbuf();
  std::string code = ist.str();

  // spusti clang prehliadku
  clang::tooling::runToolOnCodeWithArgs(
      std::make_unique<libastfri::cpp::AstfriClangTraverseAction>(
          visitedTranslationUnit),
      code, {""});
}

// TODO - presunut to sem z HPP, bol problem s includom
// template <typename T, typename P> T *AstfriClangTools::popPointer(P *&pointer) {
//   T *result = static_cast<T *>(pointer);
//   pointer = nullptr;
//   return result;
// }

} // namespace libastfri::cpp