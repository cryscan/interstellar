//
// Created by lepet on 8/4/2018.
//

#ifndef P3_GRID_H
#define P3_GRID_H

#include <vector>
#include <glm/glm.h>


enum node_type { NODE_PATH, NODE_BLOCK, NODE_EMPTY, NODE_UFO, NODE_SPACESHIP, NODE_END };
enum node_orientation { NODE_UP, NODE_LEFT, NODE_DOWN, NODE_RIGHT };

struct node {
    node_type type;
    node_orientation orientation;
    glm::vec<3, int> offset;
};

class grid {
private:
    const int columns, rows;
    std::vector<node> nodes;
    std::vector<glm::vec<2, int>> path_nodes;

    void generate();
    void generate_park(int row, node_orientation orientation);
    void generate_path(int row, node_orientation orientation);
    void generate_block(int row);

    void find_path(const node& node);

public:
    grid(int columns, int rows);
    void create_scene();
    void find_empty();
    void generate_car();
};

#endif //P3_GRID_H
