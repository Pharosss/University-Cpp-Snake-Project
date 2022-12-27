//
// Created by gosia on 26/12/2022.
//
#include "Entity.h"
Entity::Entity(unsigned int x, unsigned int y){
    this->x=x;
    this->y=y;
}

bool Entity::is_food()
{
    return false;
}

unsigned int Entity::get_x()
{
    return x;
}

unsigned int Entity::get_y()
{
    return y;
}
