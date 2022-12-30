#include <thread>
#include <chrono>
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

std::vector<int> input_buffer;

auto game_loop_f = [](Game* g, Renderer* r){
    while (!(g->get_state().is_finished())) {
        g->render(*r);
    }
};

auto input_fetch_f = [](State* s) {
    while(!(s->is_finished())) {
        int ch = getchar();
        input_buffer.push_back(ch);
    }
};

auto input_process_f = [](State* s) {
    while(!(s->is_finished())) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::string str;
        for (int i = 0; i < input_buffer.size() && i < 3; i++)
            str += std::to_string(input_buffer[i]) + " ";
 
        if (str == "27 79 65 ") {
            str = "UP";
            s->increment_score();
        }
        else if (str == "27 79 66 ") {
            str = "DOWN";
            s->finish_game();
        }
        else if (str == "27 79 67 ") {
            str = "RIGHT";
        }      
        else if (str == "27 79 68 ") {
            str = "LEFT";
        }
        else if (str == "27 ") {
            str = "ESCAPE";
        }

        s->set_input(str);
        input_buffer.clear();
    }
};

int main() {
    Board b(30, 8);
    Game g(b, State());
    g.init_game();

    Renderer r;
    r.initialize();

    std::thread game_loop_thread(game_loop_f, &g, &r);
    std::thread input_fetch_thread(input_fetch_f, &(g.get_state()));
    std::thread input_process_thread(input_process_f, &(g.get_state()));

    game_loop_thread.detach();
    input_fetch_thread.detach();
    input_process_thread.detach();

    while (!(g.get_state().is_finished()));
    
    r.clear_screen();
    r.refresh_screen();

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    r.terminate();
}