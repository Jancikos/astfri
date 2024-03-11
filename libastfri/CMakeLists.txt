file(GLOB SOURCES structures/*.cpp factories/*.cpp utils/*.cpp)

add_library(
    astfri-core STATIC ${SOURCES}
)

target_include_directories(astfri-core PUBLIC ${PROJECT_SOURCE_DIR})