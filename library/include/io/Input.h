#pragma once

class InputManager;

enum ActionCode : char {
    A_NULL, A_UP, A_DOWN, A_LEFT, A_RIGHT, A_RETURN, A_PAUSE
};

class InputObserver {
    friend class InputManager;

    virtual void on_action(ActionCode code) {};
};
