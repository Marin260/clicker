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
	Button(std::string btnT, sf::Vector2f btnSize, sf::Color btnBgColor, sf::Color btnTxtColor, int btnCharSize);

	// -- setting the font of the button
	void setFont(sf::Font& font);

	// -- setting the background color of the button
	void setBackgroundColor(sf::Color btnBgColor);

	// -- setting the text color of the button
	void setTextColor(sf::Color btnTxtColor);

	// -- setting the position of the button and centering the text
	void setPosition(sf::Vector2f btnPosition);

	// -- drawing the button
	void drawButton(sf::RenderWindow& window);

	// -- determining whether the mouse is on the button []
	bool isMouseOverButton(sf::RenderWindow& window);
};