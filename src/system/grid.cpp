//
// Created by lepet on 8/4/2018.
//

#include <random>
#include <algorithm>
#include <cassert>
#include <objects/object.h>
#include <objects/tile.h>
#include <objects/ufo.h>
#include <objects/spaceship.h>
#include <objects/car.h>
#include <system/engine.h>


using namespace std;

grid::grid(int C, int R) : columns(C), rows(R), size(C * R) {
    nodes.resize(size);
    generate();
}

void grid::generate() {
    assert(columns > 3);
    assert(rows >= 5);

    for (int i = 0; i < rows; ++i) {
        switch (i % 5) {
            case 0:
                generate_park(i, NODE_UP);
                break;
            case 1:
                generate_path(i, NODE_RIGHT);
                break;
            case 2:
                generate_block(i);
                break;
            case 3:
                generate_path(i, NODE_LEFT);
                break;
            case 4:
                generate_park(i, NODE_DOWN);
                break;
            default:
                break;
        }
    }
    // Leave at least one empty seat for car.
    nodes[1].type = NODE_EMPTY;
}

void grid::generate_park(int row, node_orientation orientation) {
    for (int i = 0; i < columns; ++i) {
        int n = i + columns * row;
        nodes[n].offset = {i, 0, -row};
        nodes[n].type = (i == 0 || i == columns - 1) ?
                        NODE_PATH : (node_type) (rand() % (NODE_END - NODE_EMPTY) + NODE_EMPTY);
        nodes[n].orientation = (i == 0 || i == columns - 1) ? NODE_UP : orientation;
    }
}

void grid::generate_path(int row, node_orientation orientation) {
    for (int i = 0; i < columns; ++i) {
        int n = i + columns * row;
        nodes[n].offset = {i, 0, -row};
        nodes[n].type = NODE_PATH;
        nodes[n].orientation = (i == 0 || i == columns - 1) ? NODE_UP : orientation;
    }
}

void grid::generate_block(int row) {
    for (int i = 0; i < columns; ++i) {
        int n = i + columns * row;
        nodes[n].offset = {i, 0, -row};
        nodes[n].type = (i == 0 || i == columns - 1) ? NODE_PATH : NODE_BLOCK;
    }
}

void grid::create_scene() {
    auto &engine = engine::get_instance();

    // First pass, create tiles and ufos.
    for (auto &node : nodes) {
        // Create tiles.
        object *obj = new tile(node.type, node.orientation, glm::vec3(node.offset));
        engine.add_object(obj);

        switch (node.type) {
            case NODE_UFO:
                obj = new ufo(glm::vec3(node.offset), rand() % 360, rand() % 360);
                engine.add_object(obj);
                break;
            case NODE_SPACESHIP:
                obj = new spaceship(glm::vec3(node.offset), rand() % 360);
                engine.add_object(obj);
                break;
            default:
                break;
        }
    }
}

// Find the path from origin to an empty node, storing it into a vector.
void grid::find_path(const node &node) {
    path_nodes.clear();
    if (node.type == NODE_EMPTY) {
        glm::vec<2, int> origin({0, 4});
        glm::vec<2, int> target({node.offset[0], node.offset[2]});
        int region = -target[1] / 5;
        int entry = 5 * region;
        int primary_path = entry + 1;    // The row number of primary path.
        int block = entry + 2;
        int secondary_path = entry + 3;

        path_nodes.push_back(origin);
        path_nodes.push_back(glm::vec<2, int>({0, -entry}));
        path_nodes.push_back(glm::vec<2, int>({1, -primary_path}));
        if (node.orientation == NODE_UP) {
            // This is the easy case.
            path_nodes.push_back(target + glm::vec<2, int>({0, -1}));
            path_nodes.push_back(target + glm::vec<2, int>({1, -1}));

            path_nodes.push_back(target + glm::vec<2, int>({0, -1}));
            path_nodes.push_back(target);
        } else {
            // Otherwise we should go around.
            path_nodes.push_back(glm::vec<2, int>({columns - 2, -primary_path}));
            path_nodes.push_back(glm::vec<2, int>({columns - 1, -block}));
            path_nodes.push_back(glm::vec<2, int>({columns - 2, -secondary_path}));
            path_nodes.push_back(target + glm::vec<2, int>({0, 1}));
            path_nodes.push_back(target + glm::vec<2, int>({-1, 1}));

            path_nodes.push_back(target + glm::vec<2, int>({0, 1}));
            path_nodes.push_back(target);
        }

        auto compare = [](glm::vec<2, int> &u, glm::vec<2, int> &v) {
            auto ret = u - v;
            return ret[0] == 0 && ret[1] == 0;
        };
        auto end = unique(path_nodes.begin(), path_nodes.end(), compare);
        path_nodes.resize(distance(path_nodes.begin(), end));
    }
}

void grid::find_empty() {
    vector<node> empty;
    for (auto &node : nodes)
        if (node.type == NODE_EMPTY)
            empty.push_back(node);

    int n = rand() % empty.size();
    find_path(empty[n]);
}

void grid::generate_car() {
    vector<glm::vec3> points;
    vector<glm::vec3> tangents;

    for (auto &path_node : path_nodes) {
        glm::vec3 point;
        point[0] = path_node[0];
        point[2] = path_node[1];
        points.push_back(point);
    }

    auto &engine = engine::get_instance();
    object *obj = new car(points);
    engine.add_object(obj);
}

