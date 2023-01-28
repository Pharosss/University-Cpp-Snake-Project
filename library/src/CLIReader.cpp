#include "CLIReader.h"
#include <iostream>
#include <string>

CLIReader::CLIReader()
 : should_start(false), board_w(40), board_h(10), speed_seconds(.15f) {}  //default parameters!

size_t find_flag(int argc, char *argv[], std::string flag) {
    for (size_t i = 1; i < argc; i++)
        if (argv[i] == flag)
            return i;
    return -1;
}

void CLIReader::analyse_arguments(int argc, char *argv[]) {

    // debug - display parameters
    std::cout << "argc: " << argc << '\n';
    for (size_t i = 0; i < argc; i++)
        std::cout << "argv " << i << ": '" << argv[i] << "'\n";

    // zero parameters - normal start
    if (argc == 1) {
        should_start = true;
        return;
    }

    // game parameters
    if (argc >= 2) {
        
    }

    // -h / -help: help page
    if (argc == 2 && (argv[1] == std::string("-h") || argv[1] == std::string("-help"))) {
        std::cout<<"Terminal Snake Game made by Mateusz Kubiak and Gosia Komorowska\n"
        << "@ Lodz University of Technology\n"
        << '\n'
        << "Controls:\n"
        << "WASD - change direction of the snake"
        << "Tab - exit the game\n"  // REMEMBER! Change it after implementing menu
        << '\n'
        << "Available options:\n"
        << "-b - change game board dimensions (pattern: 'UINTxUINT' i.e. '30x20').\n"
        << "-d - change difficulty (e - easy, m - medium, h - hard).\n"
        << "-s - change time duration between snake moves (double seconds) - uncompatible with -d.\n"
        << '\n'
        << "-H - show highscore. Does not run the game.\n"
        << "-c - clear highscore. Does not run the game.\n"
        << "-h (-help) - view this page.\n";
        return;
    }
    
    // -c: clear highscore
    if (argc == 2 && argv[1] == std::string("-c")) {
        std::cout<<"Do you really want to clear the highscore? Write [yes/no].\n";
        std::string response = "";
        while (response != "yes" && response != "no")
            std::cin >> response;

        if (response == "yes") {
            // clear the highscore
            std::cout << "Highscore cleared!\n";
        }
        else if (response == "no")
            std::cout<<"Highscore has not been cleared.\n";
        
        return;
    }

    std::cout<<"unrecognized parameters. Please write -h or -help to access teh help page\n";
}

bool CLIReader::game_should_start() {
    return should_start;
}

unsigned int CLIReader::get_board_w() {
    return board_w;
}

unsigned int CLIReader::get_board_h() {
    return board_h;
}

float CLIReader::get_speed_seconds() {
    return speed_seconds;
}
