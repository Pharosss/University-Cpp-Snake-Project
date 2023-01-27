#include "Food.h"
#include "Renderer.h"

Food::Food(unsigned x, unsigned y)
 : Entity(x, y) {};

void Food::render(Renderer& r) {
    r.write('@');
};

bool Food::is_food() {
    return true;
};