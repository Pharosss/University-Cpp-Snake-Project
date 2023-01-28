#include "CLIReader.h"
#include <iostream>
#include <string>
#include <memory>

void print_help_error() {
    std::cout<<"Please write -h or -help to access teh help page\n";
}

// CLIREADER

CLIReader::CLIReader(unsigned int default_width, unsigned int default_height, float default_speed)
  : should_start(false), board_w(default_width), board_h(default_height), speed_seconds(default_speed) {

    // -c: clear highscore
    argument_readers["-c"] = [](CLIReader* reader, std::string value){  
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
        
        reader->should_start = false;
        return -1;
    };

    // -h / -help: help page
    argument_readers["-h"] = argument_readers["-help"] = [](CLIReader* reader, std::string value) {
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
        reader->should_start = false;
        return -1;
    };

    argument_readers["-b"] = [](CLIReader* reader, std::string value){
        if (value == "") {
            std::cout<<"Error! Parameter -b cannot be empty!\n";
            print_help_error();
            reader->should_start = false;
            return -1;
        }
        
        int x_index = value.find('x');
        if (x_index == -1) {
            print_help_error();
            reader->should_start = false;
            return -1;
        }

        try {
            int b_width = std::stoul(value.substr(0, x_index)),
                b_height = std::stoul(value.substr(x_index + 1, value.size()));
            
            if (b_width < 1 || b_height < 1) {
                std::cout<<"Error! Invalid board size argument. Board size has to be at least 1x1\n";
                print_help_error();
                reader->should_start = false;
                return -1;
            }

            reader->board_w = b_width;
            reader->board_h = b_height;
        } catch(std::invalid_argument& e) {
            std::cout<<"Error! Invalid board size argument. Use pattern UINTxUINT i.e. '-b 40x20'\n";
            print_help_error();
            reader->should_start = false;
            return -1;
        }
    };

    argument_readers["-d"] = [](CLIReader* reader, std::string value){
        if (value == "") {
            std::cout<<"Error! Difficulty argument cannot be empty. Use either s, small, m, medium, h or hard\n";
            print_help_error();
            reader->should_start = false;
            return -1;
        }
        
        if (value == "s" || value == "medium") {
            reader->speed_seconds = .2f;
        }
        else if (value == "m" || value == "medium") {
            reader->speed_seconds = .15f;
        }
        else if (value == "h" || value == "hard") {
            reader->speed_seconds = .1f;
        }
        else {
            std::cout<<"Error! Invalid difficulty argument. Use either s, small, m, medium, h or hard\n";
            print_help_error();
            reader->should_start = false;
            return -1;
        }

        return 0;
    };
    
}

void CLIReader::analyse_arguments(int argc, char *argv[]) {

    should_start = true;
    for (unsigned int i = 1; i < argc; i++) {
        if (argv[i][0] != '-')
            continue;
        
        if (argument_readers.find(argv[i]) == argument_readers.end()) {
            std::cout<<"Error! Unrecognized parameters.\n";
            print_help_error();
            should_start = false;
            return;
        }
        
        // forbid values starting with '-'
        std::string value = "";
        if (i+1 < argc && argv[i+1][0] != '-')  
            value = argv[i+1];

        // readers can stop further execution
        if (argument_readers.at(argv[i])(this, value) == -1) {
            return;
        }
    }
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
