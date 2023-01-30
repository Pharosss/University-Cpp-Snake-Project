#pragma once
class Renderer;
#include "game/Vector.h"

class Board {
    //unsigned width, height;
    uvec2 size;

public:
    Board(uvec2 pos);

    void render(Renderer& renderer);

    bool is_position_valid(uvec2 pos);
    uvec2 get_pos();
    // bool is_position_valid(unsigned x, unsigned y);
    // unsigned get_width();
    // unsigned get_height();
};