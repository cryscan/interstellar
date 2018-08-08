//
// Created by lepet on 7/30/2018.
//

#ifndef P3_FIGURES_H
#define P3_FIGURES_H

#include <vector>
#include <GL/glut.h>
#include <glm/glm.h>
#include <models/model.h>


class figure : public model {
public:
    figure();
    void render() override;

protected:
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;
};

class rectangle : public figure {
public:
    rectangle();
    explicit rectangle(const glm::vec2 &point);

private:
    glm::vec2 point;
    void init_model();
};


#endif //P3_FIGURES_H
