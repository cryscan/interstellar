//
// Created by lepet on 8/4/2018.
//

#include <utils/spline.h>

using namespace std;

spline::spline(const vector<glm::vec3>& points, float tension) : points(points) {
    size = points.size();
    last_segment = size;

    float s = (1 - tension) / 2;
    M = {{-s,    2 * s,     -s, 0},
         {2 - s, s - 3,     0,  1},
         {s - 2, 3 - 2 * s, s,  0},
         {s,     -s,        0,  0}};
    MP = glm::mat4x3();

    this->points.insert(this->points.begin(), points[0]);
    this->points.push_back(points[size - 1]);
    size = this->points.size();
}

glm::mat3x2 spline::get(unsigned int n, float u) {
    assert(n > 0 && n + 2 < size);

    // For better performance...
    if (last_segment != n) {
        glm::vec3 p_0 = points[n - 1];
        glm::vec3 p_1 = points[n];
        glm::vec3 p_2 = points[n + 1];
        glm::vec3 p_3 = points[n + 2];

        glm::mat3x4 P_T = {p_0, p_1, p_2, p_3};
        glm::mat4x3 P = P_T.transpose();
        MP = M * P;
    }

    glm::mat2x4 U = {{u * u * u, 3 * u * u},
                     {u * u,     2 * u},
                     {u,         1},
                     {1,         0}};

    glm::mat3x2 UMP = (U * MP).transpose();
    return UMP;
}
