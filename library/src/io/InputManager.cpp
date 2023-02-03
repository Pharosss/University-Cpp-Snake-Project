#include <map>
#include <stdexcept>

#include "io/InputManager.h"
#include "io/Input.h"

void InputManager::notify_observers(ActionCode code) {
    for (auto obs : observers)
        obs->on_action(code);
}

InputManager::InputManager()
    : input_fetching_thread(nullptr), should_run(true), current_input(A_NULL) {}

// W = 119 87 A_UP
// S = 115 83 A_DOWN
// A = 97  65 A_LEFT
// D = 100 68 A_RIGHT
// Tab = 9    A_RETURN
// Space = 32 A_PAUSE

// THREADS

void InputManager::start_fetching_thread() {
    auto fetch_lambda = [](InputManager* i) {
        while(i->should_run) {
            int ch = getchar();
            switch (ch) {
                case 9:
                    i->current_input = A_RETURN;
                    break;
                case 32:
                    i->current_input = A_PAUSE;
                    break;
                case 119:
                case 87:
                    i->current_input = A_UP;
                    break;
                case 115:
                case 83:
                    i->current_input = A_DOWN;
                    break;
                case 97:
                case 65:
                    i->current_input = A_LEFT;
                    break;
                case 100:
                case 68:
                    i->current_input = A_RIGHT;
                    break;
                default:
                    i->current_input = A_NULL;
                    break;
            }

            if (i->current_input != A_NULL)
                i->notify_observers(i->current_input);
        }
    };

    input_fetching_thread = std::make_shared<std::thread>(fetch_lambda, this);
    input_fetching_thread->detach();
}

void InputManager::stop_fetching_thread() {
    should_run = false;
}

// OBSERVERS

void InputManager::add_observer(InputObserver* obs) {
    observers.push_back(obs);
}

void InputManager::remove_observer(InputObserver* obs) {
    for (size_t i = 0; i < observers.size(); i++)
        if (observers[i] == obs)
            observers.erase(observers.begin() + i--);
}