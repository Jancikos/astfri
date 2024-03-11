file(GLOB SOURCES test.cpp)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${PROJECT_SOURCE_DIR}/cmake/modules"
)
 
find_package(LibClangTooling REQUIRED)

add_definitions(${LibClangTooling_DEFINITIONS})
 
include_directories(
  ${LibClangTooling_INCLUDE_DIRS}
)

add_library(
    astfri-cpp STATIC ${SOURCES}
)

message("!!!!!! ${LibClangTooling_LIBRARIES}")

target_link_options(
    astfri-cpp
    PUBLIC ${LibClangTooling_LIBRARIES}
)

target_link_libraries(astfri-cpp PUBLIC ${LibClangTooling_LIBRARIES})

target_link_libraries(astfri-cpp PUBLIC astfri-core)

target_include_directories(astfri-cpp PUBLIC ${PROJECT_SOURCE_DIR})
