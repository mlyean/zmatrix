# zmatrix
Integer matrix manipulation in C++

## Features
ZMatrix can be initialized by:
* Fill constructors
    * Default constructor fills with zeros
* `std::initializer_list`
* Lambdas giving values of each entry

ZMatrix supports basic matrix operations:
* Addition (`+`)
* Subtraction (`-`)
* Unary negation (`-`)
* Scalar multiplication (`*`)
* Matrix multiplication (`*`)

Note that inverses are not supported, since integer matrices are not closed under that operation.

Other features:
* Access specific entry (`mat[i][j]` / `mat.at(i, j)`)
* `<<` overloading for putting to `std::ostream`
* Get identity of square matrix using `eye`
* Efficient repeated multiplication using overloaded `pow`

## Examples
`demo.cpp` provides some example use cases.
To compile it, simply run `g++ demo.cpp`.

## TODO
* Implement `+=`, `-=`, `*=`
* `t()` function to get transpose
* Implement a more efficient matrix multiplication algorithm
* `det()` function to calculate determinant

