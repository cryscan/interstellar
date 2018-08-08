//
// Created by lepet on 7/31/2018.
//

#include <GL/glut.h>
#include <objects/object.h>


object::object() : mesh(nullptr), transform(1.0), children() {
}

object::object(model *mesh) : mesh(mesh), transform(1.0), children() {
}


object::~object() {
    // Delete children if the parent is destroyed.
}


void object::update() {
    for (auto child : children)
        child->update();
}

void object::mouse(int button, int state, glm::vec<2, int> &pos) {
    for (auto child : children)
        child->mouse(button, state, pos);
}

void object::motion(glm::vec<2, int> &pos) {
    for (auto child : children)
        child->motion(pos);
}


void object::render(int pass) {
    if (pass == 0) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(reinterpret_cast<const GLfloat *>(&transform));

        // Render the mesh if the object has a mesh.
        if (mesh != nullptr)
            mesh->render();
        // Render each child based on parent's transformation.
        for (auto child : children)
            child->render(0);

        glPopMatrix();
    } else {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(reinterpret_cast<const GLfloat *>(&transform));

        // Render each child based on parent's transformation.
        for (auto child : children)
            child->render(pass);

        glPopMatrix();
    }
}

void object::add_child(object *child) {
    children.push_back(child);
}