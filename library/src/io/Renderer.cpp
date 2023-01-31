#include "io/Renderer.h"
#include <ncurses.h>
#include <stdexcept>

void Renderer::initialize() {
    initscr();  // lib init

    raw();               // disable line buffering (raw() puts special chars on the screen)
	keypad(stdscr, TRUE);   // enable arrow input
    curs_set(0);            // comment this to view cursor for debug
	noecho();               // disable echoing input
    
    move(0,0);
}

void Renderer::terminate() {
    endwin();
}

uvec2 Renderer::get_viewport_size() {
    uvec2 pos;
    getmaxyx(stdscr, pos.y, pos.x);
    return pos;
}

uvec2 Renderer::get_pos() {
    uvec2 curr_pos;
    getyx(stdscr, curr_pos.y, curr_pos.x);
    return curr_pos;
}

void Renderer::refresh_screen() {
    refresh();
}

void Renderer::clear_screen() {
    erase();
}

void Renderer::move_cursor(uvec2 pos) {
    uvec2 size = get_viewport_size();
    if (pos >= size)
        throw std::runtime_error("Cursor out of bounds!");
    move(pos.y, pos.x);
}

void Renderer::move_relative(vec2 pos) {
    uvec2 curr_pos = get_pos();
    move_cursor(uvec2(curr_pos.x + pos.x, curr_pos.y + pos.y));
}

void Renderer::write(char ch) {
    addch(ch);
}

void Renderer::write(const char *str) {
    printw(str);
}

void Renderer::write(std::string &str) {
    printw(str.c_str());
}
