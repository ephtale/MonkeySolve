#include "Vector.hpp"
#include <stdexcept>
#include <cmath>

namespace MonkeySolve {

// Constructors
Vector::Vector() : size_(0) {}

Vector::Vector(size_t size, double init_value) 
    : data_(size, init_value), size_(size) {}

Vector::Vector(const std::vector<double>& values) 
    : data_(values), size_(values.size()) {}

// Access
double& Vector::operator[](size_t i) {
    return data_[i];
}

const double& Vector::operator[](size_t i) const {
    return data_[i];
}

double& Vector::at(size_t i) {
    if (i >= size_) {
        throw std::out_of_range("Vector index out of range");
    }
    return data_[i];
}

const double& Vector::at(size_t i) const {
    if (i >= size_) {
        throw std::out_of_range("Vector index out of range");
    }
    return data_[i];
}

// Size
size_t Vector::size() const {
    return size_;
}

void Vector::resize(size_t new_size, double init_value) {
    data_.resize(new_size, init_value);
    size_ = new_size;
}

// Operations
Vector Vector::operator+(const Vector& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vector sizes must match for addition");
    }
    Vector result(size_);
    for (size_t i = 0; i < size_; ++i) {
        result[i] = data_[i] + other[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vector sizes must match for subtraction");
    }
    Vector result(size_);
    for (size_t i = 0; i < size_; ++i) {
        result[i] = data_[i] - other[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size_);
    for (size_t i = 0; i < size_; ++i) {
        result[i] = data_[i] * scalar;
    }
    return result;
}

double Vector::dot(const Vector& other) const {
    if (size_ != other.size_) {
        throw std::invalid_argument("Vector sizes must match for dot product");
    }
    double result = 0.0;
    for (size_t i = 0; i < size_; ++i) {
        result += data_[i] * other[i];
    }
    return result;
}

double Vector::norm() const {
    return std::sqrt(dot(*this));
}

// Data access
const std::vector<double>& Vector::data() const {
    return data_;
}

std::vector<double>& Vector::data() {
    return data_;
}

} // namespace MonkeySolve
