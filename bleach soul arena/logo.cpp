#include "logo.hpp"
#include <iostream>


auto LogoState::init() -> void {
	this->time_for_end = std::chrono::duration<double>(3.0);

	this->ibackground.loadFromFile("../resources/logo/logo.png");
	this->tbackground.loadFromImage(this->ibackground);
	this->sbackground.setTexture(this->tbackground);
}

auto LogoState::control(double delta_time, sf::Event& event) -> void {

}

auto LogoState::handle(StateMachine &state_machine, double delta_time) -> void {
	this->time_for_end -= std::chrono::duration<double>(delta_time);
	if (this->time_for_end.count() < 0 || (state_machine.event->type == sf::Event::KeyReleased && state_machine.event->key.code == sf::Keyboard::Enter)) {
		state_machine.switch_state("disclaimer");
	}
}

auto LogoState::draw_content(sf::RenderWindow &window) -> void {
	window.draw(this->sbackground);
};

auto DisclaimerState::init() -> void {
	this->time_for_end = std::chrono::duration<double>(3.0);
	this->ibackground.loadFromFile("../resources/logo/disclaimer.png");
	this->tbackground.loadFromImage(this->ibackground);
	this->sbackground.setTexture(this->tbackground);

}

auto DisclaimerState::control(double delta_time, sf::Event& event) -> void {

}


auto DisclaimerState::handle(StateMachine& state_machine, double delta_time) -> void {
	this->time_for_end -= std::chrono::duration<double>(delta_time);
	if (this->time_for_end.count() < 0) {
		state_machine.switch_state("menu");
	}
}

auto DisclaimerState::draw_content(sf::RenderWindow& window) -> void {
	window.draw(this->sbackground);
};