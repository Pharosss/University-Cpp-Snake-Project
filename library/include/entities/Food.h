#pragma once
#include "Entity.h"

class Food : public Entity {
public:
    Food(uvec2 pos);
    
    void render(Renderer* renderer);
};