#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::RectangleShape button; // a rectangle
	sf::Text text;			   // with text on it

public:
	Button() { } // default constructor

	// -- overloading constructor (text, size of button, background color, text color, character size of text)
	Button(std::string btnT, sf::Vector2f btnSize, sf::Color btnBgColor, sf::Color btnTxtColor, int btnCharSize) {
		text.setString(btnT);
		text.setFillColor(btnTxtColor);
		text.setCharacterSize(btnCharSize);
		button.setSize(btnSize);
		button.setFillColor(btnBgColor);
	}

	// -- setting the font of the button
	void setFont(sf::Font& font) {
		text.setFont(font);
	}

	// -- setting the background color of the button
	void setBackgroundColor(sf::Color btnBgColor) {
		button.setFillColor(btnBgColor);
	}

	// -- setting the text color of the button
	void setTextColor(sf::Color btnTxtColor) {
		text.setFillColor(btnTxtColor);
	}

	// -- setting the position of the button and centering the text
	void setPosition(sf::Vector2f btnPosition) {
		button.setPosition(btnPosition);

		// centering the text
		float xBtnTxt = (btnPosition.x + button.getLocalBounds().width / 3.1) - (text.getLocalBounds().width / 2);
		float yBtnTxt = (btnPosition.y + button.getLocalBounds().height / 3.5) - (text.getLocalBounds().height / 2);
		text.setPosition({ xBtnTxt, yBtnTxt });
		/*
		What this basically does is:

		1. Get the coordinate + bounds of the button, and divide it by number (to get the button's center)
		2. Then subtract that by the total length of text (divided by number, again)

		"Number" depends on the size of the button. https://en.sfml-dev.org/forums/index.php?topic=26805.0

		This all causes the "real" center where the text will start to be in accordance with
		both the button's center and text's length.
		So, -----text1234----- instead of --------text1234-- (the latter caused without the subtraction)
		*/
	}

	// -- drawing the button
	void drawButton(sf::RenderWindow& window) {
		window.draw(button); // first draw the button
		window.draw(text);   // then draw the text
	}

	// -- determining whether the mouse is on the button []
	bool isMouseOverButton(sf::RenderWindow& window) {
		float mouseX = sf::Mouse::getPosition(window).x; // x coordinate of the mouse
		float mouseY = sf::Mouse::getPosition(window).y; // y coordinate of the mouse

		float btnPosX = button.getPosition().x; // x coordinate of the button
		float btnPosY = button.getPosition().y; // y coordinate of the button

		float btnPositionWidth = button.getPosition().x + button.getLocalBounds().width; // button width boundary
		float btnPositionHeight = button.getPosition().y + button.getLocalBounds().height; // button height boundary

		// if the mouse is within the button || smaller than lower end, greater than upper end (x or y)
		if (mouseX < btnPositionWidth && mouseX > btnPosX&& mouseY < btnPositionHeight && mouseY > btnPosY) {
			return true;
		}
		else return false;
	}
};