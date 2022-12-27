//
// Created by gosia on 26/12/2022.
//
#include "Game.h"
#include <iostream>
Game::Game(unsigned int w, unsigned int h, float s){
    //tu w i h zainicjalizować
    speed_seconds=s;
}

float Game::get_speed()
{
    return speed_seconds;
}

int Game::get_score()
{
    return score;
}

bool Game::increment_score()
{
    //if()
    //get_score()++;
    return false;
}

bool Game::is_finished()
{
    return is_finished;
}

void Game::end_game()
{
    if(is_finished){//tu chyba coś dodać trzeba
        std::cout << "The game is over. You got "<< get_score()<< " scores.\n"; 
        exit(0);
    }
}

bool Game::is_paused()
{
    return is_paused;
}

void Game::set_pause(bool paused)//tu nie wiem
{
    if(is_paused())
    paused=true;
    else {
        paused=false;
        should_move()==false;
    }
}
