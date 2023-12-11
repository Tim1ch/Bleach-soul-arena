#pragma once
#include "SFML/Graphics.hpp"
#include <boost/json.hpp>
#include "state_machine.hpp"
#include "logo.hpp"
#include "menu.hpp"
#include "game.hpp"
#include <chrono>

#define _AFXDLL
#include <afxwin.h>

class Engine {
private:
    static Engine* engine_instance;
    Engine();
    void load_config();

    uint32_t window_width, window_height;
    bool is_fullscreen_mode;

    std::chrono::high_resolution_clock::time_point previous_time, current_time;
    std::chrono::duration<double> delta_time;

    sf::RenderWindow window;
    sf::View view;
    sf::Event event;

    StateMachine *state_machine;
public:
    static Engine* create_instance();
    void game_loop();
};