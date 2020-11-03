cmake_minimum_required(VERSION 3.10)
project(TFHE CXX)
set(CMAKE_CXX_FLAGS "-march=native -std=c++17 -O3")

add_subdirectory(src)
add_subdirectory(RANDEN)
add_subdirectory(SPQLIOS)

OPTION(USE_80BIT_SECURITY "use 80bit security parameter" OFF)
OPTION(ENABLE_TEST "Buiid tests" OFF)
if(USE_80BIT_SECURITY)
    add_compile_definitions(USE_80BIT_SECURITY)
endif()

add_subdirectory(test)



