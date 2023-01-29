#include "entities/Body.h"
#include "io/Renderer.h"

Body::Body(unsigned x, unsigned y)
    : Entity(x, y), next(nullptr) {}

void Body::render(Renderer& r) {
    r.write('&');
}

void Body::attach(std::shared_ptr<Body> next) {
    this->next = next;
}

std::shared_ptr<Body> Body::get_next() {
    return next;
}

bool Body::is_tail() {
    return !next;
}

bool Body::is_at_recursive(unsigned posx, unsigned posy) {
    if (get_x() == posx && get_y() == posy)
        return true;

    if (!is_tail())
        return next->is_at_recursive(posx, posy);

    return false;
}

Body* Body::get_tail_recursive() {
    if(is_tail())
        return this;
    else
        return next->get_tail_recursive();
}

void Body::move_recursive(unsigned x, unsigned y) {
    auto new_x = get_x(),
        new_y = get_y();
    move(x, y);
    if (!is_tail())
        next->move_recursive(new_x, new_y);
}
