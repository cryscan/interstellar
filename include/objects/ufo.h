//
// Created by lepet on 8/1/2018.
//

#ifndef P3_UFO_H
#define P3_UFO_H

#include <glm/glm.h>
#include <objects/object.h>


class ufo : public object {
private:
    glm::vec3 offset;
    GLfloat pitch;
    GLfloat precession_angle;
    GLfloat precession_velocity;

public:
    explicit ufo(const glm::vec3 &offset, GLfloat precession_angle, GLfloat spin_angle);
    void update() override;
};

#endif //P3_UFO_H
