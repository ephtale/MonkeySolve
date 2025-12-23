#ifndef MONKEYSOLVE_SPARSEMATRIX_HPP
#define MONKEYSOLVE_SPARSEMATRIX_HPP

#include "Vector.hpp"
#include <vector>
#include <cstddef>

namespace MonkeySolve {

// Compressed Sparse Row (CSR) format
class SparseMatrix {
private:
    std::vector<double> values_;      // Non-zero values
    std::vector<size_t> col_indices_; // Column indices
    std::vector<size_t> row_ptr_;     // Row pointers
    std::vector<size_t> row_indices_; // Temporary storage for row indices during construction
    size_t rows_;
    size_t cols_;
    size_t nnz_;                      // Number of non-zeros
    bool finalized_;                  // Track if finalize() has been called

public:
    // Constructors
    SparseMatrix();
    SparseMatrix(size_t rows, size_t cols);
    
    // Build from triplets (row, col, value)
    void addValue(size_t row, size_t col, double value);
    void finalize();
    
    // Access
    double operator()(size_t i, size_t j) const;
    
    // Dimensions
    size_t rows() const;
    size_t cols() const;
    size_t nnz() const;
    
    // Operations
    Vector multiply(const Vector& x) const;
    
    // Data access for advanced users
    const std::vector<double>& values() const;
    const std::vector<size_t>& colIndices() const;
    const std::vector<size_t>& rowPtr() const;
};

} // namespace MonkeySolve

#endif // MONKEYSOLVE_SPARSEMATRIX_HPP
