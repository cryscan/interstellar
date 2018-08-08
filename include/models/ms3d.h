//
// Created by lepet on 7/30/2018.
//

#ifndef P3_MS3D_H
#define P3_MS3D_H

#include <string>
#include <vector>
#include <fstream>
#include <models/model.h>


// Load milkshape 3d models.
// Reference: http://paulbourke.net/dataformats/ms3d/ms3dspec.h
class ms3d : public model {
public:
    explicit ms3d(std::string filename);

    void render() override;

private:
    typedef unsigned char byte;
    typedef unsigned short word;

    // File header.
    struct ms3d_header {
        char id[10];
        unsigned version;
    };

    word num_vertices;
    struct ms3d_vertex {
        byte flags;
        glm::vec3 vertex;
        char bone_id;
        byte reference_count;
    };

    word num_triangles;
    struct ms3d_triangle {
        word flags;
        glm::vec<3, word> indices;
        glm::mat3 normals;
        glm::vec3 s;
        glm::vec3 t;
        byte smoothing_group;
        byte group_index;
    };
    // We don't need other information...

    void load(std::string &filename);

    std::vector<vertex> vertices;
    std::vector<glm::vec<3, word>> indices;
};


#endif //P3_MS3D_H
