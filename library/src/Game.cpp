#include "Game.h"

#include <iostream>
#include <algorithm>

#include "Entity.h"
#include "Food.h"
#include "Renderer.h"

#include "Head.h"
#include "Body.h"

Game::Game(Board b, State s)
 : board(b), state(s) {}

void Game::init_game() {
    auto f1 = std::make_shared<Food>(0,0);
    auto f2 = std::make_shared<Head>(1,0, this);
    auto f3 = std::make_shared<Body>(2,0);

    attach_entity(f1);
    attach_entity(f2);
    attach_entity(f3);
}


// Update and Render

void Game::update() {
    // place update here
}
void Game::render(Renderer& r) {
    r.clear_screen();
    board.render(r);

    for(auto entity : entities) {
        r.move_cursor(entity->get_x() + 1, entity->get_y() + 1);
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