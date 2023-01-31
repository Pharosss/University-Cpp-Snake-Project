#include "entities/Entity.h"

Entity::Entity(uvec2 pos)
 : pos(pos) {}

void Entity::update(InputManager* input) {
    // intentionally left blank
}

void Entity::render(Renderer& renderer) {
    // intentionally left blank
}

void Entity::move(uvec2 pos) {
    this->pos = pos;
}

uvec2 Entity::get_pos() {
    return pos;
}
