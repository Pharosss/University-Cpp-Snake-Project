#pragma once
#include <memory>
#include "Entity.h"

class Body;
class Game;

class Head : public Entity {
    Game* game;
    std::shared_ptr<Body> next;
public:
    Head(unsigned int x, unsigned int y, Game* g);

    void update(InputManager& input) override;
    void render(Renderer& renderer) override;

    void attach(std::shared_ptr<Body>n);
    std::shared_ptr<Body> get_next();
};