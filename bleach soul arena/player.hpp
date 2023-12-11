#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>

class Player : public Entity {
public:
	Player(std::string path_to_sprite, std::string path_to_config);
	auto control(double delta_time, sf::Event& event) -> void;
	auto update(double delta_time, sf::Event& event) -> void override;
};
