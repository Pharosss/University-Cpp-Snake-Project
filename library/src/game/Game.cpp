#include "game/Game.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdint>

#include "io/Renderer.h"
#include "io/InputManager.h"

#include "entities/Food.h"
#include "entities/Head.h"

// Input Callback

void Game::on_action(ActionCode code) {
    if (code == A_RETURN)
        state.finish_game();
}

Game::Game(Board b, State s)
 : board(b), state(s) {}

void Game::init_game(InputManager* input) {
    std::srand(std::time(0));
    input->add_observer(this);

    auto head = std::make_shared<Head>(get_board().get_size() / 2 - uvec2(1,1), this);
    input->add_observer(head.get());
    attach_entity(head);

    auto food = std::make_shared<Food>(uvec2(0, 0));
    attach_entity(food);
    move_food();
}

// Update and Render

void Game::update(InputManager* input) {
    if (!board.is_position_valid(entities[0]->get_pos()) )
        state.finish_game();

    entities[0]->update(input);
    entities[1]->update(input);
}

void Game::render(Renderer* r) {
    r->clear_screen();

    std::stringstream header;
    header << "Score: " << std::to_string(state.get_score());
    std::string out = header.str();
    
    auto corner = (r->get_viewport_size() - board.get_size() - uvec2(0,2)) / 2 - uvec2(1, 1);

    r->move_cursor(corner);
    r->write(out);

    r->move_cursor(corner + uvec2(0,2));
    uvec2 inside_board = r->get_pos() + uvec2(1,1);
    board.render(r);

    for(auto entity : entities) {
        r->move_cursor(inside_board + entity->get_pos());
        entity->render(r);
    }
    r->refresh_screen();
}

//Entity List

void Game::attach_entity(std::shared_ptr<Entity> entity) {
    auto iter = std::find(entities.begin(), entities.end(), entity);
    if (iter != entities.end())
        throw std::runtime_error("Attempted to attach an entity twice!");
    
    entities.push_back(entity);
}
void Game::detach_entity(std::shared_ptr<Entity> entity) {
    auto iter = std::find(entities.begin(), entities.end(), entity);
    if (iter == entities.end())
        throw std::runtime_error("Attempted to detach a detached entity!");

    entities.erase(iter);
}

// Food

void Game::move_food() {

        uvec2 new_size(0,0),
            size = board.get_size();
    do {
        new_size = uvec2(std::rand() % size.x, std::rand() % size.y);
    } while (get_head()->is_at_recursive(new_size));

    get_food()->move(new_size);
}

// Getters and Setters

Board& Game::get_board() {
    return board;
}

State& Game::get_state() {
    return state;
}

Head* Game::get_head() {
    if (!entities.size())
        return nullptr;
    
    return reinterpret_cast<Head*>(entities[0].get());
}

Food* Game::get_food() {
    if (entities.size() < 2)
        return nullptr;
    
    return reinterpret_cast<Food*>(entities[1].get());
}