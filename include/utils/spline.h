//
// Created by lepet on 8/4/2018.
//

#ifndef P3_SPLINE_H
#define P3_SPLINE_H

#include <vector>
#include <glm/glm.h>


class spline {
private:
    std::vector<glm::vec3> points;
    unsigned int size;
    constexpr static unsigned N = 10;

    glm::mat4 M;
    glm::mat4x3 MP;

    unsigned int last_segment;

public:
    spline(const std::vector<glm::vec3>& points,
           float tension);

    glm::mat3x2 get(unsigned int n, float u);
};


#endif //P3_SPLINE_H
