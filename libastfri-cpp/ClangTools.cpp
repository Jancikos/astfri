#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

#include <libastfri/structures/Declaration.hpp>
#include <libastfri/structures/Expression.hpp>

#include <clang/AST/Expr.h>
#include <clang/AST/Stmt.h>
#include <fstream>
#include <libastfri-cpp/ClangManagement.hpp>
#include <libastfri-cpp/ClangTools.hpp>
#include <memory>
#include <sstream>

namespace lsfs = libastfri::structures;

namespace libastfri::cpp
{
lsfs::Type* ClangTools::convertType(clang::QualType qt)
{
    auto& typeFac = libastfri::factories::TypeFactory::getInstance();

    if (qt->isIntegerType())
    {
        return typeFac.getIntType();
    }

    if (qt->isFloatingType())
    {
        return typeFac.getFloatType();
    }

    if (qt->isCharType())
    {
        return typeFac.getCharType();
    }

    if (qt->isBooleanType())
    {
        return typeFac.getBoolType();
    }

    if (qt->isVoidType())
    {
        return typeFac.getVoidType();
    }

    return typeFac.getUserType(qt.getAsString());
}

lsfs::BinaryOperators ClangTools::convertBinaryOperator(
    clang::BinaryOperator::Opcode op
)
{
    switch (op)
    {
    case clang::BinaryOperator::Opcode::BO_Assign:
        return lsfs::BinaryOperators::Assign;
    case clang::BinaryOperator::Opcode::BO_Add:
        return lsfs::BinaryOperators::Add;
    case clang::BinaryOperator::Opcode::BO_Sub:
        return lsfs::BinaryOperators::Subtract;
    case clang::BinaryOperator::Opcode::BO_Mul:
        return lsfs::BinaryOperators::Multiply;
    case clang::BinaryOperator::Opcode::BO_Div:
        return lsfs::BinaryOperators::Divide;
    case clang::BinaryOperator::Opcode::BO_Rem:
        return lsfs::BinaryOperators::Modulo;
    case clang::BinaryOperator::Opcode::BO_LT:
        return lsfs::BinaryOperators::Less;
    case clang::BinaryOperator::Opcode::BO_GT:
        return lsfs::BinaryOperators::Greater;
    case clang::BinaryOperator::Opcode::BO_LE:
        return lsfs::BinaryOperators::LessEqual;
    case clang::BinaryOperator::Opcode::BO_GE:
        return lsfs::BinaryOperators::GreaterEqual;
    case clang::BinaryOperator::Opcode::BO_EQ:
        return lsfs::BinaryOperators::Equal;
    case clang::BinaryOperator::Opcode::BO_NE:
        return lsfs::BinaryOperators::NotEqual;
        //   case clang::BinaryOperator::Opcode::BO_And:
        //     return lsfs::BinaryOperators::AND;
        //   case clang::BinaryOperator::Opcode::BO_Or:
        //     return lsfs::BinaryOperators::OR;
    }

    throw std::runtime_error("Unknown binary operator");
}

lsfs::UnaryOperators ClangTools::convertUnaryOperator(
    clang::UnaryOperator::Opcode op
)
{
    switch (op)
    {
    case clang::UnaryOperator::Opcode::UO_Minus:
        return lsfs::UnaryOperators::Negative;
    case clang::UnaryOperator::Opcode::UO_Not:
        return lsfs::UnaryOperators::Not;
    }

    throw std::runtime_error("Unknown unary operator");
}

void ClangTools::BeginClangTreeVisit(
    std::string pathToCode,
    lsfs::TranslationUnit& visitedTranslationUnit
)
{
    // nacitanie vstupneho suboru
    auto ifst = std::ifstream(pathToCode);
    auto ist  = std::stringstream();
    ist << ifst.rdbuf();
    std::string code = ist.str();

    // spusti clang prehliadku
    clang::tooling::runToolOnCodeWithArgs(
        std::make_unique<libastfri::cpp::ClangTraverseAction>(
            visitedTranslationUnit
        ),
        code,
        {""}
    );
}

} // namespace libastfri::cpp