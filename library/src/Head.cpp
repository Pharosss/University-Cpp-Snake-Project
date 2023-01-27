#include "Head.h"
#include "Renderer.h"
#include "Game.h"
#include "Food.h"

Head::Head(unsigned int x, unsigned int y, Game* g)
 : Body(x, y), game(g) {}

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
    }
};


void Head::on_keepress(KeyCode code) {

    auto x = get_x(), y = get_y();

    switch (code)
    {
    case K_UP:    move_recursive(x, y-1); break;
    case K_DOWN:  move_recursive(x, y+1); break;
    case K_LEFT:  move_recursive(x-1, y); break;
    case K_RIGHT: move_recursive(x+1, y); break;
    }
};