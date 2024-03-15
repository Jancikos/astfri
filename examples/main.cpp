#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri-cpp/clang_management.hpp>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage needs 1 parameter: path to .cpp file" << std::endl;
    return 1;
  }

  auto ifst = std::ifstream(argv[1]);
  auto ist = std::stringstream();
  ist << ifst.rdbuf();
  std::string code = ist.str();


  auto *visitedTranslationUnit = libastfri::factories::StatementFactory::getInstance()
                                   .createTranslationUnitStatement({});

  // todo - premysliet ci v maine uplne neabstrahovat od pouzutia clangu
  clang::tooling::runToolOnCodeWithArgs(
      std::make_unique<AstfriClangTraverseAction>(*visitedTranslationUnit), code, {""});


// vypis translation unit
    std::cout << "Translation unit: " << std::endl;
    int i = 0;
    for (auto *fun : visitedTranslationUnit->functions) {
        std::cout << "  Function: " << fun->name << std::endl;
        for (auto *param : fun->parameters) {
            std::cout << "    Param: " << param->name << " (" << param->type->name << ")" << std::endl;
        }
    }

  return 0;
}