file(GLOB SOURCES structures/*.cpp factories/*.cpp utils/*.cpp)

add_executable(
    ast main.cpp ${SOURCES}
)

target_include_directories(ast PUBLIC ${PROJECT_SOURCE_DIR})