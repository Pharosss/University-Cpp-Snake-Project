#pragma once
#include "Body.h"

class Game;

class Head : public Body {
    Game* game;
    KeyCode last_arrow, new_arrow;
    
public:
    Head(uvec2 pos, Game* g);

    void update(InputManager* input) override;
    void render(Renderer& r) override;

    void move_recursive(uvec2 pos);

    void on_keepress(KeyCode code) override;
};