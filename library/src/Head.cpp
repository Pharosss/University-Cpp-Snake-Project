#include "Head.h"

Head::Head(unsigned int x, unsigned int y, std::shared_ptr<Game> g)
 : Entity(x, y), game(g) {}

void Head::update() {
    // put update here
};
void Head::render(Renderer& renderer) {
    // put render here
};