#pragma once
#include <vector>
#include <thread>
#include <memory>

enum KeyCode : char;
class InputObserver;

class InputManager { 
    bool should_run;
    
    std::vector<int> input_buffer;
    KeyCode current_input;

    std::shared_ptr<std::thread> input_fetching_thread;
    std::shared_ptr<std::thread> input_processing_thread;

    std::vector<InputObserver*> observers;
    
    void notify_observers(KeyCode code);
    
    void erase_codes(unsigned int n);

public:
    InputManager();

    void start_fetch_thread();
    void start_process_thread();

    void stop_threads();

    void add_observer(InputObserver* obs);
    void remove_observer(InputObserver* obs);

    KeyCode get_input();
};