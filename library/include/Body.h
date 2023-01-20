#pragma once
#include <memory>
#include "Entity.h"

class Body : public Entity {
    std::shared_ptr<Body> next;
public:
    Body(unsigned int x, unsigned int y);

    void update() override;
    void render(Renderer& renderer) override;

    void attach(std::shared_ptr<Body> next);
    bool is_tail();

    bool is_at_recursive(unsigned int x, unsigned int y);
    Body* get_tail_recursive();
    void move_recursive(unsigned int x, unsigned int y);
};