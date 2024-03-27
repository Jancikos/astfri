#include <iostream>
#include <libastfri-cpp/ClangManagement.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri-output/CodeVisitor.hpp>

#include "libastfri-cpp/ClangTools.hpp"
#include "libastfri/structures/Statement.hpp"

int main (int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage needs 1 parameter: path to .cpp file" << std::endl;
        return 1;
    }

    auto* visitedTranslationUnit
        = libastfri::factories::StatementFactory::getInstance()
              .createTranslationUnit({});

    libastfri::cpp::ClangTools::BeginClangTreeVisit(
        argv[1],
        *visitedTranslationUnit
    );

    // vypis z CodeVisitora
    std::cout << "CodeVisitor output: " << std::endl;
    libastfri::output::CodeVisitor codeVisitor(std::cout);

    codeVisitor.Visit(*visitedTranslationUnit);

    return 0;
}