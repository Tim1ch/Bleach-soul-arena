#include "menu.hpp"
#include <iostream>

void MenuState::init() {
	this->ibackground.loadFromFile("../resources/gui/menu/background.png");
	this->tbackground.loadFromImage(this->ibackground);
	this->sbackground.setTexture(this->tbackground);
	this->sbackground.setOrigin(960, 540);
	this->sbackground.setPosition(960, 540);

	this->isaves.loadFromFile("../resources/gui/menu/saves.png");
	this->isaves.createMaskFromColor(sf::Color(0, 255, 0));
	this->tsaves.loadFromImage(this->isaves);
	this->ssaves.setTexture(this->tsaves);
	this->ssaves.setOrigin(960, 540);
	this->ssaves.setPosition(-960, 540);

	this->menu_font.loadFromFile("../resources/gui/fonts/bleach_font.ttf");

	this->buttons.push_back(*new Button(CONTINUE_BUTTON, "CONTINUE", menu_font, 100, 90));
	this->buttons.push_back(*new Button(RESTART_BUTTON,  "NEW GAME", menu_font,  100,   180));
	this->buttons.push_back(*new Button(SAVES_BUTTON,    "SAVES",    menu_font,  100,   270));
	this->buttons.push_back(*new Button(OPTIONS_BUTTON,  "OPTIONS",     menu_font,  100,   360));
	this->buttons.push_back(*new Button(ABOUT_US_BUTTON, "ABOUT US",    menu_font,  100,   450));
	this->buttons.push_back(*new Button(EXIT_BUTTON,     "EXIT",         menu_font,  100,   540));
	this->buttons.push_back(*new Button(BACK_BUTTON,     "BACK",         menu_font,  1620, -980));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 "BACK",		   menu_font, -300,   100));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 "BACK",		   menu_font,  3540,  100));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 "BACK",		   menu_font,  1620,  1180));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 "BACK",		   menu_font, -300, -980));
	this->buttons.push_back(*new Button(BACK_BUTTON,	 "BACK",		   menu_font, 3540, -980));
	
	this->about_us_text.setString(this->about_us_text_string);
	this->about_us_text.setCharacterSize(64);
	this->about_us_text.setFillColor(sf::Color(255, 255, 255));
	this->about_us_text.setFont(this->menu_font);
	this->about_us_text.setPosition(100, 1380);

	this->restart_game_text.setString(this->restart_game_text_string);
	this->restart_game_text.setCharacterSize(64);
	this->restart_game_text.setFillColor(sf::Color(255, 255, 255));
	this->restart_game_text.setFont(this->menu_font);
	this->restart_game_text.setPosition(175, -840);

	this->options_text.setString(this->options_text_string);
	this->options_text.setCharacterSize(100);
	this->options_text.setFillColor(sf::Color(255, 255, 255));
	this->options_text.setFont(this->menu_font);
	this->options_text.setPosition(2550, 420);

}

auto MenuState::control(double delta_time, sf::Event& event) -> void {

}

void MenuState::change_page(MenuPages page, sf::View& view) {
	sf::Vector2i end_view_pos(0, 0);
	switch (page) {
	case RESTART_PAGE:
		end_view_pos.x = 960;
		end_view_pos.y = -540;
		break;
	case SAVES_PAGE:
		end_view_pos.x = -960;
		end_view_pos.y = 540;
		break;
	case OPTIONS_PAGE:
		end_view_pos.x = 2880;
		end_view_pos.y = 540;
		break;
	case ABOUT_US_PAGE:
		end_view_pos.x = 960;
		end_view_pos.y = 1620;
		break;
	case MAIN_PAGE:
		end_view_pos.x = 960;
		end_view_pos.y = 540;
	}

	this->view_animation = true;
	this->view_end_point = sf::Vector2f(end_view_pos);
}

void MenuState::handle(StateMachine &state_machine, double delta_time) {
	if (view_animation) {
		if (abs(this->view_end_point.x - state_machine.view->getCenter().x) > 10) {
			if (this->view_end_point.x - state_machine.view->getCenter().x < 10) {
				state_machine.view->move(-1980 * delta_time, 0);
			} 
			if (this->view_end_point.x - state_machine.view->getCenter().x > 10) {
				state_machine.view->move(1980 * delta_time, 0);
			}
		} else if (abs(this->view_end_point.y - state_machine.view->getCenter().y) > 10) {
			if (this->view_end_point.y - state_machine.view->getCenter().y < 10) {
				state_machine.view->move(0, -1080 * delta_time);
			}
			if (this->view_end_point.y - state_machine.view->getCenter().y > 10) {
				state_machine.view->move(0, 1080 * delta_time);
			}
		} else {
			state_machine.view->setCenter(view_end_point);
			view_animation = false;
		}
		sbackground.setPosition(state_machine.view->getCenter());
	} else {
		for (Button &button_iter : this->buttons) {
			if (button_iter.contains(*state_machine.event, *state_machine.window)) {
				button_iter.set_text_color(sf::Color(255, 0, 0, 255));
			} else {
				button_iter.set_text_color(sf::Color(255, 255, 255, 255));
			}

			if (button_iter.click_on(*state_machine.event, *state_machine.window)) {
				switch (button_iter.type) {
				case CONTINUE_BUTTON:
					state_machine.switch_state("game");
					break;
				case RESTART_BUTTON:
					this->change_page(RESTART_PAGE, *state_machine.view);
					break;
				case SAVES_BUTTON:
					this->change_page(SAVES_PAGE, *state_machine.view);
					break;
				case OPTIONS_BUTTON:
					this->change_page(OPTIONS_PAGE, *state_machine.view);
					break;
				case ABOUT_US_BUTTON:
					this->change_page(ABOUT_US_PAGE, *state_machine.view);
					break;
				case EXIT_BUTTON:
					std::exit(0);
					break;
				case BACK_BUTTON:
					this->change_page(MAIN_PAGE, *state_machine.view);
					break;
				}
			}
		}
	}
}

void MenuState::draw_content(sf::RenderWindow &window) {
	window.draw(this->sbackground);
	window.draw(this->ssaves);
	for (Button& button_iter : this->buttons) {
		window.draw(button_iter.get_text());
	}
	window.draw(this->restart_game_text);
	window.draw(this->about_us_text);
	window.draw(this->options_text);
};


Button::Button(int type, std::string str, sf::Font& font, int xpos, int ypos) {
	this->type = type;
	this->text.setCharacterSize(64);
	this->text.setFillColor(sf::Color(255, 255, 255, 200));
	this->text.setString(str);
	this->text.setFont(font);
	this->text.setPosition(xpos, ypos);
}

sf::Text Button::get_text() {
	return this->text;
}

bool Button::contains(sf::Event& event, sf::RenderWindow& window) {
	if (this->text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		return true;
	}
	return false;
}
bool Button::click_on(sf::Event& event, sf::RenderWindow& window) {
	if (this->text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		if (event.type == sf::Event::MouseButtonReleased || event.key.code == sf::Mouse::Left) {
			return true;
		}

	}
	return false;
}
void Button::set_text_color(sf::Color color) {
	this->text.setFillColor(color);
}