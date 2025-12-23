# MonkeySolve

A performant C++ library for solving linear systems of equations (Ax = b) with support for both dense and sparse matrices.

## Features

- **Dense Linear Solver**: LU decomposition with partial pivoting for general dense systems
- **Sparse Linear Solver**: Conjugate Gradient (CG) method for symmetric positive definite sparse systems
- **Efficient Data Structures**: 
  - Dense matrices with row-major storage
  - Sparse matrices in Compressed Sparse Row (CSR) format
  - Vector operations with BLAS-like interface
- **Performance Optimized**: Designed for computational efficiency with modern C++17

## Building

### Requirements
- CMake 3.10 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

This will build:
- `libmonkeysolve.a` - The static library
- `dense_example` - Dense solver example program
- `sparse_example` - Sparse solver example program

## Usage

### Dense Linear Solver

```cpp
#include "DenseMatrix.hpp"
#include "DenseSolver.hpp"
#include "Vector.hpp"

using namespace MonkeySolve;

// Create a 3x3 system: Ax = b
DenseMatrix A(3, 3);
A(0, 0) = 3.0;  A(0, 1) = 2.0;   A(0, 2) = -1.0;
A(1, 0) = 2.0;  A(1, 1) = -2.0;  A(1, 2) = 4.0;
A(2, 0) = -1.0; A(2, 1) = 0.5;   A(2, 2) = -1.0;

Vector b({1.0, -2.0, 0.0});

// Solve the system
Vector x = DenseSolver::solve(A, b);
```

### Sparse Linear Solver

```cpp
#include "SparseMatrix.hpp"
#include "SparseSolver.hpp"
#include "Vector.hpp"

using namespace MonkeySolve;

// Create a sparse matrix (symmetric positive definite)
SparseMatrix A(3, 3);
A.addValue(0, 0, 4.0);
A.addValue(0, 1, -1.0);
A.addValue(1, 0, -1.0);
A.addValue(1, 1, 4.0);
A.addValue(1, 2, -1.0);
A.addValue(2, 1, -1.0);
A.addValue(2, 2, 4.0);
A.finalize();  // Must call finalize() after adding all values

Vector b({1.0, 2.0, 3.0});

// Solve using Conjugate Gradient
Vector x = SparseSolver::solveCG(A, b, 1e-10, 1000);
```

## Running Examples

After building, run the example programs:

```bash
./dense_example
./sparse_example
```

## Architecture

### Core Components

- **Vector**: 1D array with vector arithmetic operations
- **DenseMatrix**: 2D dense matrix with row-major storage
- **SparseMatrix**: Compressed Sparse Row (CSR) format for efficient sparse storage
- **DenseSolver**: LU decomposition-based solver for general dense systems
- **SparseSolver**: Iterative Conjugate Gradient solver for sparse SPD systems

### Algorithms

#### Dense Solver
Uses LU decomposition with partial pivoting:
1. Factorize A = PLU (where P is a permutation matrix)
2. Solve Ly = Pb (forward substitution)
3. Solve Ux = y (backward substitution)

#### Sparse Solver
Uses Conjugate Gradient iteration:
- Suitable for symmetric positive definite matrices
- Iterative method that converges to the solution
- Memory efficient for large sparse systems
- Configurable tolerance and maximum iterations

## Performance Characteristics

- **Dense Solver**: O(n³) time complexity, O(n²) space complexity
- **Sparse Solver**: O(k·nnz) time per iteration where k is iteration count and nnz is number of non-zeros
- **Sparse Storage**: Only stores non-zero elements, reducing memory from O(n²) to O(nnz)

## License

See LICENSE file for details.
