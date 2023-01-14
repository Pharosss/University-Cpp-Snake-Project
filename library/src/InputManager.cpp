#include <map>
#include <stdexcept>

#include "InputManager.h"
#include "Input.h"

std::map<KeyCode, std::string> string_map = {
    {K_NULL,    "Null"},
    {K_UP,      "Up"},
    {K_DOWN,    "Down"},
    {K_RIGHT,   "Right"},
    {K_LEFT,    "Left"},
    {K_ENTER,   "Enter"},
    {K_ESCAPE,  "Escape"}
};

std::string to_string(KeyCode c) {
    try {
        return string_map.at(c);
    } catch (std::out_of_range e) {
        return string_map.at(K_NULL);
    }
}

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
    : fetch(nullptr), process(nullptr), should_run(true), current_input(K_NULL) {}

    InputManager::~InputManager() {
    while(!buffer_mutex.try_lock());
    buffer_mutex.unlock();
}

void InputManager::start_fetch_thread() {
    auto fetch_lambda = [](InputManager* i) {
        while(i->should_run) {
            int ch = getchar();
            while(!i->buffer_mutex.try_lock());
            i->input_buffer.push_back(ch);
            i->buffer_mutex.unlock();
        }
    };

    fetch = std::make_shared<std::thread>(fetch_lambda, this);
    fetch->detach();
}
 
void InputManager::start_process_thread() {
    auto process_lambda = [](InputManager* i) {
        while (i->should_run) {
            if (i->current_input != K_NULL)
                i->notify_observers(i->current_input);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10));

            while (!i->buffer_mutex.try_lock());
            int size = i->input_buffer.size();
            i->buffer_mutex.unlock();
            
            if (size == 0) {
                i->current_input = K_NULL;
                continue;
            }

            // try to process multiple codes
            bool is_multiple = false;

            while(!i->buffer_mutex.try_lock());

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
            i->buffer_mutex.unlock();

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

    process = std::make_shared<std::thread>(process_lambda, this);
    process->detach();
}

void InputManager::add_observer(InputObserver* obs) {
    observers.push_back(obs);
}

void InputManager::remove_observer(InputObserver* obs) {
    for (size_t i = 0; i < observers.size(); i++)
        if (observers[i] == obs)
            observers.erase(observers.begin() + i--);
}

void InputManager::stop_threads() {
    should_run = false;
}

KeyCode InputManager::get_input() {
    return current_input;
}