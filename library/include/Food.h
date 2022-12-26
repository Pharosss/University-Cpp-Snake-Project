//
// Created by gosia on 26/12/2022.
//

#ifndef UNIVERSITY_CPP_SNAKE_PROJECT_FOOD_H
#define UNIVERSITY_CPP_SNAKE_PROJECT_FOOD_H
#include "Entity.h"
class Food : public Entity {
public:
    Food(unsigned x, unsigned y);
    void update();
    void render(Renderer& renderer);

    bool is_food() override;
};
#endif //UNIVERSITY_CPP_SNAKE_PROJECT_FOOD_H
