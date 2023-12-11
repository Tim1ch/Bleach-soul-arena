#include "engine.hpp"
#include <string>
#include <fstream>
#include <iostream>

Engine * Engine::engine_instance = nullptr;

Engine * Engine::create_instance() {
    if (engine_instance == nullptr) {
        return new Engine();
    }

    return engine_instance;
}


void Engine::load_config() {
    CRegKey register_key;
    LPCTSTR register_path = L"Software\\Bleach-soul-arena";
    register_key.Create(HKEY_CURRENT_USER, register_path);
    DWORD register_reader;
    if (register_key.QueryDWORDValue(L"ResolutionX", register_reader) != ERROR_SUCCESS) {
        register_key.SetDWORDValue(L"ResolutionX", 1280);
        this->window_width = 1280;
        register_key.SetDWORDValue(L"ResolutionY", 720);
        this->window_height = 720;
        register_key.SetDWORDValue(L"Fullscreen", 0);
        this->is_fullscreen_mode = false;
    } else {
        this->window_width = register_reader;
        register_key.QueryDWORDValue(L"ResolutionY", register_reader);
        this->window_height = register_reader;
        register_key.QueryDWORDValue(L"Fullscreen", register_reader);
        this->is_fullscreen_mode = register_reader;
    }
    register_key.Close();
}

Engine::Engine() {
    this->load_config();

    this->state_machine = new StateMachine(this->window, this->view, this->event);
    this->state_machine->insert_state("logo", new LogoState());
    this->state_machine->insert_state("disclaimer", new DisclaimerState());
    this->state_machine->insert_state("menu", new MenuState());
    this->state_machine->insert_state("game", new GameState());
    this->state_machine->switch_state("game");

    if (this->is_fullscreen_mode) {
        this->window.create(sf::VideoMode(this->window_width, this->window_height), "Bleach soul arena", sf::Style::Fullscreen);
    } else {
        this->window.create(sf::VideoMode(this->window_width, this->window_height), "Bleach soul arena", sf::Style::Close | sf::Style::Titlebar);
    }
    this->view.reset(sf::FloatRect(0, 0, 1920, 1080));
    this->previous_time = std::chrono::high_resolution_clock::now();
}

void Engine::game_loop() {
    while (this->window.isOpen()) {
        while (this->window.pollEvent(this->event)) {
            if (this->event.type == sf::Event::Closed) {
                this->window.close();
            }
            this->state_machine->control(delta_time.count(), this->event);
        }
        this->current_time = std::chrono::high_resolution_clock::now();
        this->delta_time = this->current_time - this->previous_time;
        this->previous_time = this->current_time;

        this->window.setView(this->view);
        this->window.clear();
        this->state_machine->update(this->delta_time.count());
        this->window.display();
    }
}