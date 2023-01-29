#pragma once
#include <map>
#include <functional>
#include <string>

class CLIReader {
    bool should_start;
    unsigned board_w;
    unsigned board_h;
    float speed_seconds;
    std::string highscore_path;

    std::map<std::string, std::function<int(CLIReader* reader, std::string value)>> argument_readers;

public:
    CLIReader(unsigned default_width, unsigned default_height, float default_speed, std::string highscore_path);
    void analyse_arguments(int argc, char *argv[]);

    bool game_should_start();
    unsigned get_board_w();
    unsigned get_board_h();
    float get_speed_seconds();
};