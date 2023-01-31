#include "entities/Body.h"
#include "io/Renderer.h"

Body::Body(uvec2 pos)
    : Entity(pos), next(nullptr) {}

void Body::render(Renderer* renderer) {
    renderer->write('&');
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

bool Body::is_at_recursive(uvec2 pos) {
    if (get_pos() == pos)
        return true;

    if (!is_tail())
        return next->is_at_recursive(pos);

    return false;
}

Body* Body::get_tail_recursive() {
    if(is_tail())
        return this;
    else
        return next->get_tail_recursive();
}

void Body::move_recursive(uvec2 pos) {
    auto new_pos = get_pos();
    move(pos);
    if (!is_tail())
        next->move_recursive(new_pos);
}
