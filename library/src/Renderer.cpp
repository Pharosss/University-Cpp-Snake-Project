#include "Renderer.h"
#include <ncurses.h>
#include <stdexcept>

void Renderer::initialize() {
    initscr();
	raw();
	keypad(stdscr, TRUE);
    curs_set(0);    // comment this to view cursor for debug
	noecho();
    move(0,0);
}
void Renderer::terminate() {
    endwin();
}

void Renderer::refresh_screen() {
    refresh();
}
void Renderer::clear_screen() {
    clear();
}

void Renderer::move_cursor(unsigned int x, unsigned int y) {
    unsigned int w, h;
    getmaxyx(stdscr, h, w);
    if (x >= w || y >= h)
        throw std::runtime_error("Cursor out of bounds!");
    move(y, x);
}
void Renderer::move_relative(int x, int y) {
    int currx, curry;
    getyx(stdscr, curry, currx);
    move_cursor(currx + x, curry + y);
}

void Renderer::write(char ch) {
    addch(ch);
}
void Renderer::write(const char *str) {
    printw(str);
}