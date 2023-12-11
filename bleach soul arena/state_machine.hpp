#pragma once
#include <SFML/Graphics.hpp>
#include <map>
class StateMachine;

class State {
public:
	virtual auto init() -> void = 0;
	virtual auto handle(StateMachine &state_machine, double delta_time) -> void = 0;
	virtual auto control(double delta_time, sf::Event &event) -> void = 0;
	virtual auto draw_content(sf::RenderWindow &window) -> void = 0;
};

class StateMachine {
public:
	StateMachine(sf::RenderWindow &window, sf::View &view, sf::Event &event);
	std::map <std::string, State*> states;
	sf::Event *event;
	sf::RenderWindow *window;
	sf::View *view;
	State* current_state;
	auto insert_state(std::string state_name, State *state) -> void;
	auto switch_state(std::string state_name) -> void;
	auto control(double delta_time, sf::Event &event) -> void;
	auto update(double delta_time) -> void;
};