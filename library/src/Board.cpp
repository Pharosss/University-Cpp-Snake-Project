#include "Board.h"
#include "Renderer.h"

Board::Board(unsigned int w, unsigned int h)
: width(w), height(h) {}

bool Board::is_position_valid(unsigned int x, unsigned int y) {
    return (x <= width && y <= height);
}

void Board::render(Renderer& r) {
    for (size_t i = 0; i < width + 2; i++) {
        r.write('#');
    }

    r.move_relative(-width - 2, 1);
    
    for (size_t j = 0; j < height; j++) {
        r.write('#');
        r.move_relative(width, 0);
        r.write('#');
        r.move_relative(-width - 2, 1);
    }

    for (size_t i = 0; i < width + 2; i++) {
        r.write('#');
    }    
}

unsigned int Board::get_width() {
    return width;
};
unsigned int Board::get_height() {
    return height;
};