//
// Created by hsy on 2018/8/5.
//
#ifndef OPENGL_ROCKET_H
#define OPENGL_ROCKET_H

#include <iostream>
#include <vector>
#include <glm/glm.h>
#include <models/model.h>

class rocket : public model {
public:
    explicit rocket();
    ~rocket();
    void render() override;

private:
    std::vector<glm::vec3> surface;
    GLUquadric *obj;
};

#endif