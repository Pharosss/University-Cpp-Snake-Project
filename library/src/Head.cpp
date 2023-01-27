#include "Head.h"
#include "Renderer.h"

Head::Head(unsigned int x, unsigned int y, Game* g)
 : Entity(x, y), game(g) {}

void Head::update() {
    // put update here
};
void Head::render(Renderer& r) {
    r.write('%');
};

void Head::attach(std::shared_ptr<Body> n) {
    next = n;
};
std::shared_ptr<Body> Head::get_next() {
    return next;
};

void Head::on_keepress(KeyCode code) {
    switch (code)
    {
    case K_UP: y--; break;
    case K_DOWN: y++; break;
    case K_LEFT: x--; break;
    case K_RIGHT: x++; break;
    }
};