//
// Created by gosia on 26/12/2022.
//

#ifndef UNIVERSITY_CPP_SNAKE_PROJECT_BOARD_H
#define UNIVERSITY_CPP_SNAKE_PROJECT_BOARD_H
class Board {
    unsigned int width, height;
public:
    Board(unsigned int w, unsigned int h);
    bool is_position_valid(unsigned int x, unsigned int y);
    void render(Renderer& renderer);
};
#endif //UNIVERSITY_CPP_SNAKE_PROJECT_BOARD_H
