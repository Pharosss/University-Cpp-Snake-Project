#pragma once
#include <memory>
#include "Entity.h"

class Body : public Entity {
    std::shared_ptr<Body> next;

public:
    Body(unsigned x, unsigned y);

    void render(Renderer& renderer) override;

    void attach(std::shared_ptr<Body> next);
    std::shared_ptr<Body> get_next();
    bool is_tail();

    bool is_at_recursive(unsigned x, unsigned y);
    Body* get_tail_recursive();
    void move_recursive(unsigned x, unsigned y);
};