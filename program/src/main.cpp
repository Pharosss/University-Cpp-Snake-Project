#include <chrono>
#include "Game.h"

#include "Renderer.h"
#include "InputManager.h"
#include "CLIReader.h"

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

    CLIReader cli;
    cli.analyse_arguments(argc, argv);
    if (!cli.game_should_start())
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
    Board board(cli.get_board_w(), cli.get_board_h());
    Game game(board, State());
    game.get_state().set_speed(cli.get_speed_seconds());
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