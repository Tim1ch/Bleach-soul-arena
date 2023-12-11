#pragma once
#include "state_machine.hpp"

enum MenuPages : int {
	MAIN_PAGE	  = 0,
	RESTART_PAGE  = 1,
	SAVES_PAGE    = 2,
	OPTIONS_PAGE  = 3,
	ABOUT_US_PAGE = 4
};

enum Buttons : int {
	CONTINUE_BUTTON = 0,
	RESTART_BUTTON  = 1,
	SAVES_BUTTON    = 2,
	OPTIONS_BUTTON  = 3,
	ABOUT_US_BUTTON = 4,
	EXIT_BUTTON     = 5,
	BACK_BUTTON     = 6,
};

class Button;

class MenuState : public State {
private:
	bool view_animation = false;
	sf::Vector2f view_end_point;

	sf::Image ibackground, isaves;
	sf::Texture tbackground, tsaves;
	sf::Sprite sbackground, ssaves;
	
	sf::Font menu_font;

	std::vector <Button> buttons;

	std::string restart_game_text_string = "ARE YOU WANT TO BEGIN AGAIN?";
	sf::Text restart_game_text;

	std::string about_us_text_string = "MAIN DEVELOPER - TIMUR";
	sf::Text about_us_text;

	std::string options_text_string = "EMPTY NOW";
	sf::Text options_text;

public:
	auto init() -> void override;
	auto change_page(MenuPages page, sf::View& view) -> void;
	auto control(double delta_time, sf::Event& event) -> void override;
	auto handle(StateMachine &state_machine, double delta_time) -> void override;
	auto draw_content(sf::RenderWindow &window) -> void override;
};

class Button {
private:
	sf::Text text;
public:
	int type;
	Button(int type, std::string str, sf::Font& font, int xpos, int ypos);
	sf::Text get_text();
	auto click_on(sf::Event &event, sf::RenderWindow& window) -> bool;
	auto contains(sf::Event &event, sf::RenderWindow& window) -> bool;
	auto set_text_color(sf::Color color) -> void;

};