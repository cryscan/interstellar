//
// Created by lepet on 7/30/2018.
//

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <models/model.h>


using namespace std;


model::model() : texture_id(0), color({1.0f, 1.0f, 1.0f, 1.0f}) {
}

// Load a bmp file.
// Reference: https://stackoverflow.com/questions/41858408/how-to-load-texture-opengl
image* model::load_bmp(const std::string& filename) {
    ifstream is(filename, ios::binary | ios::in);
    if (!is.is_open()) {
        cerr << "Unable to open bitmap file: " << filename << endl;
        return nullptr;
    }

    unsigned long size;
    unsigned short planes;
    unsigned short bpp;

    auto* im = new image();

    is.seekg(18, ios::beg);
    is.read(reinterpret_cast<char*>(&im->size_x), sizeof(im->size_x));
    is.read(reinterpret_cast<char*>(&im->size_y), sizeof(im->size_y));

    is.read(reinterpret_cast<char*>(&planes), sizeof(planes));
    if (planes != 1) {
        cerr << "Invalid planes number in " << filename << endl;
        is.close();
        return nullptr;
    }

    is.read(reinterpret_cast<char*>(&bpp), sizeof(bpp));
    if (bpp != 24) {
        cerr << "Invalid bpp number in" << filename << endl;
        is.close();
        return nullptr;
    }

    is.seekg(24, ios::cur);
    size = im->size_x * im->size_y;
    im->data.resize(size);
    is.read(reinterpret_cast<char*>(&im->data[0]), size * 3);

    is.close();
    return im;
}

void model::load_texture(const std::string& filename) {
    image* im = load_bmp(filename);
    if (im == nullptr)
        return;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, im->size_x, im->size_y,
                      GL_BGR, GL_UNSIGNED_BYTE, &im->data[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    delete im;
}

void model::set_color(const glm::vec4& color_) {
    this->color = color_;
}
