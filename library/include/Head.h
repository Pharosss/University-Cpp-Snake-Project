#pragma once
#include <memory>
#include "Body.h"

class Game;

class Head : public Body {
    Game* game;
public:
    Head(unsigned int x, unsigned int y, Game* g);

    void update(InputManager* input) override;
    void render(Renderer& r) override;
    void move_recursive(unsigned int x, unsigned int y);

    void on_keepress(KeyCode code) override;
};