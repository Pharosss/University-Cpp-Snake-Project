#include "Food.h"

Food::Food(unsigned x, unsigned y)
 : Entity(x, y) {};


void Food::update() {
    // here place update
};
void Food::render(Renderer& renderer) {
    // here place render
};


bool Food::is_food() {
    return true;
};