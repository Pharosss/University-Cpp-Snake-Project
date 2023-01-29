#pragma once
#include "Input.h"
class Renderer;
class InputManager;

class Entity : public InputObserver {
protected:
    unsigned int x, y;
public:
    Entity(unsigned int x, unsigned int y);

    virtual void update(InputManager* input);
    virtual void render(Renderer& renderer);

    virtual bool is_food();

    void move(unsigned int x, unsigned int y);
    unsigned int get_x();
    unsigned int get_y();
};