#pragma once
#include <string>
#include "game/Vector.h"

class Renderer {
public:
    void initialize();
    void terminate();

    /* unsigned get_viewport_width();
    unsigned get_viewport_height();
 */
    uvec2 get_viewport_pos();
    /* unsigned get_x();
    unsigned get_y(); */
    uvec2 get_pos();

    void refresh_screen();
    void clear_screen();

    void move_cursor(uvec2 pos/* unsigned x, unsigned y */);
    void move_relative(vec2 pos/* int x, int y */);

    void write(char ch);
    void write(const char* str);
    void write(std::string& str);
};