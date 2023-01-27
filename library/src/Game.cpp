#include "Game.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <cstdint>

#include "Entity.h"
#include "Renderer.h"
#include "InputManager.h"

#include "Food.h"
#include "Body.h"
#include "Head.h"

Game::Game(Board b, State s)
 : board(b), state(s) {}

void Game::init_game(InputManager* input) {
    std::srand(std::time(0));
    input->add_observer(this);

    std::shared_ptr<Head> head = std::make_shared<Head>(4, 3, this);
    input->add_observer(head.get());
    attach_entity(head);

    auto food = std::make_shared<Food>(0, 0);
    attach_entity(food);
    move_food();
};

// Input Callback

void Game::on_keepress(KeyCode code) {
    if (code == K_RETURN)
        state.finish_game();
}

// Update and Render

void Game::update(InputManager* input) {
    if (!board.is_position_valid(entities[0]->get_x(), entities[0]->get_y()))
        state.finish_game();

    for (auto entity : entities)
        entity->update(input);
}

void Game::render(Renderer& r) {
    r.clear_screen();

    std::stringstream header;
    header << "Score: " << std::to_string(state.get_score()) << "    Input: " << state.get_input();
    std::string out = header.str();
    
    auto corner_x = (r.get_width() - board.get_width())/2 - 1;
    auto corner_y = (r.get_height() - board.get_height() - 2)/2 - 1;

    r.move_cursor(corner_x, corner_y);
    r.write(out);

    r.move_cursor(corner_x, corner_y + 2);
    unsigned int inside_board_x = r.get_x() + 1, inside_board_y = r.get_y() + 1;
    board.render(r);

    for(auto entity : entities) {
        r.move_cursor(inside_board_x + entity->get_x(), inside_board_y + entity->get_y());
        entity->render(r);
    }
    r.refresh_screen();
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

    unsigned int new_x, new_y,
        w = board.get_width(),
        h = board.get_height();

    do {
        new_x = std::rand() % w;
        new_y = std::rand() % h;
    } while (get_head()->is_at_recursive(new_x, new_y));


    get_food()->move(new_x, new_y);
}

std::shared_ptr<Entity> Game::find_food_at(unsigned int x, unsigned int y) {
    auto is_food_predicate = [](std::shared_ptr<Entity> ptr){ return ptr->is_food(); };
    auto iter = std::find_if(entities.begin(), entities.end(), is_food_predicate);

    if (iter == entities.end())
        return nullptr;

    return *iter;
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