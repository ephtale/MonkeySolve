#include "DenseMatrix.hpp"
#include "DenseSolver.hpp"
#include "Vector.hpp"
#include <iostream>
#include <iomanip>

using namespace MonkeySolve;

int main() {
    std::cout << "=== Dense Linear Solver Example ===" << std::endl;
    std::cout << std::endl;
    
    // Example 1: Simple 3x3 system
    // 3x + 2y - z = 1
    // 2x - 2y + 4z = -2
    // -x + 0.5y - z = 0
    
    std::cout << "Solving system Ax = b:" << std::endl;
    std::cout << "3x + 2y - z = 1" << std::endl;
    std::cout << "2x - 2y + 4z = -2" << std::endl;
    std::cout << "-x + 0.5y - z = 0" << std::endl;
    std::cout << std::endl;
    
    DenseMatrix A(3, 3);
    A(0, 0) = 3.0;  A(0, 1) = 2.0;   A(0, 2) = -1.0;
    A(1, 0) = 2.0;  A(1, 1) = -2.0;  A(1, 2) = 4.0;
    A(2, 0) = -1.0; A(2, 1) = 0.5;   A(2, 2) = -1.0;
    
    Vector b({1.0, -2.0, 0.0});
    
    try {
        Vector x = DenseSolver::solve(A, b);
        
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
    
    // Example 2: Larger system
    std::cout << "=== Larger System Example (5x5) ===" << std::endl;
    std::cout << std::endl;
    
    DenseMatrix A2(5, 5);
    // Create a diagonally dominant matrix for stability
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (i == j) {
                A2(i, j) = 10.0;
            } else {
                A2(i, j) = 1.0 / (std::abs(static_cast<int>(i) - static_cast<int>(j)) + 1.0);
            }
        }
    }
    
    Vector b2({1.0, 2.0, 3.0, 4.0, 5.0});
    
    try {
        Vector x2 = DenseSolver::solve(A2, b2);
        
        std::cout << "Solution:" << std::endl;
        for (size_t i = 0; i < x2.size(); ++i) {
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
