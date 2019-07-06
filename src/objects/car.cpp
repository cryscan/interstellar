//
// Created by lepet on 8/4/2018.
//

#include <iostream>
#include <system/engine.h>
#include <objects/car.h>


using namespace std;

class wheel : public object {
private:
    glm::vec3 offset;

public:
    explicit wheel(const glm::vec3& offset);

    void update() override;
};

wheel::wheel(const glm::vec3& offset) :
        object{engine::get_instance().get_model("car.wheel")},
        offset{offset} {}

void wheel::update() {
    object::update();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offset[0], offset[1], offset[2]);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(&transform));
}


car::car(const vector<glm::vec3>& points) :
        object{engine::get_instance().get_model("car.body")},
        points{points},
        route{points, 0.2},
        u{1.0f} {
    // The first wheel.
    add_child(std::make_unique<wheel>(glm::vec3{-2.0f, 0, 1.1f}));
    // The second wheel.
    add_child(std::make_unique<wheel>(glm::vec3{-2.0f, 0, -1.1f}));
    // The third wheel.
    add_child(std::make_unique<wheel>(glm::vec3{0.0f, 0, 1.1f}));
    // The fourth wheel.
    add_child(std::make_unique<wheel>(glm::vec3{0.0f, 0, -1.1f}));
}

void car::update() {
    object::update();

    auto n = static_cast<unsigned int>(u);
    if (n < points.size()) {
        auto point = route.get(n, u - n);
        offset = point[0];
        target = point[1];
    }
    u = u + 0.01f;

    // Look-at transform.
    // reference: https://stackoverflow.com/questions/6992541/opengl-rotation-in-given-direction
    target.normalize();
    glm::vec3 T = target;
    glm::vec3 U = {0, 1.0f, 0};
    glm::vec3 L = glm::cross(U, T);
    glm::mat4 look(1.0);
    look[0] = T;
    look[1] = U;
    look[2] = L;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offset[0], offset[1], offset[2]);
    if (n < points.size() - 2)
        glRotatef(180, 0, 1.0f, 0);
    glMultMatrixf(reinterpret_cast<const GLfloat*>(&look));
    glScalef(0.15f, 0.15f, 0.15f);
    glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<GLfloat*>(&transform));
}
