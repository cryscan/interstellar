//
// Created by hsy on 2018/8/5.
//

#include <GL/glut.h>
#include <glm/glm.h>
#include <models/rocket.h>


rocket::rocket() {
    glm::vec3 parameter;
    // cylinder
    parameter = {0.125f, 0.125f, 2.0f};
    surface.push_back(parameter);
    // side_cylinder
    parameter = {0.125f, 0.125f, 0.5f};
    surface.push_back(parameter);
    // cone
    parameter = {0.125f, 0.0f, 0.5f};
    surface.push_back(parameter);
    //side cone
    parameter = {0.125f, 0.0f, 0.25f};
    surface.push_back(parameter);
    parameter = {0.175f, 0.125f, 0.25f};
    surface.push_back(parameter);
}

void rocket::render() {
    glColor4fv(reinterpret_cast<const GLfloat *>(&color));
    glBindTexture(GL_TEXTURE_2D, texture_id);

    obj = gluNewQuadric();

    glRotatef(90.0f, -1.0f, 0, 0);
    glTranslatef(0, 0, 0.25f);

    glPushMatrix();
    gluCylinder(obj, surface[0][0], surface[0][1], surface[0][2], 32, 32);
    glPopMatrix();

    //cone middle
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    gluCylinder(obj, surface[2][0], surface[2][1], surface[2][2], 32, 32);
    glPopMatrix();

    //left cylinder
    glPushMatrix();
    glTranslatef(-0.25f, 0.0f, 0.0f);
    gluCylinder(obj, surface[1][0], surface[1][1], surface[1][2], 32, 32);
    glPopMatrix();

    //left cone
    glPushMatrix();
    glTranslatef(-0.25f, 0.0f, 0.5f);
    gluCylinder(obj, surface[3][0], surface[3][1], surface[3][2], 32, 32);
    glPopMatrix();

    //right cylinder
    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.0f);
    gluCylinder(obj, surface[1][0], surface[1][1], surface[1][2], 32, 32);
    glPopMatrix();

    //right cone
    glPushMatrix();
    glTranslatef(0.25f, 0.0f, 0.5f);
    gluCylinder(obj, surface[3][0], surface[3][1], surface[3][2], 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.25f);
    gluCylinder(obj, surface[4][0], surface[4][1], surface[4][2], 32, 32);
    glPopMatrix();

    gluDeleteQuadric(obj);
}

rocket::~rocket() = default;