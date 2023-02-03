#pragma once
#include "Body.h"

class Game;

class Head : public Body {
    Game* game;
    ActionCode last_arrow, new_arrow;
    
    void on_action(ActionCode code) override;
    
public:
    Head(uvec2 pos, Game* g);

    void update(InputManager* input) override;
    void render(Renderer* renderer) override;

    void move_recursive(uvec2 pos);

    ActionCode get_current_direction();
};