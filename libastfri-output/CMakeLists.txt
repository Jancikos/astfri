file(
    GLOB SOURCES ./writers/*.cpp ./formatters/*.cpp ./visitors/*.cpp
)

add_library(
    astfri-output STATIC ${SOURCES}
)

target_compile_options(
    astfri-output PUBLIC
)

target_link_libraries(
    astfri-output PUBLIC astfri-core
)

target_include_directories(
    astfri-output PUBLIC ${PROJECT_SOURCE_DIR}
)
