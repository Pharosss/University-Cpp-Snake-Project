//
// Created by gosia on 26/12/2022.
//

#ifndef UNIVERSITY_CPP_SNAKE_PROJECT_BODY_H
#define UNIVERSITY_CPP_SNAKE_PROJECT_BODY_H
#include "Entity.h"
class Body : public Entity {
    std::shared_ptr<Body> next;
public:
    Body(unsigned int x, unsigned int y);

    void update();
    void render(Renderer& renderer);

    void attach(std::shared_ptr<Body> next);
    bool is_tail();

    bool is_at_recursive(unsigned int x, unsigned int y);
    std::shared_ptr<Body>get_tail_recursive();
    void move_recursive(unsigned int x, unsigned int y);
};
#endif //UNIVERSITY_CPP_SNAKE_PROJECT_BODY_H
