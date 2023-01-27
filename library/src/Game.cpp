#include "Game.h"

#include <algorithm>
#include <string>
#include <sstream>

#include "Entity.h"
#include "Food.h"
#include "Renderer.h"
#include "InputManager.h"

#include "Head.h"
#include "Body.h"

Game::Game(Board b, State s)
 : board(b), state(s) {}

void Game::init_game(InputManager* input) {
    input->add_observer(this);

    std::shared_ptr<Head> head = std::make_shared<Head>(3, 3, this);
    input->add_observer(head.get());
    attach_entity(head);
};

// Input Callback

void Game::on_keepress(KeyCode code) {
    if (code == K_RETURN)
        state.finish_game();
}

// Update and Render

void Game::update() {
    if (!board.is_position_valid(entities[0]->get_x(), entities[0]->get_y()))
        state.finish_game();
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

void Game::spawn_food() {
    // get random empty location
    // auto f = std::make_shared(Food(x, y));
    // attach(f);
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