#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

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

  auto action = std::make_unique<AstfriClangTraverseAction>();

  // todo - premysliet ci v maine uplne neabstrahovat od pouzutia clangu
  clang::tooling::runToolOnCodeWithArgs(
      std::make_unique<AstfriClangTraverseAction>(), code, {""});


  // auto translationUnit = action->getVisitedTranslationUnit();

  return 0;
}