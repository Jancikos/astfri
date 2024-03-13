#include <memory>
#include <libastfri-cpp/test.hpp>
#include <fstream>
#include <sstream>

#include <libastfri/structures/Expression.hpp>
#include <libastfri/structures/Statement.hpp>

#include <libastfri/factories/ExpressionFactory.hpp>
#include <libastfri/factories/FunctionFactory.hpp>
#include <libastfri/factories/StatementFactory.hpp>
#include <libastfri/factories/TypeFactory.hpp>

using namespace libastfri::structures;
using namespace libastfri::factories;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage needs 1 parameter: path to .cpp file" << std::endl;
        return 1;
    }

    auto ifst = std::ifstream(argv[1]);
    auto ist = std::stringstream();
    ist << ifst.rdbuf();
    std::string code = ist.str();

    clang::tooling::runToolOnCodeWithArgs(std::make_unique<FindClassAction>(), code, {""});

    return 0;
}