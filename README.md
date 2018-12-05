# zmatrix
Integer matrix manipulation in C++

# Features
ZMatrix supports basic matrix operations:
* Addition (`+`)
* Subtraction (`-`)
* Unary negation (`-`)
* Scalar multiplication (`*`)
* Matrix multiplication (`*`)

Other features:
* Initialization using `std::initializer_list`s
* Access specific entry (`mat[i][j]` / `mat.at(i, j)`)
* `<<` overloading for putting to `std::ostream`

# TODO
* Implement a more efficient matrix multiplication algorithm

To compile the example, simply run
```g++ demo.cpp```

