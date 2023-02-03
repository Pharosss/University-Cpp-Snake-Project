#pragma once

#include "io/Input.h"
#include "core/Vector.h"

class Renderer;
class InputManager;

class Entity : public InputObserver {
protected:
    uvec2 pos;
    
public:
    Entity(uvec2 pos);

    virtual void update(InputManager* input);
    virtual void render(Renderer* renderer);

    void move(uvec2 pos);
    uvec2 get_pos();
};