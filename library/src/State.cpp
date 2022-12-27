#include "State.h"
#include <stdexcept>

State::State() : score(0), speed_seconds(0.5f),
    m_is_finished(false), m_is_paused(false), m_should_move(false) {}


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
};


// Finished?
bool State::is_finished() {
    return m_is_finished;
}
void State::finish_game() {
    m_is_finished = true;
}


// Paused?
bool State::is_paused() {
    return m_is_paused;
}
void State::set_pause(bool paused) {
    m_is_paused = paused;
}

// Should Move?
bool State::should_move() {
    return m_should_move;
};
void State::set_should_move(bool should) {
    m_should_move = should;
};