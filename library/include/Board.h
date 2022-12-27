#pragma once
class Renderer;

class Board {
    unsigned int width, height;
public:
    Board(unsigned int w, unsigned int h);
    bool is_position_valid(unsigned int x, unsigned int y);
    void render(Renderer& renderer);
};