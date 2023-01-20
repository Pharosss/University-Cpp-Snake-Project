#pragma once

enum KeyCode : char {
    K_NULL, K_UP, K_DOWN, K_RIGHT, K_LEFT, K_ENTER, K_ESCAPE
};

class InputObserver {
public:
    virtual void on_keepress(KeyCode code) {};
};