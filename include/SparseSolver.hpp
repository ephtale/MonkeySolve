#ifndef MONKEYSOLVE_SPARSESOLVER_HPP
#define MONKEYSOLVE_SPARSESOLVER_HPP

#include "SparseMatrix.hpp"
#include "Vector.hpp"

namespace MonkeySolve {

class SparseSolver {
public:
    // Solve Ax = b using Conjugate Gradient method (for symmetric positive definite matrices)
    static Vector solveCG(const SparseMatrix& A, const Vector& b, 
                          double tolerance = 1e-10, size_t max_iterations = 1000);
    
private:
    // Helper function for convergence check
    static bool hasConverged(double residual_norm, double tolerance);
};

} // namespace MonkeySolve

#endif // MONKEYSOLVE_SPARSESOLVER_HPP
