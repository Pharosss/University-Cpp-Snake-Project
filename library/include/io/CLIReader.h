#pragma once
#include <map>
#include <functional>
#include <string>
#include "core/Vector.h"

class CLIReader {
    bool should_start;

    uvec2 board_size;
    float speed_seconds;
    std::string highscore_path;

    std::map<std::string, std::function<int(CLIReader* reader, std::string value)>> argument_readers;

public:
    CLIReader(uvec2 default_size, float default_speed, std::string highscore_path);
    void analyse_arguments(int argc, char *argv[]);

    bool game_should_start();
    uvec2 get_board_size();
    float get_speed_seconds();
};