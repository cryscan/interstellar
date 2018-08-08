//
// Created by lepet on 8/2/2018.
//

#include <iostream>

#include <models/model.h>
#include <models/ms3d.h>

#include <objects/object.h>
#include <objects/camera.h>

#include <system/grid.h>
#include <system/engine.h>

using namespace std;

engine &engine::get_instance() {
    static engine instance;
    return instance;
}

model *engine::get_model(const string &name) {
    auto iter = models.find(name);
    if (iter == models.end()) {
        cerr << "Cannot locate model " << name << endl;
        return nullptr;
    } else
        return iter->second;
}

void engine::add_object(object *child) {
    world->add_child(child);
}

// Load models and textures.
void engine::load_resources() {
    // Load car.
    model *mesh = new ms3d("./data/car/car.ms3d");
    mesh->load_texture("./data/car/car.bmp");
    models.insert({"car.body", mesh});

    mesh = new ms3d("./data/car/wheel.ms3d");
    mesh->load_texture("./data/car/wheel.bmp");
    models.insert({"car.wheel", mesh});

    // Load ufo body.
    mesh = new ms3d("./data/ufo/body.ms3d");
    mesh->load_texture("./data/ufo/diffuse.bmp");
    models.insert({"ufo.body", mesh});

    // Load ufo cockpit.
    mesh = new ms3d("./data/ufo/cockpit.ms3d");
    mesh->load_texture("./data/ufo/diffuse_glow.bmp");
    models.insert({"ufo.cockpit", mesh});

    // Load rocket.
    mesh = new ms3d("./data/rocket/rocket.ms3d");
    glm::vec4 color_black = {0, 0, 0, 1.0f};
    mesh->set_color(color_black);
    models.insert({"rocket", mesh});

    // Load tiles.
    mesh = new ms3d("./data/tiles/tile.ms3d");
    mesh->load_texture("./data/tiles/block.bmp");
    models.insert({"tiles.block", mesh});

    mesh = new ms3d("./data/tiles/tile.ms3d");
    mesh->load_texture("./data/tiles/park.bmp");
    models.insert({"tiles.park", mesh});

    mesh = new ms3d("./data/tiles/tile.ms3d");
    mesh->load_texture("./data/tiles/path.bmp");
    models.insert({"tiles.path", mesh});
}

void engine::initialize() {
    load_resources();
    // Initialize world as the parent of all other objects.
    world = new camera(glm::vec3{2.0f, 6.0f, 6.0f}, glm::vec3{3.5f, 0, -4.5f}, glm::vec3({0, 1, 0}));
    park = new grid(8, 10);
    park->create_scene();
    park->find_empty();
    park->generate_car();
}

void engine::update() {
    world->update();
}

void engine::render() {
    // Render for 3 passes.
    // The first pass, render normal objects.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    world->render(0);

    // The second pass, render outlines.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    world->render(1);

    // Last pass, render objects with outlines.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    world->render(2);
}

void engine::mouse(int button, int state, glm::vec<2, int> &pos) {
    world->mouse(button, state, pos);
}

void engine::motion(glm::vec<2, int> &pos) {
    world->motion(pos);
}
