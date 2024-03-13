#include <memory>
#include <iostream>
#include <fstream>
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

    clang::tooling::runToolOnCodeWithArgs(std::make_unique<AstfriClangTraverseAction>(), code, {""});

    return 0;
}