#include <chrono>
#include "Game.h"

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

int main() {

    // Renderer Init
    Renderer renderer;
    renderer.initialize();

    // InputManager Init
    InputManager input;
    input.start_fetch_thread();
    input.start_process_thread();

    // Game Init
    Board board(30, 8);
    Game game(board, State());
    game.init_game();
    input.add_observer(&game);

    // Game Loop
    while (!(game.get_state().is_finished())) {
        game.update(input);
        game.render(renderer);
    }
    
    // End Game
    input.stop_threads();
    renderer.clear_screen();
    renderer.refresh_screen();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    renderer.terminate();
}