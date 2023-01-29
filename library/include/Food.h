#pragma once
#include "Entity.h"

class Food : public Entity {
public:
    Food(unsigned x, unsigned y);
    void render(Renderer& renderer);

    bool is_food() override;
};