#ifndef MONKEYSOLVE_DENSEMATRIX_HPP
#define MONKEYSOLVE_DENSEMATRIX_HPP

#include "Vector.hpp"
#include <vector>
#include <cstddef>

namespace MonkeySolve {

class DenseMatrix {
private:
    std::vector<double> data_;
    size_t rows_;
    size_t cols_;

public:
    // Constructors
    DenseMatrix();
    DenseMatrix(size_t rows, size_t cols, double init_value = 0.0);
    DenseMatrix(size_t rows, size_t cols, const std::vector<double>& values);
    
    // Access
    double& operator()(size_t i, size_t j);
    const double& operator()(size_t i, size_t j) const;
    double& at(size_t i, size_t j);
    const double& at(size_t i, size_t j) const;
    
    // Dimensions
    size_t rows() const;
    size_t cols() const;
    
    // Operations
    Vector multiply(const Vector& x) const;
    DenseMatrix transpose() const;
    
    // Data access
    const std::vector<double>& data() const;
    std::vector<double>& data();
};

} // namespace MonkeySolve

#endif // MONKEYSOLVE_DENSEMATRIX_HPP
