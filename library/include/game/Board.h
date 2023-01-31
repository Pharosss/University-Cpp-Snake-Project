#pragma once
class Renderer;
#include "game/Vector.h"

class Board {
    uvec2 size;

public:
    Board(uvec2 pos);

    void render(Renderer* renderer);

    bool is_position_valid(uvec2 pos);
    uvec2 get_size();
};