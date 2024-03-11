file(GLOB SOURCES test.cpp)

add_library(
    astfri-cpp STATIC ${SOURCES}
)

target_link_libraries(astfri-cpp PUBLIC astfri-core)

target_include_directories(astfri-cpp PUBLIC ${PROJECT_SOURCE_DIR})
