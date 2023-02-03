#include "core/State.h"
#include <stdexcept>

State::State() : score(0), speed_seconds(0.15f) {
    flags.insert({IS_FINISHED, false});
    flags.insert({SHOULD_MOVE, false});
}

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

// flags

bool State::get_flag(FlagName flag_name) {
    return flags[flag_name];
}

bool State::set_flag(FlagName flag_name, bool value) {
    flags[flag_name] = value;
}
