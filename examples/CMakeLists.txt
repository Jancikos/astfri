add_executable(
    astfri-cpp-example main.cpp
)

target_link_libraries(
    astfri-cpp-example PRIVATE astfri-cpp astfri-output
)