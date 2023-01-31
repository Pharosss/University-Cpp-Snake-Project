#pragma once
#include <memory>
#include "Entity.h"

class Body : public Entity {
    std::shared_ptr<Body> next;

public:
    Body(uvec2 pos);

    void render(Renderer* renderer) override;

    void attach(std::shared_ptr<Body> next);
    std::shared_ptr<Body> get_next();
    bool is_tail();

    bool is_at_recursive(uvec2 pos);
    Body* get_tail_recursive();
    void move_recursive(uvec2 pos);
};