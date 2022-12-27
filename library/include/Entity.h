//
// Created by gosia on 26/12/2022.
//

#ifndef UNIVERSITY_CPP_SNAKE_PROJECT_ENTITY_H
#define UNIVERSITY_CPP_SNAKE_PROJECT_ENTITY_H
class Entity {
protected:
    unsigned int x, y;
public:
    Entity(unsigned int x, unsigned int y);

    virtual void update() = 0;
    virtual void render(Renderer& renderer) = 0;

    virtual bool is_food();

    void move(unsigned int x, unsigned int y);
    unsigned int get_x();
    unsigned int get_y();
};
#endif //UNIVERSITY_CPP_SNAKE_PROJECT_ENTITY_H
