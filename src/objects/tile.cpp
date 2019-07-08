//
// Created by lepet on 8/4/2018.
//

#include <GL/glut.h>
#include <system/engine.h>
#include <objects/tile.h>


tile::tile(node_type type,
           node_orientation orientation,
           const glm::vec3& offset) : offset(offset),
                                      orientation(orientation) {
    auto& engine = engine::get_instance();
    switch (type) {
        case NODE_PATH:
            mesh = engine.get_model("tiles.path");
            break;
        case NODE_BLOCK:
            mesh = engine.get_model("tiles.block");
            break;
        default:
            mesh = engine.get_model("tiles.park");
            break;
    }
}

void tile::update() {
    object::update();
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glLoadIdentity();
    glTranslatef(offset[0], offset[1], offset[2]);
    // Rotate the tile according to target.
    GLfloat angle = 90.0f * orientation;
    glRotatef(angle, 0, 1.0f, 0);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(&transform));
}
