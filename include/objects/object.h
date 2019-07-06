//
// Created by lepet on 7/31/2018.
//

#ifndef P3_BODY_H
#define P3_BODY_H

#include <vector>
#include <memory>

#include <glm/glm.h>
#include <models/model.h>

class object {
protected:
    model* mesh;
    glm::mat4 transform;
    std::vector<std::unique_ptr<object>> children;

public:
    object();
    explicit object(model* mesh);
    virtual ~object() = default;

    virtual void update();
    virtual void mouse(int button, int state, const glm::vec<2, int>& pos);
    virtual void motion(const glm::vec<2, int>& pos);
    virtual void render(int pass);

    void add_child(std::unique_ptr<object>&& child);
};


#endif //P3_BODY_H
