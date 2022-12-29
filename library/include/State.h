#pragma once

class State {
    unsigned int score;
    float speed_seconds;

    bool m_is_finished;   // is the game over?
    bool m_is_paused;
    bool m_should_move;   // is automatically set to true every 1 second. After the move it resets

    int input;

public:
    State();

    float get_speed();
    float set_speed(float seconds);

    int get_score();
    void increment_score();

    bool is_finished();
    void finish_game();

    bool is_paused();
    void set_pause(bool paused);

    bool should_move();
    void set_should_move(bool should);

    int get_input();
    void set_input(int in);
};