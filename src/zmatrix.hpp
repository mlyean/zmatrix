/*
 * zmatrix.hpp
 * Purpose : Implement integer matrices with basic operations
 *
 * @author Lim Ming Yean (mlyean)
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>

// Declarations
namespace zmatrix {
    template<typename T, size_t M, size_t N>
    class ZMatrix {
    private:
        T* mat;
        static constexpr size_t sz = M * N;

    public:
        /*
         * Default constructor. Initializes all entries to 0.
         */
        ZMatrix();

        /*
         * Fill constructor. Fills all entries with the parameter.
         * @param n : The value to fill with
         */
        explicit ZMatrix(T n);

        /*
         * Construct matrix from T array pointer.
         * Does not check size.
         * @param mat : Pointer to T array
         */
        ZMatrix(T* mat);

        /*
         * Initializer list constructor.
         * The initializer list must have exactly M*N elements.
         * @param lst : Initializer list to use
         */
        ZMatrix(std::initializer_list<T> lst);

        /*
         * Construct matrix using lambda providing values at each position
         * @param func : Lambda with parameters i and j, returning the value at position (i, j)
         */
        explicit ZMatrix(std::function<T(size_t, size_t)> func);

        /*
         * Copy constructor.
         * @param a : ZMatrix to copy
         */
        ZMatrix(const ZMatrix<T, M, N>& a);

        /*
         * Move constructor
         * @param a : ZMatrix to move
         */
        ZMatrix(ZMatrix<T, M, N>&& a);

        /*
         * Copy assignment.
         * @param a : ZMatrix to copy
         */
        ZMatrix<T, M, N>& operator=(const ZMatrix<T, M, N>& a);

        /*
         * Move assignment.
         * @param a : ZMatrix to move
         */
        ZMatrix<T, M, N>& operator=(ZMatrix<T, M, N>&& a);

        /*
         * Destructor
         */
        ~ZMatrix();

        /*
         * Return ith row.
         * @param i : Row to return
         */
        T* operator[](size_t i);

        /*
         * Return reference to entry at position (i, j).
         * @param i : Row number
         * @param j : Column number
         */
        T& at(size_t i, size_t j);

        /*
         * Return entry at position (i, j).
         * @param i : Row number
         * @param j : Column number
         */
        T at(size_t i, size_t j) const;

        /*
         * Return total number of elements of the matrix.
         */
        constexpr size_t size() const;

        /*
         * Return dimensions of the matrix.
         */
        constexpr std::pair<size_t, size_t> dim() const;

        /*
         * Return sum of this and a.
         * @param a : ZMatrix to compute sum with
         */
        ZMatrix<T, M, N> operator+(const ZMatrix<T, M, N>& a) const;

        /*
         * Return difference of this and a.
         * @param a : ZMatrix to compute difference with
         */
        ZMatrix<T, M, N> operator-(const ZMatrix<T, M, N>& a) const;

        /*
         * Return the negation of this.
         */
        ZMatrix<T, M, N> operator-() const;

        /*
         * Return the (right) scalar product with a constant.
         * @param n : Constant to multiply
         */
        ZMatrix<T, M, N> operator*(T n) const;

        /*
         * Return the product of left-multiplying another matrix a.
         * @param a : The matrix to left-multiply
         */
        template<size_t P>
        ZMatrix<T, M, P> operator*(const ZMatrix<T, N, P>& a) const;

        template<typename U, size_t P, size_t Q>
        friend class ZMatrix;

        template <typename U, size_t P, size_t Q>
        friend bool operator==(const ZMatrix<U, P, Q>&, const ZMatrix<U, P, Q>&);
    };

    /*
     * Return the (right) scalar product with a constant.
     * @param n : Constant to multiply
     * @param a : ZMatrix to multiply
     */
    template<typename T, size_t M, size_t N>
    ZMatrix<T, M, N> operator*(T n, const ZMatrix<T, M, N>& a);

    /*
     * Put the matrix to os.
     * @param os : ostream to put to
     * @param a : ZMatrix to put
     */
    template<typename T, size_t M, size_t N>
    std::ostream& operator<<(std::ostream& os, const ZMatrix<T, M, N> a);

    /*
     * Check for equality between matrices.
     * @param a : A ZMatrix
     * @param b : Another ZMatrix
     */
    template <typename T, size_t M, size_t N>
    bool operator==(const ZMatrix<T, M, N>& a, const ZMatrix<T, M, N>& b);

    /*
     * Check for inequality between matrices.
     * @param a : A ZMatrix
     * @param b : Another ZMatrix
     */
    template <typename T, size_t M, size_t N>
    bool operator!=(const ZMatrix<T, M, N>& a, const ZMatrix<T, M, N>& b);

    /*
     * Return n by n identity matrix
     */
    template <typename T, size_t N>
    ZMatrix<T, N, N> eye();

    /*
     * Raise base to a given power.
     * @param base : A ZMatrix
     * @param exponent : A positive integer
     */
    template <typename T, size_t N>
    ZMatrix<T, N, N> pow(const ZMatrix<T, N, N>& base, size_t exponent);

    // Aliases
    template<typename T, size_t N>
    using NVectorC = ZMatrix<T, N, 1>;

    template<typename T, size_t N>
    using NVectorR = ZMatrix<T, 1, N>;

    template<typename T, size_t N>
    using NSquareMatrix = ZMatrix<T, N, N>;

    template<size_t M, size_t N>
    using IMatrix = ZMatrix<int, M, N>;

    template<size_t N>
    using IVectorC = IMatrix<N, 1>;

    template<size_t N>
    using IVectorR = IMatrix<1, N>;

    template<size_t N>
    using ISquareMatrix = IMatrix<N, N>;
}

// Implementation
namespace zmatrix {
    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix() : ZMatrix(0) {}

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix(T n) : mat(new T[M * N]) {
        std::fill(mat, mat + sz, n);
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix(T* mat) : mat(mat) {};

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix(std::initializer_list<T> lst) : mat(new T[M * N]) {
        assert(lst.size() == sz);
        std::copy(lst.begin(), lst.end(), mat);
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix(std::function<T(size_t, size_t)> func) : mat(new T[M * N]) {
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                mat[i * N + j] = func(i, j);
            }
        }
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix(const ZMatrix<T, M, N>& a) : mat(new T[a.sz]) {
        std::copy_n(a.mat, sz, mat);
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::ZMatrix(ZMatrix<T, M, N>&& a) : mat(a.mat) {
        a.mat = nullptr;
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>& ZMatrix<T, M, N>::operator=(const ZMatrix<T, M, N>& a) {
        std::copy_n(a.mat, sz, mat);
        return *this;
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>& ZMatrix<T, M, N>::operator=(ZMatrix<T, M, N>&& a) {
        mat = a.mat;
        a.mat = nullptr;
        return *this;
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N>::~ZMatrix() {
        delete[] mat;
    }

    template <typename T, size_t M, size_t N>
    constexpr size_t ZMatrix<T, M, N>::size() const {
        return sz;
    }

    template <typename T, size_t M, size_t N>
    constexpr std::pair<size_t, size_t> ZMatrix<T, M, N>::dim() const {
        return {M, N};
    }

    template <typename T, size_t M, size_t N>
    T& ZMatrix<T, M, N>::at(size_t i, size_t j) {
        assert(i < M);
        assert(j < N);
        return mat[i * N + j];
    }

    template <typename T, size_t M, size_t N>
    T ZMatrix<T, M, N>::at(size_t i, size_t j) const {
        assert(i < M);
        assert(j < N);
        return mat[i * N + j];
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N> ZMatrix<T, M, N>::operator+(const ZMatrix<T, M, N>& a) const {
        T* sum = new T[sz];
        std::transform(mat, mat + sz, a.mat, sum, std::plus<T>());
        return sum;
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N> ZMatrix<T, M, N>::operator-(const ZMatrix<T, M, N>& a) const {
        T* diff = new T[sz];
        std::transform(mat, mat + sz, a.mat, diff, std::minus<T>());
        return diff;
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N> ZMatrix<T, M, N>::operator-() const {
        T* neg = new T[sz];
        std::transform(mat, mat + sz, neg, std::negate<T>());
        return neg;
    }

    template <typename T, size_t M, size_t N>
    ZMatrix<T, M, N> ZMatrix<T, M, N>::operator*(T n) const {
        T* prod = new T[sz];
        std::transform(mat, mat + sz, prod, [n](T k) -> T { return n * k; });
        return prod;
    }

    template <typename T, size_t M, size_t N>
    template <size_t P>
    ZMatrix<T, M, P> ZMatrix<T, M, N>::operator*(const ZMatrix<T, N, P>& a) const {
        T* prod = new T[M * P];
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < P; j++) {
                T elem = 0;

                for (size_t k = 0; k < N; k++) {
                    elem += mat[i* N + k] * a.mat[k * P + j];
                }

                prod[i * P + j] = elem;
            }
        }

        return prod;
    }

    template<typename T, size_t M, size_t N>
    ZMatrix<T, M, N> operator*(T n, const ZMatrix<T, M, N>& a) {
        return a * n;
    }

    template<typename T, size_t M, size_t N>
    std::ostream& operator<<(std::ostream& os, const ZMatrix<T, M, N> a) {
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                os << a.at(i, j);
                if (j != N - 1) os << ' ';
            }
            if (i != M - 1) os << '\n';
        }
        return os;
    }

    template <typename T, size_t M, size_t N>
    bool operator==(const ZMatrix<T, M, N>& a, const ZMatrix<T, M, N>& b) {
        return std::equal(a.mat, a.mat + a.sz, b.mat);
    }

    template <typename T, size_t M, size_t N>
    bool operator!=(const ZMatrix<T, M, N>& a, const ZMatrix<T, M, N>& b) {
        return !(a == b);
    }

    template <typename T, size_t N>
    ZMatrix<T, N, N> eye() {
        return ZMatrix<T, N, N>([](size_t i, size_t j) -> T { return i == j ? 1 : 0; });
    }

    template <typename T, size_t N>
    ZMatrix<T, N, N> pow(const ZMatrix<T, N, N>& base, size_t exponent) {
        ZMatrix<T, N, N> ret(eye<T, N>());
        ZMatrix<T, N, N> cur(base);

        for (; exponent > 0; exponent >>= 1) {
            if (exponent & 1) ret = ret * cur;
            cur = cur * cur;
        }
        return ret;
    }
}
