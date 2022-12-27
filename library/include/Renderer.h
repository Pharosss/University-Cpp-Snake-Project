#pragma once
#include <string>

class Renderer {
public:
    void initialize();
    void terminate();

    void refresh_screen();
    void clear_screen();

    void move_cursor(unsigned int x, unsigned int y);
    void move_relative(int x, int y);

    void write(char ch);
    void write(const char* str);
};