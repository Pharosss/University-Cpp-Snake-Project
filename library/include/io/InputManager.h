#pragma once
#include <vector>
#include <thread>
#include <memory>

enum KeyCode : char;
class InputObserver;

class InputManager {
    bool should_run;
    KeyCode current_input;

    std::shared_ptr<std::thread> input_fetching_thread;

    std::vector<InputObserver*> observers;
    void notify_observers(KeyCode code);

public:
    InputManager();

    void start_fetching_thread();
    void stop_fetching_thread();

    void add_observer(InputObserver* obs);
    void remove_observer(InputObserver* obs);

    KeyCode get_input();
};