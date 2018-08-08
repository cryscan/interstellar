//
// Created by lepet on 7/26/2018.
//

#ifndef P3_GLM_H
#define P3_GLM_H

#include <cassert>
#include <initializer_list>
#include <array>
#include <cmath>

namespace glm {
    typedef int length_type;

    template<length_type L, typename T> class vec;

    template<length_type C, length_type R, typename T> class mat;
}

#include "vec.inl"
#include "mat.inl"

namespace glm {
    typedef vec<2, float> vec2;
    typedef vec<3, float> vec3;
    typedef vec<4, float> vec4;

    typedef mat<1, 2, float> mat2x1;
    typedef mat<2, 1, float> mat1x2;
    typedef mat<2, 2, float> mat2;

    typedef mat<1, 3, float> mat3x1;
    typedef mat<3, 1, float> mat1x3;
    typedef mat<2, 3, float> mat3x2;
    typedef mat<3, 2, float> mat2x3;
    typedef mat<3, 3, float> mat3;

    typedef mat<1, 4, float> mat4x1;
    typedef mat<4, 1, float> mat1x4;
    typedef mat<2, 4, float> mat4x2;
    typedef mat<4, 2, float> mat2x4;
    typedef mat<3, 4, float> mat4x3;
    typedef mat<4, 3, float> mat3x4;
    typedef mat<4, 4, float> mat4;
}

#endif //P3_GLM_H