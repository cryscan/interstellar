//
// Created by lepet on 8/4/2018.
//

#ifndef P3_TILE_H
#define P3_TILE_H

#include <glm/glm.h>
#include <objects/object.h>
#include <system/grid.h>


class tile : public object {
private:
    glm::vec3 offset;
    node_orientation orientation;

public:
    tile(node_type type, node_orientation orientation, const glm::vec3& offset);
    void update() override;
};


#endif //P3_TILE_H
