//
// Created by lepet on 7/31/2018.
//

#ifndef P3_BODY_H
#define P3_BODY_H

#include <vector>

#include <glm/glm.h>
#include <models/model.h>

class object {
protected:
    model *mesh;
    glm::mat4 transform;
    std::vector<object *> children;

public:
    object();
    explicit object(model *mesh);
    ~object();

    virtual void update();
    virtual void mouse(int button, int state, glm::vec<2, int> &pos);
    virtual void motion(glm::vec<2, int> &pos);
    virtual void render(int pass);

    void add_child(object *child);
};


#endif //P3_BODY_H
