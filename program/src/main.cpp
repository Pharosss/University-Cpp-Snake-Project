#include <thread>
#include "Game.h"
#include "Renderer.h"

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
    Board b(30, 8);
    Game g(b, State());
    g.init_game();

    auto moo = [](Game* g){
        while (!(g->get_state().is_finished())) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            g->get_state().increment_score();
            if(g->get_state().get_score() == 1000)
                g->get_state().finish_game();
        }
    };
    std::thread score_thread(moo, &g);
    score_thread.detach();

    Renderer r;
    r.initialize();
    while(!(g.get_state().is_finished())) {
        g.render(r);
    }

    r.terminate();
}