#ifndef MONKEYSOLVE_VECTOR_HPP
#define MONKEYSOLVE_VECTOR_HPP

#include <vector>
#include <cstddef>

namespace MonkeySolve {

class Vector {
private:
    std::vector<double> data_;
    size_t size_;

public:
    // Constructors
    Vector();
    explicit Vector(size_t size, double init_value = 0.0);
    Vector(const std::vector<double>& values);
    
    // Access
    double& operator[](size_t i);
    const double& operator[](size_t i) const;
    double& at(size_t i);
    const double& at(size_t i) const;
    
    // Size
    size_t size() const;
    void resize(size_t new_size, double init_value = 0.0);
    
    // Operations
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;
    double dot(const Vector& other) const;
    double norm() const;
    
    // Data access
    const std::vector<double>& data() const;
    std::vector<double>& data();
};

} // namespace MonkeySolve

#endif // MONKEYSOLVE_VECTOR_HPP
