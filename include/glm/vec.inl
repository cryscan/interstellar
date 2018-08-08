//
// Created by lepet on 7/27/2018.
//

#ifndef P3_VEC_INL
#define P3_VEC_INL

namespace glm {
    template<length_type L, typename T> class vec {
    public:
        typedef vec<L, T> type;

    private:
        std::array<T, L> data;

    public:
        // Default constructor.
        constexpr vec();
        // Copy constructor.
        constexpr vec(const vec<L, T> &u);
        template<typename U> constexpr vec(const vec<L, U> &u);
        template<length_type M> constexpr vec(const vec<M, T> &u);
        // List initializer.
        constexpr vec(std::initializer_list<T> list);
        // Initialize with an array.
        constexpr vec(std::array<T, L> &array);

        constexpr T *to_array() const;

        // Return number of elements.
        constexpr static length_type size() { return L; }

        // Accessing operators.
        T &operator [](length_type i);
        T const &operator [](length_type i) const;

        constexpr typename std::array<T, L>::const_iterator begin() const { return data.cbegin(); }

        constexpr typename std::array<T, L>::const_iterator end() const { return data.cend(); }

        // Unary operators.
        template<typename U> vec &operator +=(U scalar);
        template<typename U> vec &operator +=(vec<L, U> &u);
        template<typename U> vec &operator -=(U scalar);
        template<typename U> vec &operator -=(vec<L, U> &u);
        template<typename U> vec &operator *=(U scalar);
        template<typename U> vec &operator *=(vec<L, U> &u);
        template<typename U> vec &operator /=(U scalar);
        template<typename U> vec &operator /=(vec<L, U> &u);

        // utils
        constexpr T magnitude();
        constexpr void normalize();
    };

    template<length_type L, typename T>
    constexpr vec<L, T>::vec() : data() {
    }

    template<length_type L, typename T>
    constexpr vec<L, T>::vec(const vec<L, T> &u) : data(u.data) {
    }

    template<length_type L, typename T>
    template<typename U>
    constexpr vec<L, T>::vec(const vec<L, U> &u) : data() {
        for (int i = 0; i < L; ++i)
            data[i] = static_cast<T>(u[i]);
    }

    template<length_type L, typename T>
    template<length_type M>
    constexpr vec<L, T>::vec(const vec<M, T> &u) : data() {
        static_assert(M < L);
        std::copy(u.begin(), u.end(), data.begin());
    }

    template<length_type L, typename T>
    constexpr vec<L, T>::vec(std::initializer_list<T> list) : data() {
        assert(list.size() <= L);
        std::copy(list.begin(), list.end(), data.begin());
    }

    template<length_type L, typename T>
    constexpr vec<L, T>::vec(std::array<T, L> &array) : data(array) {
    }

    template<length_type L, typename T>
    constexpr T *vec<L, T>::to_array() const {
        return reinterpret_cast<T *>(static_cast<type *>(this));
    }

    template<length_type L, typename T>
    T &vec<L, T>::operator [](length_type i) {
        assert(i < L);
        return data[i];
    }

    // Accessing operator.
    template<length_type L, typename T>
    T const &vec<L, T>::operator [](length_type i) const {
        assert(i < L);
        return data[i];
    }

    // Unary operators.
    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator +=(U scalar) {
        for (int i = 0; i < L; ++i)
            data[i] += static_cast<T>(scalar);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator +=(vec<L, U> &u) {
        for (int i = 0; i < L; ++i)
            data[i] += static_cast<T>(u[i]);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator -=(U scalar) {
        for (int i = 0; i < L; ++i)
            data[i] -= static_cast<T>(scalar);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator -=(vec<L, U> &u) {
        for (int i = 0; i < L; ++i)
            data[i] -= static_cast<T>(u[i]);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator *=(U scalar) {
        for (int i = 0; i < L; ++i)
            data[i] *= static_cast<T>(scalar);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator *=(vec<L, U> &u) {
        for (int i = 0; i < L; ++i)
            data[i] *= static_cast<T>(u[i]);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator /=(U scalar) {
        for (int i = 0; i < L; ++i)
            data[i] /= static_cast<T>(scalar);
        return *this;
    }

    template<length_type L, typename T>
    template<typename U>
    vec<L, T> &vec<L, T>::operator /=(vec<L, U> &u) {
        for (int i = 0; i < L; ++i)
            data[i] /= static_cast<T>(u[i]);
        return *this;
    }

    template<length_type L, typename T>
    vec<L, T> operator +(const vec<L, T> &u) {
        return vec<L, T>(u);
    }

    template<length_type L, typename T>
    vec<L, T> operator -(const vec<L, T> &u) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = -u[i];
        return ret;
    }

    // Binary operators.
    template<length_type L, typename T, typename U>
    vec<L, T> operator +(const vec<L, T> &u, U scalar) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] + static_cast<T>(scalar);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator +(const vec<L, T> &u, const vec<L, U> &v) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] + static_cast<T>(v[i]);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator -(const vec<L, T> &u, U scalar) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] - static_cast<T>(scalar);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator -(const vec<L, T> &u, const vec<L, U> &v) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] - static_cast<T>(v[i]);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator *(const vec<L, T> &u, U scalar) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] * static_cast<T>(scalar);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator *(const vec<L, T> &u, const vec<L, U> &v) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] * static_cast<T>(v[i]);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator /(const vec<L, T> &u, U scalar) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] / static_cast<T>(scalar);
        return ret;
    }

    template<length_type L, typename T, typename U>
    vec<L, T> operator /(const vec<L, T> &u, const vec<L, U> &v) {
        vec<L, T> ret;
        for (int i = 0; i < L; ++i)
            ret[i] = u[i] / static_cast<T>(v[i]);
        return ret;
    }

    template<length_type L, typename T>
    constexpr T vec<L, T>::magnitude() {
        double ret = 0;
        for (int i = 0; i < L; ++i)
            ret += static_cast<double>(data[i]) * static_cast<double>(data[i]);
        ret = sqrt(ret);
        return static_cast<T>(ret);
    }

    template<length_type L, typename T>
    constexpr void vec<L, T>::normalize() {
        T len = magnitude();
        for (int i = 0; i < L; ++i)
            data[i] /= len;
    }
}

namespace glm {
    template<length_type L, typename T, typename U>
    T dot(const vec<L, T> &u, const vec<L, U> &v) {
        T ret = 0;
        for (int i = 0; i < L; ++i)
            ret += u[i] * static_cast<T>(v[i]);
        return ret;
    }

    template<typename T, typename U>
    vec<3, T> cross(const vec<3, T> &u, const vec<3, U> &v) {
        vec<3, T> ret;
        ret[0] = u[1] * static_cast<T>(v[2]) - u[2] * static_cast<T>(v[1]);
        ret[1] = -u[0] * static_cast<T>(v[2]) + u[2] * static_cast<T>(v[0]);
        ret[2] = u[0] * static_cast<T>(v[1]) - u[1] * static_cast<T>(v[0]);
        return ret;
    }
}

#endif //P3_TYPE_VEC_INL
