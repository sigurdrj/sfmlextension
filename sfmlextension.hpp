#ifndef SFMLEXTENSION_HPP
#define SFMLEXTENSION_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

extern const bool debug;

namespace SFMLExt{
	class General{
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

		static sf::Text to_sftext(const string str, sf::Font &font, const unsigned charSize, const sf::Color color={255,255,255}, const unsigned x=0, const unsigned y=0){
			sf::Text text;
			text.setFont(font);
			text.setString(str);
			text.setCharacterSize(charSize);
			text.setFillColor(color);
			text.setPosition(x,y);
			return text;
		}

		static sf::Texture to_sftxt(const string filename){
			sf::Texture txt;
			txt.loadFromFile(filename);
			return txt;
		}

		static sf::Sprite to_sfspr(sf::Texture &texture, const unsigned x=0, const unsigned y=0/*, const sf::Color color*/){
			sf::Sprite sprite;
			sprite.setTexture(texture);
//			sprite.setColor(color);
			sprite.setPosition(x,y);
			return sprite;
		}

		static void draw_spr(sf::RenderWindow &window, sf::Sprite &spr, const unsigned x=0, const unsigned y=0, const sf::Color color={255,255,255}){
			spr.setPosition(x, y);
			spr.setColor(color);
			window.draw(spr);
		}

		static bool text_clicked(const sf::RenderWindow &window, const sf::Text text){
			const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			return text.getGlobalBounds().contains(mousePos.x, mousePos.y) && m1_pressed();
		}

		static bool viewPosInWindow(const sf::Vector2f worldPos, const sf::View view){
			return !((worldPos.x > view.getSize().x || worldPos.x < 0)
				|| (worldPos.y > view.getSize().y || worldPos.y < 0));
		}

		template <class T>
		static unsigned x_position_for_middle(const T shape, sf::RenderWindow &window){
			return window.getSize().x/2 - shape.getGlobalBounds().width/2;
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

	class UI{
		public:

		static void draw_text_gradually(sf::RenderWindow &window, sf::Text &text, const sf::Time delay=sf::milliseconds(80)){
			const string textStr = text.getString();
		
			for (unsigned i = 1; i <= textStr.length(); i++){
				text.setString(textStr.substr(0,i));
				window.draw(text);
				if (!debug){
					window.display();
					sf::sleep(delay);
				}
			}
		}

		static void draw_text_box(sf::RenderWindow &window, const unsigned x, const unsigned y, const unsigned lineWidth, sf::Text &text, bool gradually=true, const sf::Time delay=sf::milliseconds(80), const unsigned spaceBetweenBoundaryAndText=8){
			const unsigned width = text.getGlobalBounds().width;
			const unsigned height = text.getGlobalBounds().height;
		
			sf::RectangleShape topLine(sf::Vector2f(width+spaceBetweenBoundaryAndText*2, lineWidth));
			topLine.setPosition(x-spaceBetweenBoundaryAndText, y);
		
			sf::RectangleShape bottomLine(sf::Vector2f(width+spaceBetweenBoundaryAndText*2, lineWidth));
			bottomLine.setPosition(x-spaceBetweenBoundaryAndText, y+height+spaceBetweenBoundaryAndText*2);
		
			sf::RectangleShape leftLine(sf::Vector2f(lineWidth, height+spaceBetweenBoundaryAndText*2));
			leftLine.setPosition(x-spaceBetweenBoundaryAndText, y);
		
			sf::RectangleShape rightLine(sf::Vector2f(lineWidth, height+spaceBetweenBoundaryAndText*2));
			rightLine.setPosition(x+width+spaceBetweenBoundaryAndText, y);
		
			window.draw(topLine);
			window.draw(bottomLine);
			window.draw(leftLine);
			window.draw(rightLine);
		
			text.setPosition(x,y);
			window.draw(text);
		}
	};
}

#endif // SFMLEXTENSION_HPP
