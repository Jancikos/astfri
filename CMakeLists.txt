cmake_minimum_required(
    VERSION 3.19
)

project(
    libast
    VERSION     0.0.1
    DESCRIPTION "A abstract syntax tree library for C++."
    LANGUAGES   CXX
)

add_subdirectory(libastfri)
add_subdirectory(libastfri-cpp)
add_subdirectory(examples)
