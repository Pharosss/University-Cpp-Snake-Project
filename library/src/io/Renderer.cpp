#include "io/Renderer.h"
#include <ncurses.h>
#include <stdexcept>
#include "Renderer.h"

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

/* unsigned Renderer::get_viewport_width() {
    unsigned w, h;
    getmaxyx(stdscr, h, w);
    return w;
}
unsigned Renderer::get_viewport_height() {
    unsigned w, h;
    getmaxyx(stdscr, h, w);
    return h;
} */

/* unsigned Renderer::get_x() {
    int currx, curry;
    getyx(stdscr, curry, currx);
    return currx;
}

unsigned Renderer::get_y() {
    int currx, curry;
    getyx(stdscr, curry, currx);
    return curry;
} */

uvec2 Renderer::get_viewport_pos()
{
    uvec2 pos;
    getmaxyx(stdscr, pos);
    return pos;
}

uvec2 Renderer::get_pos()
{
    vec2 curr_pos;
    getyx(stdscr, curr_pos);
    return curr_pos;
}
void Renderer::refresh_screen()
{
    refresh();
}

void Renderer::clear_screen() {
    erase();
}

void Renderer::move_cursor(uvec2 pos/* unsigned x, unsigned y */) {
    //unsigned w, h;
    uvec2 size;
    getmaxyx(stdscr, size);
    if (pos >= size)
        throw std::runtime_error("Cursor out of bounds!");
    move(pos);
}

void Renderer::move_relative(vec2 pos/* int x, int y */) {
    //int currx, curry;
    vec2 curr_pos;
    getyx(stdscr, curr_pos);
    move_cursor(curr_pos + pos);
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
