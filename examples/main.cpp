#include <libastfri-output/formatters/PlainTextFormatter.hpp>
#include <libastfri/factories/StatementFactory.hpp>

#include <libastfri-cpp/ClangManagement.hpp>
#include <libastfri-cpp/ClangTools.hpp>

#include <libastfri-output/visitors/CodeVisitor.hpp>
#include <libastfri-output/visitors/PseudocodeVisitor.hpp>
#include <libastfri-output/writers/StreamWriter.hpp>

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
    libastfrioutput::writers::StreamWriter writer(std::cout);
    libastfrioutput::formatters::PlainTextFormatter textStdOutputFormatter(writer);

    libastfrioutput::visitors::CodeVisitor codeVisitor(textStdOutputFormatter);
    libastfrioutput::visitors::PseudocodeVisitor pseudocodeVisitor(textStdOutputFormatter);

    std::cout << "CodeVisitor output: " << std::endl;
    codeVisitor.Output(*visitedTranslationUnit);

    std::cout << std::endl << "PseudocodeVisitor output: " << std::endl;
    pseudocodeVisitor.Output(*visitedTranslationUnit);

    return 0;
}