#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <boost/json.hpp>

class AnimObject {
protected:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	double current_frame_time = 0, animation_speed = 0;
	size_t current_frame = 0;
	sf::Vector2i direction;

	std::string current_animation;
	boost::json::value value;
	boost::json::object sprite_config;
public:
	std::map<std::string, std::vector<sf::IntRect>> frames;
	AnimObject(std::string path_to_sprite, std::string path_to_config, std::string current_animation, double animation_speed);
	auto play_animation(double delta_time) -> void;
};