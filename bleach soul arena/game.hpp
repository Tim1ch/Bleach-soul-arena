#pragma once
#include "state_machine.hpp"
#include "player.hpp"

class GameState : public State {
private:
	Player *player;
	sf::Image ibackground;
	sf::Texture tbackground;
	sf::Sprite sbackground;
public:
	
	auto init() -> void override;
	auto control(double delta_time, sf::Event& event) -> void override;
	auto handle(StateMachine& state_machine, double delta_time) -> void override;
	auto draw_content(sf::RenderWindow &window) -> void override;
};
