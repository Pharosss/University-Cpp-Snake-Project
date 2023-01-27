#pragma once
#include <memory>
#include "Body.h"

class Game;

class Head : public Body {
    Game* game;
public:
    Head(unsigned int x, unsigned int y, Game* g);

    void render(Renderer& r) override;

    void on_keepress(KeyCode code) override;
};