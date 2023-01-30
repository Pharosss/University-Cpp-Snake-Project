#include <chrono>
#include <iostream>

#include "game/Game.h"

#include "io/Renderer.h"
#include "io/InputManager.h"
#include "io/CLIReader.h"
#include "io/FileIO.h"

#define DEFAULT_WIDTH 50
#define DEFAULT_HEIGHT 10
#define DEFAULT_SPEED 0.15f


void renderer_demo() {
    Renderer r;
    r.initialize();

    r.write("Hello Ncurses!");
    r.write(" Screen dimensions: ");
    std::string dims = std::to_string(r.get_viewport_width()) + " x " + std::to_string(r.get_viewport_height());
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

    std::string highscore_path = std::getenv("HOME") + std::string("/.terminal_snake");

    // Read CLI arguments
    CLIReader cli(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_SPEED, highscore_path);
    cli.analyse_arguments(argc, argv);
    if (!cli.game_should_start())
        return 0;

    // Renderer Init
    Renderer renderer;
    renderer.initialize();

    // Viewport Size check
    while(cli.get_board_w() + 3 > renderer.get_viewport_width() ||
          cli.get_board_h() + 4 > renderer.get_viewport_height()) {
        renderer.terminate();
        std::cout<<"Error! Game board is too big. Please resize the board or the viewport!\n";
        return 0;
    }

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
            unsigned delta = state->get_speed() * 1000;
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

    // Highscore Management
    int old_hs = Files::load_highscore(highscore_path);
    int new_hs = game.get_state().get_score();

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