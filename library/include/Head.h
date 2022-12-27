//
// Created by gosia on 26/12/2022.
//

#ifndef UNIVERSITY_CPP_SNAKE_PROJECT_HEAD_H
#define UNIVERSITY_CPP_SNAKE_PROJECT_HEAD_H
#include "Body.h"
#include "Renderer.h"
#include <memory>
//#include "Game.h"
class Game;
typedef std::shared_ptr<Game> GamePtr;

class Head : public Entity {
    //std::shared_ptr<Game> game;
    GamePtr game;
    std::shared_ptr<Body> next;
public:
    //Head(unsigned int x, unsigned int y, std::shared_ptr<Game> g);
    Head(unsigned int x, unsigned int y, GamePtr g);

    void update();
    void render(Renderer& renderer);
};
#endif //UNIVERSITY_CPP_SNAKE_PROJECT_HEAD_H
