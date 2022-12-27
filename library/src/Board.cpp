#include "Board.h"
//#include "Renderer.h"

Board::Board(unsigned int w, unsigned int h)
: width(w), height(h) {}

bool Board::is_position_valid(unsigned int x, unsigned int y) {
    return (x <= width && y <= height);
}

void Board::render(Renderer& renderer) {
    // render here!
}