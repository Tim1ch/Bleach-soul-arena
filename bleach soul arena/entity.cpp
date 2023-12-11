#include "entity.hpp"

Entity::Entity(std::string path_to_sprite, std::string path_to_config, double speed) : AnimObject(path_to_sprite, path_to_config, "stay", 0.15) {
	this->speed = speed;
	this->freeze_time = 0.0;
}

auto Entity::update(double delta_time, sf::Event &event) -> void {

}

auto Entity::draw(sf::RenderWindow& window) -> void {
	window.draw(this->sprite);
}