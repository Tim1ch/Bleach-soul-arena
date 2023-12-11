#pragma once
#include "state_machine.hpp"
#include "menu.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>

class LogoState : public State {
private:
	sf::Image ibackground;
	sf::Texture tbackground;
	sf::Sprite sbackground;
	std::vector <sf::Sprite> sprite_content;
	std::chrono::duration<double> time_for_end;
public:
	auto init() -> void override;
	auto control(double delta_time, sf::Event& event) -> void override;
	auto handle(StateMachine &state_machine, double delta_time) -> void override;
	auto draw_content(sf::RenderWindow &window) -> void override;
};

class DisclaimerState : public State {
private:
	sf::Image ibackground;
	sf::Texture tbackground;
	sf::Sprite sbackground;
	std::vector <sf::Sprite> sprite_content;
	std::chrono::duration<double> time_for_end;
public:
	auto init() -> void override;
	auto control(double delta_time, sf::Event& event) -> void override;
	auto handle(StateMachine& state_machine, double delta_time) -> void override;
	auto draw_content(sf::RenderWindow& window) -> void override;
};