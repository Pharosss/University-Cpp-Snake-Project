#pragma once
#include <vector>
#include <thread>
#include <memory>
#include <mutex>

enum KeyCode : char;
class InputObserver;

std::string to_string(KeyCode c);

class InputManager { 
    
    std::vector<int> input_buffer;
    KeyCode current_input;
    
    std::mutex buffer_mutex;
    bool should_run;

    std::shared_ptr<std::thread> fetch;
    std::shared_ptr<std::thread> process;

    std::vector<InputObserver*> observers;

    void notify_observers(KeyCode code);
    void erase_codes(unsigned int n);

public:
    InputManager();
    ~InputManager();

    void start_fetch_thread();
    void start_process_thread();

    void stop_threads();

    void add_observer(InputObserver* obs);
    void remove_observer(InputObserver* obs);

    KeyCode get_input();
};