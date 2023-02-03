#include "entities/Head.h"
#include "io/Renderer.h"

#include "core/Game.h"
#include "entities/Food.h"
#include "io/InputManager.h"

#include <iostream>

void Head::on_action(ActionCode code) {
    if (code < A_UP || code > A_RIGHT)
        return;

    if (last_arrow == A_UP && code == A_DOWN ||
        last_arrow == A_DOWN && code == A_UP ||
        last_arrow == A_LEFT && code == A_RIGHT ||
        last_arrow == A_RIGHT && code == A_LEFT)
        return;

    new_arrow = code;
}

Head::Head(uvec2 pos, Game* g)
 : Body(pos), game(g), last_arrow(A_NULL), new_arrow(A_NULL) {}

void Head::update(InputManager* input) {
    if (!game->get_state().get_flag(SHOULD_MOVE))
        return;
    
    auto pos = get_pos();

    switch (new_arrow) {
        case A_UP:    move_recursive(pos + uvec2( 0,-1 )); break;
        case A_DOWN:  move_recursive(pos + uvec2( 0, 1 )); break;
        case A_LEFT:  move_recursive(pos + uvec2(-1, 0 )); break;
        case A_RIGHT: move_recursive(pos + uvec2( 1, 0 )); break;
    }

    last_arrow = new_arrow;
    game->get_state().set_flag(SHOULD_MOVE, false);
}

void Head::render(Renderer* renderer) {
    renderer->write('%');
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
        game->get_state().set_flag(IS_FINISHED, true);
    
}
