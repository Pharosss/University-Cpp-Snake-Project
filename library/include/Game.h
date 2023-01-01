#pragma once

#include <vector>
#include <memory>

#include "Board.h"
#include "State.h"

class Entity;
class Food;

class Renderer;
class InputManager;

class Game {
    Board board;
    State state;
    std::vector<std::shared_ptr<Entity>> entities;

public:
    Game(Board b, State s);
    void init_game();    //place snake and food etc.

    void update(InputManager& input);
    void render(Renderer& renderer);

    void attach_entity(std::shared_ptr<Entity> entity);
    void detach_entity(std::shared_ptr<Entity> entity);

    void spawn_food();
    std::shared_ptr<Entity> find_food_at(unsigned int x, unsigned int y);

    Board& get_board();
    State& get_state();
};