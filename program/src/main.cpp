#include <thread>
#include "Game.h"
#include "Renderer.h"
#include <ncurses.h>

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

auto game_loop_f = [](Game* g, Renderer* r){
    while (!(g->get_state().is_finished())) {
        g->render(*r);
    }
};

auto input_f = [](State* s){
    while(!(s->is_finished())) {
        int ch = getch();

        if (ch == KEY_UP)
            s->finish_game();
        if (ch == KEY_DOWN)
            s->increment_score();
    }
};

int main() {
    Board b(30, 8);
    Game g(b, State());
    g.init_game();

    Renderer r;
    r.initialize();

    std::thread game_loop_thread(game_loop_f, &g, &r);
    std::thread input_thread(input_f, &(g.get_state()));

    game_loop_thread.detach();
    input_thread.join();

    r.terminate();
}