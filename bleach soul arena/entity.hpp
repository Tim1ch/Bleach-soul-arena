#pragma once
#include "animation.hpp"

class Entity : public AnimObject {
protected:
	int last_axis = 0;
	bool is_teleporting = false, is_jumping = false;
	double speed = 0.0;
	double teleport_cooldown = 0.0;
	double freeze_time;
public:
	Entity(std::string path_to_sprite, std::string path_to_config, double speed);
	auto draw(sf::RenderWindow& window) -> void;
	virtual auto update(double delta_time, sf::Event &event) -> void;
};