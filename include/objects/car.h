//
// Created by lepet on 8/4/2018.
//

#ifndef P3_CAR_H
#define P3_CAR_H

#include <vector>
#include <glm/glm.h>
#include <utils/spline.h>
#include <objects/object.h>
#include <objects/outline.h>


class car : public object {
private:
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> tangents;
    spline *route = nullptr;

    float u;
    glm::vec3 offset;
    glm::vec3 target;

public:
    explicit car(const std::vector<glm::vec3> &points);
    void update() override;
};


#endif //P3_CAR_H
