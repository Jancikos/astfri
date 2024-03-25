#include <iostream>
#include <libastfri-cpp/ClangManagement.hpp>
#include <libastfri/factories/StatementFactory.hpp>

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

    // vypis translation unit
    std::cout << "Translation unit: " << std::endl;
    int i = 0;
    for (auto* fun : visitedTranslationUnit->functions)
    {
        std::cout << "  Function: " << fun->name << std::endl;
        for (auto* param : fun->parameters)
        {
            std::cout << "    Param: " << param->name << " ("
                      << param->type->name << ")" << std::endl;
        }

        std::cout << "    Body: " << std::endl;
        for (auto* stmt : fun->body->statements)
        {
            // tu zrejme prichadza potreba visitora pre vypis...
            std::cout << "      " << i++ << ": " << stmt->toString()
                      << std::endl;
        }
    }

    return 0;
}