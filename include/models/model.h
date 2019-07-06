//
// Created by lepet on 7/30/2018.
//

#ifndef P3_MODEL_H
#define P3_MODEL_H

#include <vector>
#include <GL/glut.h>
#include <glm/glm.h>


struct vertex {
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec2 tex_coord;
};

// For textures.
struct image {
    unsigned long size_x;
    unsigned long size_y;
    std::vector<glm::vec<3, char>> data;
};


class model {
public:
    model();
    virtual ~model() = default;

    void set_color(const glm::vec4 &color);
    void load_texture(const std::string &filename);
    virtual void render() = 0;

protected:
    GLuint texture_id;
    glm::vec4 color;

    image *load_bmp(const std::string &filename);
};

#endif //P3_MODEL_H
