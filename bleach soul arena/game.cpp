#include "game.hpp"
#include <iostream>

auto GameState::init() -> void {
	this->player = new Player("../resources/characters/ichigo/sprite_list.png", "../resources/characters/ichigo/config.json");
	this->ibackground.loadFromFile("../resources/events/urahara_shoten.png");
	this->tbackground.loadFromImage(this->ibackground);
	this->sbackground.setTexture(this->tbackground);
	this->sbackground.setColor(sf::Color(250, 250, 250));
}

auto GameState::control(double delta_time, sf::Event& event) -> void {
	this->player->control(delta_time, event);
}

auto GameState::handle(StateMachine& state_machine, double delta_time) -> void {
	this->player->update(delta_time, *state_machine.event);
}

auto GameState::draw_content(sf::RenderWindow& window) -> void {
	window.draw(this->sbackground);
	this->player->draw(window);
};
