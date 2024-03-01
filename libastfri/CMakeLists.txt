add_executable(
    ast main.cpp factories/ExpressionFactory.cpp
)

target_include_directories(ast PUBLIC ${PROJECT_SOURCE_DIR})