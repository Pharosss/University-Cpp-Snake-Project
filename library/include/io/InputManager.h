#pragma once
#include <vector>
#include <thread>
#include <memory>

enum ActionCode : char;
class InputObserver;

class InputManager {
    bool should_run;
    ActionCode current_input;

    std::shared_ptr<std::thread> input_fetching_thread;

    std::vector<InputObserver*> observers;
    void notify_observers(ActionCode code);

public:
    InputManager();

    void start_fetching_thread();
    void stop_fetching_thread();

    void add_observer(InputObserver* obs);
    void remove_observer(InputObserver* obs);
};
