#pragma once
#include <string>
#include <map>

enum FlagName {
    IS_FINISHED, SHOULD_MOVE
};

class State {
    unsigned score;
    float speed_seconds;

    std::map<FlagName, bool> flags;

public:
    State();

    float get_speed();
    float set_speed(float seconds);

    int get_score();
    void increment_score();

    bool get_flag(FlagName flag_name);
    bool set_flag(FlagName flag_name, bool value);
};