#include "game/Board.h"
#include "io/Renderer.h"

Board::Board(unsigned w, unsigned h)
: width(w), height(h) {}

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

bool Board::is_position_valid(unsigned x, unsigned y) {
    return (x < width && y < height);
}

unsigned Board::get_width() {
    return width;
}

unsigned Board::get_height() {
    return height;
}
