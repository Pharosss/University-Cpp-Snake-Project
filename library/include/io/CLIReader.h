#pragma once
#include <map>
#include <functional>
#include <string>

class CLIReader {
    bool should_start;
    unsigned int board_w;
    unsigned int board_h;
    float speed_seconds;

    std::map<std::string, std::function<int(CLIReader* reader, std::string value)>> argument_readers;

public:
    CLIReader(unsigned int default_width, unsigned int default_height, float default_speed);
    void analyse_arguments(int argc, char *argv[]);

    bool game_should_start();
    unsigned int get_board_w();
    unsigned int get_board_h();
    float get_speed_seconds();
};