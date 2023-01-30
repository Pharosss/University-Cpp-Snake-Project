#include "game/State.h"
#include <stdexcept>

State::State() : score(0), speed_seconds(0.15f),
    m_is_finished(false), m_should_move(false) {}

// Score

int State::get_score() {
    return score;
}

void State::increment_score() {
    score++;
}

// Speed

float State::get_speed() {
    return speed_seconds;
}

float State::set_speed(float seconds) {
    if (seconds <= 0)
        throw std::runtime_error("Attempted setting zero or negative speed!");
    speed_seconds = seconds;
}

// Is Finished?

bool State::is_finished() {
    return m_is_finished;
}

void State::finish_game() {
    m_is_finished = true;
}

// Should Move?

bool State::should_move() {
    return m_should_move;
}

void State::set_should_move(bool should) {
    m_should_move = should;
}
