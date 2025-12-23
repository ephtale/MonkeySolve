#include "SparseSolver.hpp"
#include <cmath>
#include <stdexcept>

namespace MonkeySolve {

Vector SparseSolver::solveCG(const SparseMatrix& A, const Vector& b, 
                              double tolerance, size_t max_iterations) {
    if (A.rows() != A.cols()) {
        throw std::invalid_argument("Matrix must be square for CG solver");
    }
    if (A.rows() != b.size()) {
        throw std::invalid_argument("Matrix rows must match vector size");
    }
    
    size_t n = A.rows();
    
    // Initial guess x = 0
    Vector x(n, 0.0);
    
    // r = b - Ax (initially r = b since x = 0)
    Vector r = b;
    
    // p = r
    Vector p = r;
    
    // rs_old = r' * r
    double rs_old = r.dot(r);
    
    if (std::sqrt(rs_old) < tolerance) {
        return x;  // Already converged
    }
    
    for (size_t iter = 0; iter < max_iterations; ++iter) {
        // Ap = A * p
        Vector Ap = A.multiply(p);
        
        // alpha = rs_old / (p' * Ap)
        double pAp = p.dot(Ap);
        
        // Check if matrix is positive definite
        // For SPD matrices, p'*Ap should be strictly positive
        if (pAp <= 0.0) {
            throw std::runtime_error("CG method failed: matrix may not be positive definite (p'Ap <= 0)");
        }
        
        // Also check for numerical issues
        if (pAp < 1e-100) {
            throw std::runtime_error("CG method failed: numerical instability detected");
        }
        
        double alpha = rs_old / pAp;
        
        // x = x + alpha * p
        x = x + p * alpha;
        
        // r = r - alpha * Ap
        r = r - Ap * alpha;
        
        // rs_new = r' * r
        double rs_new = r.dot(r);
        
        // Check convergence
        if (hasConverged(std::sqrt(rs_new), tolerance)) {
            return x;
        }
        
        // beta = rs_new / rs_old
        double beta = rs_new / rs_old;
        
        // p = r + beta * p
        p = r + p * beta;
        
        rs_old = rs_new;
    }
    
    // Did not converge within max_iterations
    throw std::runtime_error("CG solver did not converge within maximum iterations");
}

bool SparseSolver::hasConverged(double residual_norm, double tolerance) {
    return residual_norm < tolerance;
}

} // namespace MonkeySolve
