#include "Body.h"
#include "Renderer.h"

Body::Body(unsigned int x, unsigned int y)
    : Entity(x, y), next(nullptr) {}

void Body::update() {
    // here place update
};
void Body::render(Renderer& r) {
    r.write('&');
};


void Body::attach(std::shared_ptr<Body> next) {
    this->next = next;
};
bool Body::is_tail() {
    return !next;
};


bool Body::is_at_recursive(unsigned int posx, unsigned int posy) {
    if (get_x() == posx && get_y() == posy)
        return true;

    if (!is_tail())
        return next->is_at_recursive(posx, posy);

    return false;
};
Body* Body::get_tail_recursive() {
    if(is_tail())
        return this;
    else
        return next->get_tail_recursive();
};
void Body::move_recursive(unsigned int x, unsigned int y) {
    auto new_x = get_x(),
        new_y = get_y();
    move(x, y);
    if (!is_tail())
        next->move_recursive(new_x, new_y);
};