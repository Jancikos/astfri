file(
    GLOB SOURCES ./*.cpp
)

# https://github.com/firolino/clang-tool/tree/master

set(
    CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    "${PROJECT_SOURCE_DIR}/cmake/modules"
)

find_package(
    LLVM REQUIRED
)

find_package(
    Clang REQUIRED
)

add_library(
    astfri-cpp STATIC ${SOURCES}
)

target_compile_options(
    astfri-cpp PUBLIC "-fno-rtti" "-Wall" "-Wextra"
)

target_link_libraries(
    astfri-cpp PUBLIC ${CLANG_LIBS} ${LLVM_LIBS_CORE} ${LLVM_LDFLAGS}
)

target_link_libraries(
    astfri-cpp PUBLIC astfri-core
)

target_include_directories(
    astfri-cpp PUBLIC ${PROJECT_SOURCE_DIR}
)
