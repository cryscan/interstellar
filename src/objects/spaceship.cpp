//
// Created by hsy on 2018/8/6.
//

#include <system/engine.h>
#include <objects/spaceship.h>

spaceship::spaceship(const glm::vec3 &offset, GLfloat angle) : offset(offset),
                                                               angle(angle),
                                                               ratio(1.0) {
    auto &engine = engine::get_instance();
    mesh = engine.get_model("rocket");
}

void spaceship::update() {
    object::update();
    ratio = 0.8 + 0.2 * cosf(angle / 180);
    angle += 4.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offset[0], offset[1] + 0.2f, offset[2]);
    glRotatef(angle, 0, 1.0f, 0);
    glRotatef(angle, 1.0f, 0, 0);
    glRotatef(angle, 0, 0, 1.0f);
    glScalef(0.1f, 0.1f, 0.1f);
    glScalef(ratio, ratio, ratio);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat *>(&transform));
}
