#include <chrono>
#include <iostream>

#include "core/Game.h"

#include "io/Renderer.h"
#include "io/InputManager.h"
#include "io/CLIReader.h"
#include "io/FileIO.h"

#define DEFAULT_SIZE uvec2(50, 10)
#define DEFAULT_SPEED 0.15f

int main(int argc, char *argv[]) {

    std::string highscore_path = std::getenv("HOME") + std::string("/.terminal_snake");

    // Read CLI arguments
    CLIReader cli(DEFAULT_SIZE, DEFAULT_SPEED, highscore_path);
    cli.analyse_arguments(argc, argv);
    if (!cli.game_should_start())
        return 0;

    // Renderer Init
    Renderer renderer;
    renderer.initialize();

    // Viewport Size check
    uvec2 board_s = cli.get_board_size();
    if(board_s + uvec2(3,4) > renderer.get_viewport_size()) {
        renderer.terminate();
        std::cout<<"Error! Game board is too big. Please choose a smaller size.\n";
        return 0;
    }

    if(board_s.x < 9 || board_s.y < 3) {
        renderer.terminate();
        std::cout<<"Error! Game board is too small. Please choose a bigger size.\n";
        return 0;
    }

    // InputManager Init
    InputManager input;
    input.start_fetching_thread();

    // Game Init
    Board board(cli.get_board_size());
    Game game(board, State());
    game.get_state().set_speed(cli.get_speed_seconds());
    game.init_game(&input);

    // Timer Init
    auto timer_lambda = [](State* state) {
        while (!state->get_flag(IS_FINISHED)) {
            if (state->get_flag(PAUSED))
                continue;
            
            unsigned delta = state->get_speed() * 1000;
            std::this_thread::sleep_for(std::chrono::milliseconds(delta));
            state->set_flag(SHOULD_MOVE, true);
        }
    };
    std::thread timer_thread(timer_lambda, &game.get_state());
    timer_thread.detach();

    // Game Loop
    while (!(game.get_state().get_flag(IS_FINISHED))) {
        game.update(&input);
        game.render(&renderer);
    }
    
    // End Game
    input.stop_fetching_thread();
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    renderer.terminate();

    // Highscore Management
    int old_hs = Files::load_highscore(highscore_path),
        new_hs = game.get_state().get_score();

    if (new_hs <= old_hs || new_hs == 0) {
        std::cout << "Your score was: " << new_hs << '\n';
        return 0;
    }

    if (old_hs == -1)
        std::cout<<"You have no previous highscore saved.\n";
    else {
        std::cout<<"Congratulations!\n"
        <<"You have beaten your previous highscore of: " << old_hs << '\n';
    }
    std::cout << "Your new highscore is: " << new_hs <<'\n'
    << "Do you want to save the highscore? Write [yes/no]\n";

    std::string resp;
    while (resp != "yes" && resp != "no")
        std::cin >> resp;

    if (resp == "no")
        return 0;

    if(Files::save_highscore(highscore_path, new_hs)) {
        std::cout<<"Error while writing the file!\n";
        return -1;
    }

    std::cout<<"Highscore has been saved\n";

    return 0;
}