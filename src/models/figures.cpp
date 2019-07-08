//
// Created by lepet on 7/30/2018.
//

#include <GL/glut.h>
#include <models/figures.h>


void figure::render() {
    glColor3dv(reinterpret_cast<const GLdouble*>(&color));
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(vertex), &vertices[0]);
    glNormalPointer(GL_FLOAT, sizeof(vertex), &vertices[0].normal);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), &vertices[0].tex_coord);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

figure::figure() : vertices(), indices() {
}


rectangle::rectangle() : point({0.5f, 0.5f}) {
    init_model();
}

rectangle::rectangle(const glm::vec2& point) : point(point) {
    init_model();
}

void rectangle::init_model() {
    vertices.resize(4);

    vertex& vertex1 = vertices[0];
    vertex1.vertex = point * glm::vec2({-1, 1});
    vertex1.normal = {0.0, 0.0, 1.0};
    vertex1.tex_coord = {0.0, 0.0};

    vertex& vertex2 = vertices[1];
    vertex2.vertex = point;
    vertex2.normal = {0.0, 0.0, 1.0};
    vertex2.tex_coord = {0.0, 1.0};

    vertex& vertex3 = vertices[2];
    vertex3.vertex = point * glm::vec2({1, -1});
    vertex3.normal = {0.0, 0.0, 1.0};
    vertex3.tex_coord = {1.0, 0.0};

    vertex& vertex4 = vertices[3];
    vertex4.vertex = point * glm::vec2({-1, -1});
    vertex3.normal = {0.0, 0.0, 1.0};
    vertex3.tex_coord = {1.0, 1.0};

    indices = {0, 1, 2, 2, 3, 0};
}