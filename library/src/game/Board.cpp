#include "game/Board.h"
#include "io/Renderer.h"
#include "Board.h"

Board::Board(uvec2 pos)
: size(pos){}//width(w), height(h) {}

void Board::render(Renderer& r) {
    for (size_t i = 0; i < size.x + 2; i++) {
        r.write('#');
    }

    r.move_relative(-size.x - 2);
    
    for (size_t j = 0; j < size.y; j++) {
        r.write('#');
        r.move_relative(size.x);
        r.write('#');
        r.move_relative(-size.x - 2);
    }

    for (size_t i = 0; i < size.x + 2; i++) {
        r.write('#');
    }    
}

/* bool Board::is_position_valid(uvec2 pos) {
    return (x < width && y < height);
} */
bool Board::is_position_valid(uvec2 pos) {
    return (pos.x<size.x && pos.y<size.y);
}
uvec2 Board::get_pos()
{
    return size;
}

/* unsigned Board::get_width() {
    return width;
}

unsigned Board::get_height() {
    return height;
} */
