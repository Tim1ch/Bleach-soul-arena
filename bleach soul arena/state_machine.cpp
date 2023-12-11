#include "state_machine.hpp"

auto StateMachine::insert_state(std::string state_name, State *state) -> void {
	this->states.insert(std::pair<std::string, State*>(state_name, state));
}

StateMachine::StateMachine(sf::RenderWindow &window, sf::View &view, sf::Event &event) {
	this->window = &window;
	this->view = &view;
	this->event = &event;
}

auto StateMachine::switch_state(std::string state_name) -> void {
	this->current_state = this->states[state_name];
	this->current_state->init();
}
auto StateMachine::control(double delta_time, sf::Event &event) -> void {
	this->current_state->control(delta_time, event);
}
auto StateMachine::update(double delta_time) -> void {
	this->current_state->handle(*this, delta_time);
	this->current_state->draw_content(*window);
}