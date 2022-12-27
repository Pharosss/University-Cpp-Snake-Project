#ifndef UNIVERSITY_CPP_SNAKE_PROJECT_RENDERER_H
#define UNIVERSITY_CPP_SNAKE_PROJECT_RENDERER_H

class Renderer {
public:
    Renderer();
    void set_char();
    void set_string();

    void clear_screen();
    void render_end_game();
};
#endif