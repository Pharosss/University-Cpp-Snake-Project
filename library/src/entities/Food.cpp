#include "entities/Food.h"
#include "io/Renderer.h"

Food::Food(uvec2 pos)
 : Entity(pos) {}

void Food::render(Renderer& r) {
    r.write('@');
}
