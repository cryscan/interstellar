//
// Created by lepet on 8/2/2018.
//

#include <GL/glut.h>

#include <objects/object.h>
#include <objects/camera.h>


camera::camera(const glm::vec3 &eye,
               const glm::vec3 &center,
               const glm::vec3 &up) : eye(eye), center(center), up(up), mouse_down(0) {
    rot = glm::vec2();
    diff = glm::vec2();
}

void camera::update() {
    object::update();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2]);
    glTranslatef(center[0], center[1], center[2]);
    glRotatef(rot[1], 1.0f, 0, 0);
    glRotatef(rot[0], 0, 1.0f, 0);
    glTranslatef(-center[0], -center[1], -center[2]);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat *>(&transform));
}

void camera::mouse(int button, int state, glm::vec<2, int> &pos) {
    object::mouse(button, state, pos);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouse_down = 1;
        diff = pos - rot;
    } else
        mouse_down = 0;
}

void camera::motion(glm::vec<2, int> &pos) {
    object::motion(pos);
    if (mouse_down)
        rot = pos - diff;
}
