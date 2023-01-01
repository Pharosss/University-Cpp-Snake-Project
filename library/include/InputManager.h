#pragma once
#include <vector>
#include <thread>
#include <memory>
#include <mutex>

enum KeyCode {
    K_NULL, K_UP, K_DOWN, K_RIGHT, K_LEFT, K_ENTER, K_ESCAPE
};

std::string to_string(KeyCode c);

class InputManager { 
    std::vector<int> input_buffer;
    KeyCode current_input;

    std::mutex buffer_mutex;
    bool should_run;

    std::shared_ptr<std::thread> fetch;
    std::shared_ptr<std::thread> process;

    //std::map<KeyCode, std::vector<std::lambda>> callbacks;

    void erase_codes(unsigned int n);

public:
    InputManager();
    ~InputManager();

    void start_fetch_thread();
    void start_process_thread();

    void stop_threads();

    void add_callback(KeyCode code);

    KeyCode get_input();
};