//
// Created by lepet on 8/2/2018.
//

#ifndef P3_CAMERA_H
#define P3_CAMERA_H

#include <glm/glm.h>


class camera : public object {
private:
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    glm::vec2 rot;
    glm::vec2 diff;

    int mouse_down;

public:
    camera(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up);
    void update();
    void mouse(int button, int state, glm::vec<2, int> &pos);
    void motion(glm::vec<2, int> &pos);
};


#endif //P3_CAMERA_H
