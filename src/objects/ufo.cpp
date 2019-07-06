//
// Created by lepet on 8/1/2018.
//

#include <GL/glut.h>
#include <objects/ufo.h>
#include <system/engine.h>


class ufo_body : public object {
private:
    GLfloat spin_angle;
    GLfloat spin_velocity;

public:
    explicit ufo_body(GLfloat spin_angle);
    void update() override;
};

class ufo_cockpit : public object {
public:
    ufo_cockpit();
};

ufo_body::ufo_body(GLfloat spin_angle) : spin_angle(spin_angle), spin_velocity(12.0) {
    auto& engine = engine::get_instance();
    mesh = engine.get_model("ufo.body");
}

void ufo_body::update() {
    object::update();
    spin_angle += spin_velocity;
    while (spin_angle > 360)
        spin_angle -= 360;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(spin_angle, 0.0, 1.0, 0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(&transform));
}

ufo_cockpit::ufo_cockpit() {
    auto& engine = engine::get_instance();
    mesh = engine.get_model("ufo.cockpit");
}

ufo::ufo(const glm::vec3& offset,
         GLfloat precession_angle,
         GLfloat spin_angle) : offset(offset),
                               pitch(4.0f),
                               precession_angle(precession_angle),
                               precession_velocity(-2.0f) {
    add_child(std::make_unique<ufo_body>(spin_angle));
    add_child(std::make_unique<ufo_cockpit>());
}

void ufo::update() {
    object::update();
    precession_angle += precession_velocity;
    while (precession_angle < -360)
        precession_angle += 360;

    // Calculate precession of the ufo.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offset[0], offset[1], offset[2]);
    glScalef(0.1, 0.1, 0.1);
    // First, rotate the axis around the y axis.
    glRotatef(precession_angle, 0.0, 1.0, 0.0);
    // Next, rotate the axis to an angle of pitch.
    glRotatef(pitch, 1.0, 0.0, 0.0);
    // Finally, save the matrix to variable.
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(&transform));
}
