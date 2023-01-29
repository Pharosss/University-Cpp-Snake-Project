#pragma once
#include "Body.h"

class Game;

class Head : public Body {
    Game* game;
    KeyCode last_arrow, new_arrow;
    
public:
    Head(unsigned x, unsigned y, Game* g);

    void update(InputManager* input) override;
    void render(Renderer& r) override;

    void move_recursive(unsigned x, unsigned y);

    void on_keepress(KeyCode code) override;
};