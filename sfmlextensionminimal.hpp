#ifndef SFMLEXTENSIONMINIMAL_HPP
#define SFMLEXTENSIONMINIMAL_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

class SFMLExtensionMinimal{
	bool holdingM1 = false;
	bool holdingM2 = false;

	public:

	bool m1_pressed(){
		const bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		const bool out = (!holdingM1) && pressed;
		holdingM1 = pressed;
		return out;
	}

	bool m2_pressed(){
		const bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
		const bool out = (!holdingM2) && pressed;
		holdingM2 = pressed;
		return out;
	}

	bool text_clicked(const sf::RenderWindow &window, const sf::Text text){
		const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		return text.getGlobalBounds().contains(mousePos.x, mousePos.y) && m1_pressed();
	}

	template <class T>
	static unsigned x_position_for_middle(const T shape, sf::RenderWindow &window){
		return window.getSize().x/2 - shape.getGlobalBounds().width/2;
	}

	template <class T>
	static unsigned y_position_for_middle(const T shape, sf::RenderWindow &window){
		return window.getSize().y/2 - shape.getGlobalBounds().height/2;
	}

	template <class T>
	static signed y_position_for_lowest(const T shape, sf::RenderWindow &window){
		return window.getSize().y - shape.getGlobalBounds().height;
	}

	static float get_rightmost_position_of_character(sf::Text &text, const std::size_t charIndex){
		const sf::Uint32 unicodeCode = text.getString()[charIndex];
		// Technically the start of the next character
		const float lengthToEndOfChar = text.getFont()->getGlyph(unicodeCode, text.getCharacterSize(), false).advance;

		return text.findCharacterPos(charIndex).x + lengthToEndOfChar;
	}
};

#endif // SFMLEXTENSIONMINIMAL_HPP
