#include "DenseSolver.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

namespace MonkeySolve {

Vector DenseSolver::solve(const DenseMatrix& A, const Vector& b) {
    if (A.rows() != A.cols()) {
        throw std::invalid_argument("Matrix must be square");
    }
    if (A.rows() != b.size()) {
        throw std::invalid_argument("Matrix rows must match vector size");
    }
    
    size_t n = A.rows();
    
    // Create a copy of A for LU decomposition
    DenseMatrix LU = A;
    std::vector<size_t> perm(n);
    for (size_t i = 0; i < n; ++i) {
        perm[i] = i;
    }
    
    // Perform LU decomposition with partial pivoting
    luDecomposition(LU, perm);
    
    // Solve Ly = Pb using forward substitution
    Vector y = forwardSubstitution(LU, b, perm);
    
    // Solve Ux = y using backward substitution
    Vector x = backwardSubstitution(LU, y);
    
    return x;
}

void DenseSolver::luDecomposition(DenseMatrix& A, std::vector<size_t>& perm) {
    size_t n = A.rows();
    
    for (size_t k = 0; k < n; ++k) {
        // Partial pivoting: find the pivot
        double max_val = std::abs(A(k, k));
        size_t pivot_row = k;
        
        for (size_t i = k + 1; i < n; ++i) {
            double val = std::abs(A(i, k));
            if (val > max_val) {
                max_val = val;
                pivot_row = i;
            }
        }
        
        if (max_val < 1e-14) {
            throw std::runtime_error("Matrix is singular or nearly singular");
        }
        
        // Swap rows in permutation
        if (pivot_row != k) {
            std::swap(perm[k], perm[pivot_row]);
            for (size_t j = 0; j < n; ++j) {
                std::swap(A(k, j), A(pivot_row, j));
            }
        }
        
        // Perform LU decomposition
        for (size_t i = k + 1; i < n; ++i) {
            A(i, k) /= A(k, k);
            for (size_t j = k + 1; j < n; ++j) {
                A(i, j) -= A(i, k) * A(k, j);
            }
        }
    }
}

Vector DenseSolver::forwardSubstitution(const DenseMatrix& L, const Vector& b, 
                                        const std::vector<size_t>& perm) {
    size_t n = L.rows();
    Vector y(n);
    
    for (size_t i = 0; i < n; ++i) {
        double sum = b[perm[i]];
        for (size_t j = 0; j < i; ++j) {
            sum -= L(i, j) * y[j];
        }
        y[i] = sum;
    }
    
    return y;
}

Vector DenseSolver::backwardSubstitution(const DenseMatrix& U, const Vector& y) {
    size_t n = U.rows();
    Vector x(n);
    
    for (int i = n - 1; i >= 0; --i) {
        double sum = y[i];
        for (size_t j = i + 1; j < n; ++j) {
            sum -= U(i, j) * x[j];
        }
        x[i] = sum / U(i, i);
    }
    
    return x;
}

} // namespace MonkeySolve
