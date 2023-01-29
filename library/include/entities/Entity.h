#pragma once
#include "io/Input.h"
class Renderer;
class InputManager;

class Entity : public InputObserver {
protected:
    unsigned x, y;
    
public:
    Entity(unsigned x, unsigned y);

    virtual void update(InputManager* input);
    virtual void render(Renderer& renderer);

    virtual bool is_food();

    void move(unsigned x, unsigned y);
    unsigned get_x();
    unsigned get_y();
};