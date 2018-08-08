//
// Created by lepet on 7/28/2018.
//

#ifndef P3_MAT_INL
#define P3_MAT_INL

namespace glm {
    template<length_type C, length_type R, typename T> class mat {
    public:
        typedef glm::vec<R, T> col_type;
        typedef glm::vec<C, T> row_type;
        typedef glm::mat<C, R, T> type;
        typedef glm::mat<R, C, T> transpose_type;

    private:
        constexpr static length_type S = C * R;
        std::array<glm::vec<R, T>, C> data;

    public:
        // Default constructor.
        constexpr mat();
        // Copy constructor.
        constexpr mat(const mat<C, R, T> &m);
        // List initializer.
        constexpr mat(std::initializer_list<col_type> list);
        // Initialize from an array.
        constexpr mat(std::array<T, S> &array);
        // Initialize from a scalar
        constexpr mat(T scalar);

        constexpr T *to_array() const;

        // Return the number of elements.
        constexpr static length_type size() { return S; }

        // Return the number of rows or columns.
        constexpr length_type size(int i);

        // Access operators.
        col_type &operator [](length_type i);
        col_type const &operator [](length_type i) const;

        // Matrix manipulation.
        transpose_type transpose() const;
    };

    template<length_type C, length_type R, typename T>
    constexpr mat<C, R, T>::mat() : data() {
    }

    template<length_type C, length_type R, typename T>
    constexpr mat<C, R, T>::mat(const mat<C, R, T> &m) : data(m.data) {
    }

    template<length_type C, length_type R, typename T>
    constexpr mat<C, R, T>::mat(std::initializer_list<col_type> list) : data() {
        assert(list.size() == C);
        std::copy(list.begin(), list.end(), data.begin());
    }

    template<length_type C, length_type R, typename T>
    constexpr mat<C, R, T>::mat(std::array<T, mat<C, R, T>::S> &array) : data() {
        std::copy(array.cbegin(), array.cend(), data);
    }

    template<length_type C, length_type R, typename T>
    constexpr mat<C, R, T>::mat(T scalar) : data() {
        static_assert(C >= R);
        for (int i = 0; i < R; ++i)
            data[i][i] = scalar;
    }

    template<length_type C, length_type R, typename T>
    constexpr T *mat<C, R, T>::to_array() const {
        return reinterpret_cast<T *>(const_cast<type *>(this));
    }

    template<length_type C, length_type R, typename T>
    constexpr length_type mat<C, R, T>::size(int i) {
        if (i == 0)
            return C;
        if (i == 1)
            return R;
        return 0;
    }

    template<length_type C, length_type R, typename T>
    typename mat<C, R, T>::col_type &mat<C, R, T>::operator [](length_type i) {
        assert(i < C);
        return data[i];
    }

    template<length_type C, length_type R, typename T>
    const typename mat<C, R, T>::col_type &mat<C, R, T>::operator [](length_type i) const {
        assert(i < C);
        return data[i];
    }

    template<length_type C, length_type R, typename T>
    typename mat<C, R, T>::transpose_type mat<C, R, T>::transpose() const {
        mat<R, C, T> ret;
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                ret[j][i] = data[i][j];
        return ret;
    }

    // Unary operators.
    template<length_type C, length_type R, typename T>
    mat<C, R, T> operator +(const mat<C, R, T> &m) {
        return mat<C, R, T>(m);
    }

    template<length_type C, length_type R, typename T>
    mat<C, R, T> operator -(const mat<C, R, T> &m) {
        mat<C, R, T> ret;
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                ret[i][j] = -m[i][j];
        return ret;
    }

    // Binary operators.
    template<length_type C, length_type R, typename T, typename U>
    mat<C, R, T> operator +(const mat<C, R, T> &mat1, const mat<C, R, T> &mat2) {
        mat<C, R, T> ret;
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                ret[i][j] = mat1[i][j] + static_cast<T>(mat2[i][j]);
        return ret;
    }

    template<length_type C, length_type R, typename T, typename U>
    mat<C, R, T> operator -(const mat<C, R, T> &mat1, const mat<C, R, T> &mat2) {
        mat<C, R, T> ret;
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                ret[i][j] = mat1[i][j] - static_cast<T>(mat2[i][j]);
        return ret;
    }

    template<length_type C, length_type R, typename T, typename U>
    mat<C, R, T> operator *(const mat<C, R, T> &m, U scalar) {
        mat<C, R, T> ret;
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                ret[i][j] = m[i][j] * static_cast<T>(scalar);
        return ret;
    }

    template<length_type C, length_type R, typename T, typename U>
    mat<C, R, T> operator /(const mat<C, R, T> &m, U scalar) {
        mat<C, R, T> ret;
        for (int i = 0; i < C; ++i)
            for (int j = 0; j < R; ++j)
                ret[i][j] = m[i][j] / static_cast<T>(scalar);
        return ret;
    }

    // Matrix manipulations.
    template<length_type C, length_type R, typename T, typename U>
    vec <R, T> operator *(const mat<C, R, T> &m, const vec <C, U> &u) {
        vec<R, T> ret;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                ret[i] += m[j][i] * static_cast<T>(u[j]);
        return ret;
    }

    template<length_type C, length_type R, length_type P, typename T, typename U>
    mat<P, R, T> operator *(const mat<C, R, T> &mat1, const mat<P, C, U> &mat2) {
        mat<P, R, T> ret;
        for (int i = 0; i < P; ++i)
            for (int j = 0; j < R; ++j)
                for (int k = 0; k < C; ++k)
                    ret[i][j] += mat1[k][j] * static_cast<T>(mat2[i][k]);
        return ret;
    }
}

namespace glm {
    template<length_type C, typename T>
    mat<C, C, T> diagonal(T scalar) {
        mat<C, C, T> ret;
        for (int i = 0; i < C; ++i)
            ret[i][i] = scalar;
        return ret;
    }

    template<length_type C, typename T>
    mat<C, C, T> diagonal(vec <C, T> &u) {
        mat<C, C, T> ret;
        for (int i = 0; i < C; ++i)
            ret[i][i] = u[i];
        return ret;
    }

    // Forward pass of Gauss-Jordan elimination.
    template<length_type C, length_type R, typename T>
    mat<R, C, T> forward(mat<C, R, T> &m) {
        static_assert(C >= R);
        mat<R, C, T> ret = m.transpose();
        for (int i = 0; i < R; ++i) {
            for (int j = R - 1; j > i; --j)
                ret[j] = ret[j] - ret[i] / ret[i][i] * ret[j][i];   // Eliminate the first columns.
            ret[i] /= ret[i][i];    // Normalize rows.
        }
        return ret;
    }

    template<length_type C, length_type R, typename T>
    T determinant(mat<C, R, T> &m) {
        mat<R, C, T> ret = forward(m);
        T det = 1;
        for (int i = 0; i < R; ++i)
            det *= ret[i][i];
        return det;
    }

    // Full process of Gauss-Jordan elimination.
    template<length_type C, length_type R, typename T>
    mat<C, R, T> solve(mat<C, R, T> &m) {
        mat<R, C, T> ret = forward(m);
        for (int i = R - 1; i > 0; --i)
            for (int j = 0; j < i; ++j)
                ret[j] = ret[j] - ret[i] * ret[j][i];
        return ret.transpose();
    }
}

#endif //P3_MAT_INL