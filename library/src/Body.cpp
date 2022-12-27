#include "Body.h"

Body::Body(unsigned int x, unsigned int y)
 : Entity(x, y) {};


void Body::update() {
    // here place update
};
void Body::render(Renderer& renderer) {
    // here place render
};


void Body::attach(std::shared_ptr<Body> next) {
    next = next;
};
bool Body::is_tail() {
    return !next;
};


bool Body::is_at_recursive(unsigned int x, unsigned int y) {
    return (get_x() == x && get_y() == y) || next->is_at_recursive(x, y);
};
std::shared_ptr<Body> Body::get_tail_recursive() {
    if(is_tail()) return std::make_shared<Body>(this);
    else return next->get_tail_recursive();
};
void Body::move_recursive(unsigned int x, unsigned int y) {
    auto new_x = get_x(),
        new_y = get_y();
    move(x, y);
    next->move_recursive(new_x, new_y);
};