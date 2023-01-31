#pragma once

class InputManager;

enum KeyCode : char {
    K_NULL, K_UP, K_DOWN, K_LEFT, K_RIGHT, K_RETURN
};

class InputObserver {
    friend class InputManager;

    virtual void on_keepress(KeyCode code) {};
};
