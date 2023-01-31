#include "entities/Head.h"
#include "io/Renderer.h"

#include "game/Game.h"
#include "entities/Food.h"
#include "io/InputManager.h"

#include <iostream>

Head::Head(uvec2 pos, Game* g)
 : Body(pos), game(g), last_arrow(K_NULL), new_arrow(K_NULL) {}

void Head::update(InputManager* input) {
    if (game->get_state().should_move()) {
        auto pos = get_pos();

        switch (new_arrow) {
            case K_UP:    move_recursive(pos + uvec2( 0, -1 )); break;
            case K_DOWN:  move_recursive(pos + uvec2( 0, 1 )); break;
            case K_LEFT:  move_recursive(pos + uvec2(-1, 0 )); break;
            case K_RIGHT: move_recursive(pos + uvec2( 1, 0 )); break;
        }

        last_arrow = new_arrow;
        game->get_state().set_should_move(false);
    }
}

void Head::render(Renderer& r) {
    r.write('%');
}

void Head::move_recursive(uvec2 pos) {
    auto old_tail = get_tail_recursive()->get_pos();
    
    Body::move_recursive(pos);

    if (game->get_food()->get_pos() == pos) {
        auto new_tail = std::make_shared<Body>(old_tail);
        get_tail_recursive()->attach(new_tail);
        game->attach_entity(new_tail);
        game->move_food();
        game->get_state().increment_score();
    }

    auto now_pos = get_pos();
    if (!is_tail() && get_next()->is_at_recursive(now_pos))
        game->get_state().finish_game();
    
}

void Head::on_keepress(KeyCode code) {
    if (code < K_UP || code > K_RIGHT)
        return;

    if (last_arrow == K_UP && code == K_DOWN ||
        last_arrow == K_DOWN && code == K_UP ||
        last_arrow == K_LEFT && code == K_RIGHT ||
        last_arrow == K_RIGHT && code == K_LEFT)
        return;

    new_arrow = code;
}