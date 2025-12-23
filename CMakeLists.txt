cmake_minimum_required(VERSION 3.10)
project(MonkeySolve VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for optimization
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Library sources
set(LIBRARY_SOURCES
    src/DenseMatrix.cpp
    src/SparseMatrix.cpp
    src/Vector.cpp
    src/DenseSolver.cpp
    src/SparseSolver.cpp
)

# Create static library
add_library(monkeysolve STATIC ${LIBRARY_SOURCES})

# Examples
add_executable(dense_example examples/dense_example.cpp)
target_link_libraries(dense_example monkeysolve)

add_executable(sparse_example examples/sparse_example.cpp)
target_link_libraries(sparse_example monkeysolve)

# Installation
install(TARGETS monkeysolve
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)
