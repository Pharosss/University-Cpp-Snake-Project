#pragma once
#include <memory>
#include "Entity.h"

class Body;
class Game;

class Head : public Entity {
    std::shared_ptr<Game> game;
    std::shared_ptr<Body> next;
public:
    Head(unsigned int x, unsigned int y, std::shared_ptr<Game> g);

    void update() override;
    void render(Renderer& renderer) override;
};