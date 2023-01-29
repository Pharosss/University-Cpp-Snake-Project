#pragma once
class Renderer;

class Board {
    unsigned width, height;

public:
    Board(unsigned w, unsigned h);

    void render(Renderer& renderer);

    bool is_position_valid(unsigned x, unsigned y);
    unsigned get_width();
    unsigned get_height();
};