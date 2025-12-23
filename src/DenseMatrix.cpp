#include "DenseMatrix.hpp"
#include <stdexcept>

namespace MonkeySolve {

// Constructors
DenseMatrix::DenseMatrix() : rows_(0), cols_(0) {}

DenseMatrix::DenseMatrix(size_t rows, size_t cols, double init_value)
    : data_(rows * cols, init_value), rows_(rows), cols_(cols) {}

DenseMatrix::DenseMatrix(size_t rows, size_t cols, const std::vector<double>& values)
    : data_(values), rows_(rows), cols_(cols) {
    if (values.size() != rows * cols) {
        throw std::invalid_argument("Data size must match rows * cols");
    }
}

// Access (row-major storage)
double& DenseMatrix::operator()(size_t i, size_t j) {
    return data_[i * cols_ + j];
}

const double& DenseMatrix::operator()(size_t i, size_t j) const {
    return data_[i * cols_ + j];
}

double& DenseMatrix::at(size_t i, size_t j) {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[i * cols_ + j];
}

const double& DenseMatrix::at(size_t i, size_t j) const {
    if (i >= rows_ || j >= cols_) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data_[i * cols_ + j];
}

// Dimensions
size_t DenseMatrix::rows() const {
    return rows_;
}

size_t DenseMatrix::cols() const {
    return cols_;
}

// Operations
Vector DenseMatrix::multiply(const Vector& x) const {
    if (cols_ != x.size()) {
        throw std::invalid_argument("Matrix columns must match vector size");
    }
    
    Vector result(rows_, 0.0);
    for (size_t i = 0; i < rows_; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < cols_; ++j) {
            sum += (*this)(i, j) * x[j];
        }
        result[i] = sum;
    }
    return result;
}

DenseMatrix DenseMatrix::transpose() const {
    DenseMatrix result(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

// Data access
const std::vector<double>& DenseMatrix::data() const {
    return data_;
}

std::vector<double>& DenseMatrix::data() {
    return data_;
}

} // namespace MonkeySolve
