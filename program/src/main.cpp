#include <chrono>
#include "Game.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>

#include "Renderer.h"
#include "InputManager.h"

void renderer_demo() {
    Renderer r;
    r.initialize();

    r.write("Hello Ncurses!");
    r.write(" Screen dimensions: ");
    std::string dims = std::to_string(r.get_width()) + " x " + std::to_string(r.get_height());
    r.write(dims);
    r.move_cursor(0, 2);
    r.write("You can move to a discrete location");
    r.move_relative(-1, 2);
    r.write("Or to a relative one ...");
    r.write("Always remember to refresh_screen() at the end!");
    r.refresh_screen();
    getchar();

    r.clear_screen();
    try {
        r.move_cursor(-1, -2);
    }
    catch(std::exception e) {
        r.write("Moving out of the bounds throws exception!");
    }
    r.refresh_screen();
    getchar();

    r.terminate();
}

int main(int argc, char *argv[]) {

    std::cout << "argc: " << argc << '\n';
    for (size_t i = 0; i < argc; i++)
        std::cout << "argv " << i << ": '" << argv[i] << "'\n";

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
        return 0;
    }
    else if (argc == 2 && argv[1] == std::string("-c")) {
        std::cout<<"Do you really want to clear the highscore? Write [yes/no].\n";
        std::string response = "";
        while (response != "yes" && response != "no")
            std::cin >> response;

        if (response == "yes") {
            // clear the highscore
            std::cout << "Highscore cleared!\n";
            return 0;
        }
        else if (response == "no") {
            std::cout<<"Highscore has not been cleared.\n";
            return 0;
        }
    }
    else if (argc >= 2) {




    }
    else {
        std::cout<<"unrecognized parameters. Please write -h or -help to access teh help page\n";
        return 0; 
    }

    return 0;

    // creating a State object to get to know the score
    State state;
    // working with a file
    // std::ifstream ifile;
    // int number;
    /*ifile.open("file.txt");
    
    if(ifile) {
        if(ifile.is_open())
    {
        std::cout<<"Your current score: "<< number<<'\n';
        
        while(ifile >> number)
        if(state.get_score()>number){
             number=state.get_score();
            std::cout<<"You have improved. You currently score is: "<< number <<'\n';
         }
    }
      ifile.close();
    } else {
      std::cout<<"file doesn't exist";
    } */


    // using exception
    // try{
    //     if(ifile){
    //         try{
    //             if(ifile.is_open()){
    //                 ifile >> number;
    //                 std::cout<<"Your current score: "<< number<<'\n';
    //                 if(state.get_score()>number){
    //                 number=state.get_score();
    //                 std::cout<<"You have improved. You currently score is: "<< number <<'\n';
    //                 ifile.close();
    //                 }
    //                 }
    //             else{
    //                 throw(-1);
    //                 }
    //         }
    //             catch(const std::exception& e){
    //                 std::cout<<"Cannot open the file.";
    //                 }
    //         }
    //     else{
    //         throw (-1);
    //     }
    //     }
    //     catch(const std::exception& e){
    //         std::cout<<"File doesn't exist";
    //         }


    // Renderer Init
    Renderer renderer;
    renderer.initialize();

    // InputManager Init
    InputManager input;
    input.start_fetching_thread();

    // Game Init
    Board board(30, 8);
    Game game(board, State());
    game.init_game(&input);

    // Timer Init
    auto timer_lambda = [](State* state) {
        while (!state->is_finished()) {
            unsigned int delta = state->get_speed() * 1000;
            std::this_thread::sleep_for(std::chrono::milliseconds(delta));
            state->set_should_move(true);
        }
    };
    std::thread timer_thread(timer_lambda, &game.get_state());
    timer_thread.detach();

    // Game Loop
    while (!(game.get_state().is_finished())) {
        game.update(&input);
        game.render(renderer);
    }
    
    // End Game
    input.stop_fetching_thread();
    renderer.clear_screen();
    renderer.refresh_screen();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    renderer.terminate();
}