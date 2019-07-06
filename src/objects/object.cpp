//
// Created by lepet on 7/31/2018.
//

#include <GL/glut.h>
#include <objects/object.h>


object::object() : mesh{nullptr}, transform{1.0} {
}

object::object(model* mesh) : mesh{mesh}, transform{1.0} {
}


void object::update() {
    for (auto& child : children)
        child->update();
}

void object::mouse(const int button, const int state, const glm::vec<2, int>& pos) {
    for (auto& child : children)
        child->mouse(button, state, pos);
}

void object::motion(const glm::vec<2, int>& pos) {
    for (auto& child : children)
        child->motion(pos);
}


void object::render(const int pass) {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(reinterpret_cast<const GLfloat*>(&transform));

    // Render the mesh if the object has a mesh.
    if (mesh) mesh->render();
    // Render each child based on parent's transformation.
    for (auto& child : children)
        child->render(pass);

    glPopMatrix();
}

void object::add_child(std::unique_ptr<object>&& child) {
    children.push_back(std::move(child));
}