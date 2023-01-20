#pragma once
class Renderer;
class InputManager;

class Entity {
protected:
    unsigned int x, y;
public:
    Entity(unsigned int x, unsigned int y);

    virtual void update(InputManager& input) = 0;
    virtual void render(Renderer& renderer) = 0;

    virtual bool is_food();

    void move(unsigned int x, unsigned int y);
    unsigned int get_x();
    unsigned int get_y();
};