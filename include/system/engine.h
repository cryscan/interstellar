//
// Created by lepet on 8/2/2018.
//

#ifndef P3_ENGINE_H
#define P3_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <system/grid.h>
#include <models/model.h>
#include <objects/object.h>


// The engine should maintain all resources and objects in the scene.
class engine {
private:
    std::map<std::string, std::unique_ptr<model>> models;
    grid* park = nullptr;
    object* world = nullptr;

public:
    engine(engine const&) = delete;
    void operator =(engine const&) = delete;

    static engine& get_instance();

    model* get_model(const std::string& name);
    void add_object(std::unique_ptr<object>&& child);

    void initialize();
    void update();
    void render();
    void mouse(int button, int state, glm::vec<2, int>& pos);
    void motion(glm::vec<2, int>& pos);

private:
    engine() = default;
    void load_resources();
};


#endif //P3_ENGINE_H
