#ifndef MONKEYSOLVE_DENSESOLVER_HPP
#define MONKEYSOLVE_DENSESOLVER_HPP

#include "DenseMatrix.hpp"
#include "Vector.hpp"
#include <vector>

namespace MonkeySolve {

class DenseSolver {
public:
    // Solve Ax = b using LU decomposition with partial pivoting
    static Vector solve(const DenseMatrix& A, const Vector& b);
    
private:
    // LU decomposition with partial pivoting
    static void luDecomposition(DenseMatrix& A, std::vector<size_t>& perm);
    
    // Forward substitution: Ly = Pb
    static Vector forwardSubstitution(const DenseMatrix& L, const Vector& b, 
                                      const std::vector<size_t>& perm);
    
    // Backward substitution: Ux = y
    static Vector backwardSubstitution(const DenseMatrix& U, const Vector& y);
};

} // namespace MonkeySolve

#endif // MONKEYSOLVE_DENSESOLVER_HPP
