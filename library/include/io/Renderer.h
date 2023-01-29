#pragma once
#include <string>

class Renderer {
public:
    void initialize();
    void terminate();

    unsigned get_viewport_width();
    unsigned get_viewport_height();

    unsigned get_x();
    unsigned get_y();

    void refresh_screen();
    void clear_screen();

    void move_cursor(unsigned x, unsigned y);
    void move_relative(int x, int y);

    void write(char ch);
    void write(const char* str);
    void write(std::string& str);
};