#include <libastfri/factories/StatementFactory.hpp>

#include <libastfri-cpp/ClangManagement.hpp>
#include <libastfri-cpp/ClangTools.hpp>

#include <libastfri-output/CodeVisitor.hpp>
#include <libastfri-output/StreamWriter.hpp>

#include <iostream>

int main (int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage needs least 1 parameter: path to .cpp file"
                  << std::endl;
        return 1;
    }
    // nacitavenie cpp zdrojakov
    auto* visitedTranslationUnit
        = libastfri::factories::StatementFactory::getInstance()
              .createTranslationUnit({});

    libastfri::cpp::ClangTools::BeginClangTreeVisit(
        argv[1],
        *visitedTranslationUnit
    );

    // vypis z CodeVisitora
    std::cout << "CodeVisitor output: " << std::endl;
    libastfri::output::StreamWriter writer(std::cout);
    libastfri::output::CodeVisitor codeVisitor(writer);

    codeVisitor.Output(*visitedTranslationUnit);

    return 0;
}