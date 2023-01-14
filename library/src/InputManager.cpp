#include <map>
#include <stdexcept>

#include "InputManager.h"
#include "Input.h"

void InputManager::notify_observers(KeyCode code) {
    for (auto obs : observers)
        obs->on_keepress(code);
}

void InputManager::erase_codes(unsigned int n) {
    while (n > 0) {
        input_buffer.erase(input_buffer.begin());
        n--;
    }
}

InputManager::InputManager()
    : input_fetching_thread(nullptr), input_processing_thread(nullptr), should_run(true), current_input(K_NULL) {}

// THREADS

void InputManager::start_fetch_thread() {
    auto fetch_lambda = [](InputManager* i) {
        while(i->should_run) {
            int ch = getchar();
            i->input_buffer.push_back(ch);
        }
    };

    input_fetching_thread = std::make_shared<std::thread>(fetch_lambda, this);
    input_fetching_thread->detach();
}
 
void InputManager::start_process_thread() {
    auto process_lambda = [](InputManager* i) {
        while (i->should_run) {
            if (i->current_input != K_NULL)
                i->notify_observers(i->current_input);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            int size = i->input_buffer.size();
            if (size == 0) {
                i->current_input = K_NULL;
                continue;
            }

            // try to process multiple codes
            bool is_multiple = false;
            if (size >= 3 || i->input_buffer[0] == 27 || i->input_buffer[1] == 91) {
                is_multiple = true;
                switch (i->input_buffer[2]) {
                    case 65:
                        i->current_input = K_UP;
                        break;
                    case 66:
                        i->current_input = K_DOWN;
                        break;
                    case 67:
                        i->current_input = K_RIGHT;
                        break;
                    case 68:
                        i->current_input = K_LEFT;
                        break;
                    default: {
                        i->current_input = K_NULL;
                        is_multiple = false;
                        break;
                    }
                }
            }

            if (!is_multiple) { // process one code
                switch (i->input_buffer[0]) {
                    case 27:
                        i->current_input = K_ESCAPE;
                        break;
                    default:
                        i->current_input = K_NULL;
                        break;
                }
                i->erase_codes(1);
                continue;
            }

            i->erase_codes(3);
        } 
    };

    input_processing_thread = std::make_shared<std::thread>(process_lambda, this);
    input_processing_thread->detach();
}

void InputManager::stop_threads() {
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