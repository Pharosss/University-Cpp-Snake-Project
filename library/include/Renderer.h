#pragma once
#include <string>

class Renderer {
public:
    void initialize();
    void terminate();

    unsigned int get_width();
    unsigned int get_height();

    unsigned int get_x();
    unsigned int get_y();

    void refresh_screen();
    void clear_screen();

    void move_cursor(unsigned int x, unsigned int y);
    void move_relative(int x, int y);

    void write(char ch);
    void write(const char* str);
    void write(std::string& str);
};