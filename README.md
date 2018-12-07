# zmatrix
Integer matrix manipulation in C++

## Features
ZMatrix supports basic matrix operations:
* Addition (`+`)
* Subtraction (`-`)
* Unary negation (`-`)
* Scalar multiplication (`*`)
* Matrix multiplication (`*`)

Note that inverses are not supported, since integer matrices are not closed under that operation.

Other features:
* Initialization using fill constructors and `std::initializer_list`s
* Access specific entry (`mat[i][j]` / `mat.at(i, j)`)
* `<<` overloading for putting to `std::ostream`

## Examples
`demo.cpp` provides some example use cases. To compile it, simply run `g++ demo.cpp`.

## TODO
* Implement a more efficient matrix multiplication algorithm
* `det()` function to calculate determinant
* `t()` function to get transpose
