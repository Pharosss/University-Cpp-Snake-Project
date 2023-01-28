#include "CLIReader.h"
#include <iostream>
#include <string>

// UTIL

std::string find_flag_value(int argc, char *argv[], std::string flag) {
    int index = -1;
    std::string value = "";

    for (int i = 1; i < argc; i++)
        if (argv[i] == flag)
            index = i;
    
    if (index > -1 && index + 1 < argc)
        value = argv[index + 1];

    return value;
}

void print_help_error() {
    std::cout<<"Please write -h or -help to access teh help page\n";
}





// OPTIONS

void option_help_page() {
    std::cout<<"Terminal Snake Game made by Mateusz Kubiak and Gosia Komorowska\n"
        << "@ Lodz University of Technology\n"
        << '\n'
        << "Controls:\n"
        << "WASD - change direction of the snake"
        << "Tab - exit the game\n"  // REMEMBER! Change it after implementing menu
        << '\n'
        << "Available options:\n"
        << "-b - change game board dimensions (pattern: 'UINTxUINT' i.e. '-b 40x20').\n"
        << "-d - change difficulty (e - easy, m - medium, h - hard).\n"
        << "-s - change time duration between snake moves (double seconds) - uncompatible with -d.\n"
        << '\n'
        << "-H - show highscore. Does not run the game.\n"
        << "-c - clear highscore. Does not run the game.\n"
        << "-h (-help) - view this page.\n";
}

void option_clear_cache() {
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
}


// CLIREADER

CLIReader::CLIReader(unsigned int default_width, unsigned int default_height, float default_speed)
  : should_start(false),
    board_w(default_width),
    board_h(default_height),
    speed_seconds(default_speed) {}  //default parameters!

void CLIReader::analyse_arguments(int argc, char *argv[]) {

    // display parameters for debug
    // std::cout << "argc: " << argc << '\n';
    // for (size_t i = 0; i < argc; i++)
    //     std::cout << "argv " << i << ": '" << argv[i] << "'\n";

    // zero parameters - normal start
    if (argc == 1) {
        should_start = true;
        return;
    }

    // -h / -help: help page
    if (argc == 2 && (argv[1] == std::string("-h") || argv[1] == std::string("-help"))) {
        option_help_page();
        return;
    }
    
    // -c: clear highscore
    if (argc == 2 && argv[1] == std::string("-c")) {
        option_clear_cache();
        return;
    }

    // game parameters
    if (argc >= 2) {
        std::string b_param = find_flag_value(argc, argv, "-b"),
                    d_param = find_flag_value(argc, argv, "-d"),
                    s_param = find_flag_value(argc, argv, "-s");

        std::cout<<"-b: " << b_param << '\n';
        std::cout<<"-d: " << d_param << '\n';
        std::cout<<"-s: " << s_param << '\n';

        // b - board dimensions
        if (b_param != "") {
            int x_index = b_param.find('x');
            if (x_index == -1) {
                print_help_error();
                return;
            }

            try {
                int b_width = std::stoul(b_param.substr(0, x_index)),
                    b_height = std::stoul(b_param.substr(x_index + 1, b_param.size()));
                
                if (b_width < 1 || b_height < 1) {
                    std::cout<<"Error! Invalid board size argument. Board size has to be at least 1x1\n";
                    print_help_error();
                }

                board_w = b_width;
                board_h = b_height;
            } catch(std::invalid_argument& e) {
                std::cout<<"Error! Invalid board size argument. Use pattern UINTxUINT i.e. '-b 40x20'\n";
                print_help_error();
                return;
            }
        }

        // Error - both -s and -d params
        if (s_param != "" && d_param != "") {
            std::cout<<"Error! Difficulty parameter -d and speed parameter -s cannot coexist!\n";
            print_help_error();
            return;
        }

        should_start = true;
        return;
    }



    std::cout<<"Error! Unrecognized parameters.\n";
    print_help_error();
}



// GETTERS

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
