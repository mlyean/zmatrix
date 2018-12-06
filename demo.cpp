#include <iostream>
#include "src/zmatrix.hpp"

// The matrices ZMatrix and IMatrix are declared in the namespace "matrix"
// IMatrix is a specialization of ZMatrix
using namespace matrix;

int main() {
    // Declare matrix using initializer list
    // Matrices can be declared const
    const IMatrix<3, 3> mat {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    // Declare column vector using initializer list
    IVectorC<3> vec {
        1,
        2,
        3
    };

    // Declare row vector using initializer list
    IVectorR<3> rvec {
        1, 2, 3
    };

    std::cout << "Size of mat: " << mat.size() << std::endl;
    std::cout << "Dimensions of mat: " << mat.dim().first << 'x' << mat.dim().second << std::endl;

    // Get entry using ZMatrix::at(size_t, size_t)
    // Can also use mat[1][2] for non-const matrices
    std::cout << "mat[1][2]=" << mat.at(1, 2) << std::endl;

    // Printing matrices / putting them to std::ostream
    std::cout << "mat=\n" << mat << std::endl;
    std::cout << "vec=\n" << vec << std::endl;
    std::cout << "rvec=\n" << rvec << std::endl;

    // Matrix negation
    std::cout << "-mat=\n" << -mat << std::endl;

    // Scalar multiplication
    std::cout << "2*mat=\n" << 2 * mat << std::endl;

    // Matrix multiplication
    std::cout << "mat*mat=\n" << mat * mat << std::endl;
    std::cout << "mat*vec=\n" << mat * vec << std::endl;
    std::cout << "vec*rvec=\n" << vec * rvec << std::endl;
    std::cout << "rvec*vec=\n" << rvec * vec << std::endl;

    // Other types can be used, such as double
    ZMatrix<double, 2, 2> doubles {1.1, -0.7, 0.4, 1.2};
    std::cout << doubles << std::endl;

    // Check equality
    std::cout << (mat == vec * rvec) << std::endl;

    return 0;
}
