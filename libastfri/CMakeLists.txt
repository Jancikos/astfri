add_executable(
    ast main.cpp factories/ExpressionFactory.cpp factories/StatementFactory.cpp factories/FunctionFactory.cpp factories/TypeFactory.cpp
)

target_include_directories(ast PUBLIC ${PROJECT_SOURCE_DIR})