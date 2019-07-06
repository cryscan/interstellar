//
// Created by lepet on 7/30/2018.
//

#include <iostream>
#include <GL/glut.h>
#include <models/ms3d.h>


using namespace std;

ms3d::ms3d(string filename) : num_vertices{0}, num_triangles{0} {
    load(filename);
}

void ms3d::render() {
    glColor4fv(reinterpret_cast<const GLfloat*>(&color));
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(vertex), &vertices[0]);
    glNormalPointer(GL_FLOAT, sizeof(vertex), &vertices[0].normal);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), &vertices[0].tex_coord);
    glDrawElements(GL_TRIANGLES, 3 * indices.size(), GL_UNSIGNED_SHORT, &indices[0]);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

// Load model from .ms3d files.
// Reference: http://paulbourke.net/dataformats/ms3d
void ms3d::load(string& filename) {
    ifstream is(filename, ios::binary | ios::in);
    if (!is.is_open()) {
        cerr << "Unable to open model file: " << filename << endl;
        return;
    }

    // Read the header.
    ms3d_header header{{0}};
    is.read(reinterpret_cast<char*>(&header.id), sizeof(header.id));
    is.read(reinterpret_cast<char*>(&header.version), sizeof(header.version));
    // Check whether it is a MS3D file.
    if (string(header.id) != "MS3D000000") {
        cerr << "Invalid model file format in " << filename << endl;
        is.close();
        return;
    } else if (header.version != 3 && header.version != 4) {
        cerr << "Invalid model file version in" << filename << endl;
        is.close();
        return;
    }

    is.read(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));
    vertices.resize(num_vertices);

    for (int i = 0; i < num_vertices; ++i) {
        ms3d_vertex ver = {0};
        is.read(reinterpret_cast<char*>(&ver.flags), sizeof(ver.flags));
        is.read(reinterpret_cast<char*>(&ver.vertex), sizeof(ver.vertex));
        is.read(reinterpret_cast<char*>(&ver.bone_id), sizeof(ver.bone_id));
        is.read(reinterpret_cast<char*>(&ver.reference_count), sizeof(ver.reference_count));

        vertices[i].vertex = ver.vertex;
    }

    is.read(reinterpret_cast<char*>(&num_triangles), sizeof(num_triangles));
    indices.resize(num_triangles);

    for (int i = 0; i < num_triangles; ++i) {
        ms3d_triangle triangle = {0};
        is.read(reinterpret_cast<char*>(&triangle.flags), sizeof(triangle.flags));
        is.read(reinterpret_cast<char*>(&triangle.indices), sizeof(triangle.indices));
        is.read(reinterpret_cast<char*>(&triangle.normals), sizeof(triangle.normals));
        is.read(reinterpret_cast<char*>(&triangle.s), sizeof(triangle.s));
        is.read(reinterpret_cast<char*>(&triangle.t), sizeof(triangle.t));
        is.read(reinterpret_cast<char*>(&triangle.smoothing_group), sizeof(triangle.smoothing_group));
        is.read(reinterpret_cast<char*>(&triangle.group_index), sizeof(triangle.group_index));

        indices[i] = triangle.indices;
        for (int j = 0; j < 3; ++j) {
            vertex& ver = vertices[indices[i][j]];
            ver.normal += triangle.normals[j];
            ver.tex_coord[0] = triangle.s[j];
            ver.tex_coord[1] = 1.0f - triangle.t[j];
        }
    }

    // Normalize normals.
    for (auto& ver : vertices)
        ver.normal.normalize();

    is.close();
}