#include "Head.h"
#include "Renderer.h"
#include "Game.h"
#include "Food.h"
#include "InputManager.h"
#include <iostream>

Head::Head(unsigned int x, unsigned int y, Game* g)
 : Body(x, y), game(g), last_arrow(K_NULL), new_arrow(K_NULL) {}

void Head::update(InputManager* input) {
    if (game->get_state().should_move()) {
        auto x = get_x(), y = get_y();

        switch (new_arrow) {
            case K_UP:    move_recursive(x, y-1); break;
            case K_DOWN:  move_recursive(x, y+1); break;
            case K_LEFT:  move_recursive(x-1, y); break;
            case K_RIGHT: move_recursive(x+1, y); break;
        }

        last_arrow = new_arrow;
        game->get_state().set_should_move(false);
    }
    
}

void Head::render(Renderer& r) {
    r.write('%');
};

void Head::move_recursive(unsigned int x, unsigned int y) {
    auto old_tail_x = get_tail_recursive()->get_x(),
        old_tail_y = get_tail_recursive()->get_y();
    
    Body::move_recursive(x, y);
    
    auto food = game->get_food();

    if (food->get_x() == x && food->get_y() == y) {
        auto new_tail = std::make_shared<Body>(old_tail_x, old_tail_y);
        get_tail_recursive()->attach(new_tail);
        game->attach_entity(new_tail);
        game->move_food();
        game->get_state().increment_score();
    }

    auto now_x = get_x(), now_y = get_y();
    if (!is_tail() && get_next()->is_at_recursive(now_x, now_y))
        game->get_state().finish_game();
    
};

void Head::on_keepress(KeyCode code) {
    if (code < K_UP || code > K_RIGHT)
        return;

    if (last_arrow == K_UP && code == K_DOWN ||
        last_arrow == K_DOWN && code == K_UP ||
        last_arrow == K_LEFT && code == K_RIGHT ||
        last_arrow == K_RIGHT && code == K_LEFT)
        return;

    new_arrow = code;
};