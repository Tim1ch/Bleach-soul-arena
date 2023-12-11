#include "player.hpp"
#include <iostream>

Player::Player(std::string path_to_sprite, std::string path_to_config) : Entity(path_to_sprite, path_to_config, 500) {
	this->sprite.setTextureRect(sf::IntRect(12, 888, 83, 108));
	this->sprite.setPosition(300, 850);
	this->sprite.setScale(2.8, 2.8);
	this->sprite.setColor(sf::Color(255, 255, 255, 210));
}

auto Player::control(double delta_time, sf::Event& event) -> void {
	if (this->teleport_cooldown < 0.1) {
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift) {
			this->current_animation = "teleport";
			this->teleport_cooldown = this->animation_speed * (this->frames["teleport"].size()) * 1.5;
			this->freeze_time = this->animation_speed * this->frames["teleport"].size();
			this->is_teleporting = true;
		}
	}
}

auto Player::update(double delta_time, sf::Event& event) -> void {
	if (this->freeze_time < 0.3) {
		this->current_animation = "stance";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->sprite.move(this->speed * delta_time, 0);
			this->current_animation = "walk";
			this->direction.x = 1;
			this->last_axis = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->sprite.move(-this->speed * delta_time, 0);
			this->current_animation = "walk";
			this->direction.x = 0;
			this->last_axis = 0;
		}
		this->sprite.setColor(sf::Color(255, 255, 255, 220));
		this->play_animation(delta_time);
	}
	else {
		if (this->is_teleporting) {
			this->current_frame = 2;
			this->play_animation(delta_time);
			if (direction.x) {
				this->current_frame = 2;
				this->sprite.setPosition(this->sprite.getPosition().x + 500, this->sprite.getPosition().y);
			}
			else {
				this->sprite.setPosition(this->sprite.getPosition().x - 500, this->sprite.getPosition().y);
			}
			this->is_teleporting = false;
			this->sprite.setColor(sf::Color(255, 255, 255, 100));
		}
	}
	this->sprite.setOrigin(this->frames[this->current_animation][this->current_frame].width / 2, this->frames[this->current_animation][this->current_frame].height / 2);
	this->freeze_time -= delta_time;
	this->teleport_cooldown -= delta_time;
}