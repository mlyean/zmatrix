#include <algorithm>
#include <cassert>
#include <iostream>
#include <functional>

namespace matrix {

    /*
     * Implementation of integer matrices - useful(?) for representing linear transformations involving only integers.
     * Integer matrices are not closed under multiplicative inverse, hence this operation is not supported.
     */
    template<typename T, size_t M, size_t N>
    class ZMatrix {
    private:
        T* mat;
        const size_t sz;

    public:
        template<typename U, size_t M2, size_t N2>
        friend class ZMatrix;

        ZMatrix(T* mat) : mat(mat), sz(M * N) {};

        ZMatrix() : mat(new T[M * N]), sz(M * N) {
            for (size_t i = 0; i < M; i++) {
                for (size_t j = 0; j < N; j++) {
                    (*this)[i][j] = 0;
                }
            }
        }

        ZMatrix(std::initializer_list<T> lst) : mat(new T[M * N]), sz(M * N) {
            assert(lst.size() == sz);
            std::copy(lst.begin(), lst.end(), mat);
        }

        ZMatrix(const ZMatrix<T, M, N>& a) : mat(new T[a.sz]), sz(a.sz) {
            std::copy_n(a.mat, sz, mat);
        }

        ZMatrix(ZMatrix<T, M, N>&& a) : mat(a.mat), sz(a.sz) {
            a.mat = nullptr;
        }

        ZMatrix<T, M, N>& operator=(const ZMatrix<T, M, N>& a) {
            std::copy_n(a.mat, a.sz, mat);
        }

        ZMatrix<T, M, N>& operator=(ZMatrix<T, M, N>&& a) {
            mat = a.mat;
            a.mat = nullptr;
        }

        ~ZMatrix() {
            delete[] mat;
        }

        T* operator[](size_t i) {
            return &mat[i * N];
        }

        T at(size_t i, size_t j) const {
            assert(i < M);
            assert(j < N);
            return mat[i * N + j];
        }

        size_t size() {
            return sz;
        }

        std::pair<size_t, size_t> dim() {
            return {M, N};
        }

        ZMatrix<T, M, N> operator+(const ZMatrix<T, M, N>& a) const {
            T* sum = new T[sz];
            std::transform(mat, mat + sz, a.mat, sum, std::plus<T>());
            return sum;
        }

        ZMatrix<T, M, N> operator-(const ZMatrix<T, M, N>& a) const {
            T* diff = new T[sz];
            std::transform(mat, mat + sz, a.mat, diff, std::minus<T>());
            return diff;
        }

        ZMatrix<T, M, N> operator-() const {
            T* neg = new T[sz];
            std::transform(mat, mat + sz, neg, std::negate<T>());
            return neg;
        }

        ZMatrix<T, M, N> operator*(T n) const {
            T* prod = new T[sz];
            std::transform(mat, mat + sz, prod, [n](T k) -> T { return n * k; });
            return prod;
        }

        template<size_t P>
        ZMatrix<T, M, P> operator*(const ZMatrix<T, N, P>& a) const {
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
    };

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