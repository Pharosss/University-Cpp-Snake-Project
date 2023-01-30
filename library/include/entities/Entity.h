#pragma once
#include "io/Input.h"
#include "game/Vector.h"
class Renderer;
class InputManager;

class Entity : public InputObserver {
protected:
    //unsigned x, y;
    uvec2 pos;
    
public:
    Entity(uvec2 pos);

    virtual void update(InputManager* input);
    virtual void render(Renderer& renderer);

    void move(uvec2 pos);
    /* unsigned get_x();
    unsigned get_y(); */
    uvec2 get_pos();
};