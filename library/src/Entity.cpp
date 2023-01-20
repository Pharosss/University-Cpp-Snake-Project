#include "Entity.h"

Entity::Entity(unsigned int x, unsigned int y)
 : x(x), y(y) {}

bool Entity::is_food() {
    return false;
}

void Entity::move(unsigned int x, unsigned int y) {
    this->x = x; this->y = y;
}

unsigned int Entity::get_x() {
    return x;
}

unsigned int Entity::get_y() {
    return y;
}