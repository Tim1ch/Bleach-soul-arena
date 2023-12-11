#include "animation.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

AnimObject::AnimObject(std::string path_to_sprite, std::string path_to_config, std::string current_animation, double animation_speed) {
	this->current_animation = current_animation;
	this->animation_speed = animation_speed;
	
	this->image.loadFromFile(path_to_sprite);
	this->image.createMaskFromColor(sf::Color(0, 128, 0));
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);

	std::ifstream input(path_to_config);

	if (input.is_open()) {
		value = boost::json::parse(input);
		input.close();
		if (value.is_object()) {
			sprite_config = value.as_object();
		}
	}
	for (auto sprite_config_iter = sprite_config.begin(); sprite_config_iter != sprite_config.end(); ++sprite_config_iter) {
		const std::string& animation_name = sprite_config_iter->key();
		std::string animation_name_string = std::string(animation_name.c_str());
		std::vector<sf::IntRect> animation_frames;
		for (auto animation_iter = sprite_config_iter->value().as_array().begin(); animation_iter != sprite_config_iter->value().as_array().end(); animation_iter++) {
			animation_frames.push_back(sf::IntRect(animation_iter->as_array()[0].as_int64(), animation_iter->as_array()[1].as_int64(), animation_iter->as_array()[2].as_int64(), animation_iter->as_array()[3].as_int64()));
		}
		this->frames[animation_name_string] = animation_frames;
	}
}

auto AnimObject::play_animation(double delta_time) -> void {
	this->current_frame_time += delta_time;
	if (this->current_frame_time > this->frames[this->current_animation].size() * this->animation_speed) {
		this->current_frame_time = 0;
		this->current_frame = 0;
	}
	this->current_frame = (int)(current_frame_time / animation_speed);

	if (this->direction.x) {
		this->sprite.setTextureRect(this->frames[this->current_animation][this->current_frame]);
	} else {
		sf::IntRect mirrored_rect(this->frames[this->current_animation][this->current_frame]);
		mirrored_rect.left += mirrored_rect.width;
		mirrored_rect.width *= -1;
		this->sprite.setTextureRect(mirrored_rect);
	}
	this->sprite.setOrigin(this->frames[this->current_animation][this->current_frame].width / 2, this->frames[this->current_animation][this->current_frame].height / 2);
}