#include "io/CLIReader.h"
#include <iostream>
#include <string>
#include <memory>

void print_help_error() {
    std::cout<<"Please write -h or -help to access teh help page\n";
}

// CLIREADER

#define END_READERS(str) {\
    std::cout << "Error! " << str << '\n'; \
    print_help_error();\
    reader->should_start = false;\
    return -1;\
    }

CLIReader::CLIReader(unsigned int default_width, unsigned int default_height, float default_speed)
  : should_start(false), board_w(default_width), board_h(default_height), speed_seconds(default_speed) {

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
        << "-s - change time duration between snake moves (double seconds).\n"
        << '\n'
        << "-H - show highscore. Does not run the game.\n"
        << "-c - clear highscore. Does not run the game.\n"
        << "-h (-help) - view this page. Does not run the game\n";
        reader->should_start = false;
        return -1;
    };

    // -H: show highscore
    argument_readers["-H"] = [](CLIReader* reader, std::string value) {
        std::cout << "Your highscore is: " << 0 << '\n';
        reader->should_start = false;
        return -1;
    };

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

    // -b: change board dimensions
    argument_readers["-b"] = [](CLIReader* reader, std::string value){
        if (value == "")
            END_READERS("Parameter -b cannot be empty!");
        
        int x_index = value.find('x');
        if (x_index == -1)
            END_READERS("Invalid board size argument. Use pattern UINTxUINT i.e. '-b 40x20'");

        try {
            int b_width = std::stoul(value.substr(0, x_index)),
                b_height = std::stoul(value.substr(x_index + 1, value.size()));
            
            if (b_width < 1 || b_height < 1)
                END_READERS("Invalid board size argument. Board size has to be at least 1x1");

            reader->board_w = b_width;
            reader->board_h = b_height;
        } catch(std::invalid_argument& e) {
            END_READERS("Invalid board size argument. Use pattern UINTxUINT i.e. '-b 40x20'")
        }
    };

    // -d: change difficulty level
    argument_readers["-d"] = [](CLIReader* reader, std::string value){
        if (value == "")
            END_READERS("Difficulty argument cannot be empty. Use either e, easy, m, medium, h or hard");
        
        if (value == "e" || value == "easy") {
            reader->speed_seconds = .2f;
        }
        else if (value == "m" || value == "medium") {
            reader->speed_seconds = .15f;
        }
        else if (value == "h" || value == "hard") {
            reader->speed_seconds = .1f;
        }
        else
            END_READERS("Invalid difficulty argument. Use either s, small, m, medium, h or hard");

        return 0;
    };

    // -s: speed (float in seconds)
    argument_readers["-s"] = [](CLIReader* reader, std::string value){
        if (value == "")
            END_READERS("Error! Speed argument cannot be empty. Use a positive float fumber");

        float new_speed = 0.f;
        try {
            new_speed = std::stof(value);
            if (new_speed <= 0.f)
                throw std::invalid_argument("");
        }
        catch (std::invalid_argument e){
            END_READERS("Invalid speed argument. Use a positive float fumber");
        }

        reader->speed_seconds = new_speed;
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
