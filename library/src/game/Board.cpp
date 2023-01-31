#include "game/Board.h"
#include "io/Renderer.h"
#include "game/Board.h"

Board::Board(uvec2 pos)
: size(pos){}

void Board::render(Renderer& r) {
    for (size_t i = 0; i < size.x + 2; i++) {
        r.write('#');
    }
    
    r.move_relative(vec2(-size.x - 2, 1));
    
    for (size_t j = 0; j < size.y; j++) {
        r.write('#');
        r.move_relative(vec2(size.x, 0));
        r.write('#');
        r.move_relative(vec2(-size.x - 2, 1));
    }

    for (size_t i = 0; i < size.x + 2; i++) {
        r.write('#');
    }
}

bool Board::is_position_valid(uvec2 pos) {
    return (pos.x<size.x && pos.y<size.y);
}

uvec2 Board::get_size() {
    return size;
}
