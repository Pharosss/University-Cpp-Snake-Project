#include "entities/Entity.h"

Entity::Entity(unsigned x, unsigned y)
 : x(x), y(y) {}

void Entity::update(InputManager* input) {
    // intentionally left blank
}
void Entity::render(Renderer& renderer) {
    // intentionally left blank
}

bool Entity::is_food() {
    return false;
}

void Entity::move(unsigned x, unsigned y) {
    this->x = x; this->y = y;
}

unsigned Entity::get_x() {
    return x;
}

unsigned Entity::get_y() {
    return y;
}