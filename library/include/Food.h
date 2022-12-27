#pragma once
#include "Entity.h"

class Food : public Entity {
public:
    Food(unsigned x, unsigned y);
    void update();
    void render(Renderer& renderer);

    bool is_food() override;
};