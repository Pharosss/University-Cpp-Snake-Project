#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "Board.h"
#include "Food.h"

class Renderer;

class Game {
    Board board;
    std::vector<std::shared_ptr<Entity>> entities;

    float speed_seconds;
    int score;

    bool is_finished;   // is the game over?
    bool is_paused;
    bool should_move;   // is automatically set to true every 1 second. After the move it resets

public:
    Game(unsigned int w, unsigned int h, float s);
    void init_game();    //place snake and food etc.

    // speed
    float get_speed();
    float set_speed(float seconds);

    // score
    int get_score();
    bool increment_score();

    // finished?
    bool is_finished();
    void end_game();

    // paused?
    bool is_paused();
    void set_pause(bool paused);

    // should move?
    bool should_move();
    void set_should_move(bool should);

    void update();
    void render(Renderer& renderer);

    void spawn_food();
    std::shared_ptr<Food> find_food_at(unsigned int x, unsigned int y);

    Board* get_board();
    void attach_entity(std::shared_ptr<Entity> entity);
    void detach_entity(std::shared_ptr<Entity> entity);
};