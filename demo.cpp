#include <iostream>
#include "matrix.hpp"

using namespace matrix;

int main() {
    // Declare matrix using initializer list
    const IMatrix<3, 3> mat {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    // Declaring column vector using initializer list
    IVectorC<3> vec {
        1,
        2,
        3
    };

    // Declaring row vector using initializer list
    IVectorR<3> rvec {
        1, 2, 3
    };

    // Get entry
    std::cout << "mat[1][2]=" << mat.at(1, 2) << std::endl;

    // Printing matrices
    std::cout << "mat=\n" << mat << std::endl;
    std::cout << "vec=\n" << vec << std::endl;
    std::cout << "rvec=\n" << rvec << std::endl;

    // Negating a matrix
    std::cout << "-mat=\n" << -mat << std::endl;

    // Scalar multiplication
    std::cout << "2*mat=\n" << 2 * mat << std::endl;

    // Matrix multiplication
    std::cout << "mat*mat=\n" << mat * mat << std::endl;
    std::cout << "mat*vec=\n" << mat * vec << std::endl;
    std::cout << "vec*rvec=\n" << vec * rvec << std::endl;
    std::cout << "rvec*vec=\n" << rvec * vec << std::endl;

    return 0;
}
