#include "SparseMatrix.hpp"
#include "SparseSolver.hpp"
#include "Vector.hpp"
#include <iostream>
#include <iomanip>

using namespace MonkeySolve;

int main() {
    std::cout << "=== Sparse Linear Solver Example ===" << std::endl;
    std::cout << std::endl;
    
    // Example 1: Simple 3x3 sparse symmetric positive definite system
    // 4x - y = 1
    // -x + 4y - z = 2
    // -y + 4z = 3
    
    std::cout << "Solving sparse system Ax = b using Conjugate Gradient:" << std::endl;
    std::cout << "4x - y = 1" << std::endl;
    std::cout << "-x + 4y - z = 2" << std::endl;
    std::cout << "-y + 4z = 3" << std::endl;
    std::cout << std::endl;
    
    SparseMatrix A(3, 3);
    A.addValue(0, 0, 4.0);
    A.addValue(0, 1, -1.0);
    A.addValue(1, 0, -1.0);
    A.addValue(1, 1, 4.0);
    A.addValue(1, 2, -1.0);
    A.addValue(2, 1, -1.0);
    A.addValue(2, 2, 4.0);
    A.finalize();
    
    std::cout << "Matrix sparsity: " << A.nnz() << " non-zeros out of " 
              << (A.rows() * A.cols()) << " elements" << std::endl;
    std::cout << std::endl;
    
    Vector b({1.0, 2.0, 3.0});
    
    try {
        Vector x = SparseSolver::solveCG(A, b, 1e-10, 1000);
        
        std::cout << "Solution:" << std::endl;
        std::cout << std::fixed << std::setprecision(6);
        for (size_t i = 0; i < x.size(); ++i) {
            std::cout << "x[" << i << "] = " << x[i] << std::endl;
        }
        std::cout << std::endl;
        
        // Verify solution
        Vector Ax = A.multiply(x);
        std::cout << "Verification (Ax):" << std::endl;
        for (size_t i = 0; i < Ax.size(); ++i) {
            std::cout << "Ax[" << i << "] = " << Ax[i] 
                      << " (expected: " << b[i] << ")" << std::endl;
        }
        std::cout << std::endl;
        
        // Calculate residual
        Vector residual = Ax - b;
        double residual_norm = residual.norm();
        std::cout << "Residual norm: " << residual_norm << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << std::endl;
    
    // Example 2: Larger sparse system (tridiagonal matrix)
    std::cout << "=== Larger Sparse System Example (100x100 tridiagonal) ===" << std::endl;
    std::cout << std::endl;
    
    size_t n = 100;
    SparseMatrix A2(n, n);
    
    // Create a tridiagonal matrix (symmetric positive definite)
    // Using a smaller diagonal value to ensure positive definiteness
    for (size_t i = 0; i < n; ++i) {
        if (i > 0) {
            A2.addValue(i, i-1, -1.0);
        }
        A2.addValue(i, i, 3.0);  // Changed from 4.0 to 3.0 for better conditioning
        if (i < n - 1) {
            A2.addValue(i, i+1, -1.0);
        }
    }
    A2.finalize();
    
    std::cout << "Matrix size: " << A2.rows() << "x" << A2.cols() << std::endl;
    std::cout << "Matrix sparsity: " << A2.nnz() << " non-zeros out of " 
              << (A2.rows() * A2.cols()) << " elements" << std::endl;
    std::cout << "Sparsity ratio: " << (100.0 * A2.nnz() / (A2.rows() * A2.cols())) 
              << "%" << std::endl;
    std::cout << std::endl;
    
    // Create right-hand side
    Vector b2(n, 1.0);
    
    try {
        Vector x2 = SparseSolver::solveCG(A2, b2, 1e-10, 10000);
        
        std::cout << "Solution computed successfully" << std::endl;
        std::cout << "First 5 elements:" << std::endl;
        for (size_t i = 0; i < 5 && i < x2.size(); ++i) {
            std::cout << "x[" << i << "] = " << x2[i] << std::endl;
        }
        std::cout << std::endl;
        
        // Verify solution
        Vector Ax2 = A2.multiply(x2);
        Vector residual2 = Ax2 - b2;
        double residual_norm2 = residual2.norm();
        std::cout << "Residual norm: " << residual_norm2 << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
