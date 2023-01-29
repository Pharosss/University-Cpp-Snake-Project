#include <map>
#include <stdexcept>

#include "InputManager.h"
#include "Input.h"

void InputManager::notify_observers(KeyCode code) {
    for (auto obs : observers)
        obs->on_keepress(code);
}

InputManager::InputManager()
    : input_fetching_thread(nullptr), should_run(true), current_input(K_NULL) {}

// W = 119 87 K_UP
// S = 115 83 K_DOWN
// A = 97 65 K_LEFT
// D = 100 68 K_RIGHT

// Tab = 9
// Enter = 13

// THREADS

void InputManager::start_fetching_thread() {
    auto fetch_lambda = [](InputManager* i) {
        while(i->should_run) {
            int ch = getchar();
            switch (ch) {
                case 9:
                    i->current_input = K_RETURN;
                    break;
                case 13:
                    i->current_input = K_ENTER;
                    break;
                case 119:
                case 87:
                    i->current_input = K_UP;
                    break;
                case 115:
                case 83:
                    i->current_input = K_DOWN;
                    break;
                case 97:
                case 65:
                    i->current_input = K_LEFT;
                    break;
                case 100:
                case 68:
                    i->current_input = K_RIGHT;
                    break;
                default:
                    i->current_input = K_NULL;
                    break;
            }

            if (i->current_input != K_NULL)
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