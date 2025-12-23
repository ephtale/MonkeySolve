#include "SparseMatrix.hpp"
#include <stdexcept>
#include <algorithm>
#include <tuple>

namespace MonkeySolve {

// Constructors
SparseMatrix::SparseMatrix() : rows_(0), cols_(0), nnz_(0), finalized_(false) {}

SparseMatrix::SparseMatrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), nnz_(0), finalized_(false) {}

// Build from triplets - store in temporary format
void SparseMatrix::addValue(size_t row, size_t col, double value) {
    if (finalized_) {
        throw std::runtime_error("Cannot add values after finalize() has been called");
    }
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    if (value != 0.0) {
        // Store as triplets - will be sorted in finalize()
        row_indices_.push_back(row);
        col_indices_.push_back(col);
        values_.push_back(value);
    }
}

void SparseMatrix::finalize() {
    if (finalized_) {
        return;  // Already finalized
    }
    
    if (values_.empty()) {
        nnz_ = 0;
        row_ptr_.assign(rows_ + 1, 0);
        finalized_ = true;
        return;
    }
    
    // Build sorted CSR format from triplets
    std::vector<std::tuple<size_t, size_t, double>> triplets;
    
    for (size_t i = 0; i < values_.size(); ++i) {
        triplets.push_back(std::make_tuple(row_indices_[i], col_indices_[i], values_[i]));
    }
    
    // Sort by row, then by column
    std::sort(triplets.begin(), triplets.end());
    
    // Build CSR arrays
    values_.clear();
    col_indices_.clear();
    row_ptr_.assign(rows_ + 1, 0);
    
    for (const auto& triplet : triplets) {
        size_t row = std::get<0>(triplet);
        size_t col = std::get<1>(triplet);
        double val = std::get<2>(triplet);
        
        values_.push_back(val);
        col_indices_.push_back(col);
        row_ptr_[row + 1]++;
    }
    
    // Convert counts to cumulative pointers
    for (size_t i = 0; i < rows_; ++i) {
        row_ptr_[i + 1] += row_ptr_[i];
    }
    
    nnz_ = values_.size();
    row_indices_.clear();  // No longer needed
    finalized_ = true;
}

// Access
double SparseMatrix::operator()(size_t i, size_t j) const {
    if (!finalized_) {
        throw std::runtime_error("Matrix must be finalized before access");
    }
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    
    // Search for the element in row i
    for (size_t k = row_ptr_[i]; k < row_ptr_[i + 1]; ++k) {
        if (col_indices_[k] == j) {
            return values_[k];
        }
    }
    return 0.0;
}

// Dimensions
size_t SparseMatrix::rows() const {
    return rows_;
}

size_t SparseMatrix::cols() const {
    return cols_;
}

size_t SparseMatrix::nnz() const {
    return nnz_;
}

// Operations
Vector SparseMatrix::multiply(const Vector& x) const {
    if (!finalized_) {
        throw std::runtime_error("Matrix must be finalized before operations");
    }
    if (cols_ != x.size()) {
        throw std::invalid_argument("Matrix columns must match vector size");
    }
    
    Vector result(rows_, 0.0);
    for (size_t i = 0; i < rows_; ++i) {
        double sum = 0.0;
        for (size_t k = row_ptr_[i]; k < row_ptr_[i + 1]; ++k) {
            sum += values_[k] * x[col_indices_[k]];
        }
        result[i] = sum;
    }
    return result;
}

// Data access
const std::vector<double>& SparseMatrix::values() const {
    return values_;
}

const std::vector<size_t>& SparseMatrix::colIndices() const {
    return col_indices_;
}

const std::vector<size_t>& SparseMatrix::rowPtr() const {
    return row_ptr_;
}

} // namespace MonkeySolve
