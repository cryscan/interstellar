//
// Created by hsy on 2018/8/6.
//

#ifndef P3_SPACESHIFT_H
#define P3_SPACESHIFT_H

#include <objects/object.h>
#include <objects/outline.h>

class spaceship : public outline {
public:
    explicit spaceship(const glm::vec3 &offset, GLfloat angle);
    spaceship(const spaceship &obj) = default;

    void update() override;

private:
    glm::vec3 offset;
    GLfloat angle;
    GLfloat ratio;
};

#endif //P3_SPACESHIFT_H
