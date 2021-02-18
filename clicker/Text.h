#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#define DELETE_KEY 8 // the value for the delete key is 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

// TO DO, this is just a test
class Descriptions {
private:
	sf::Text description;
	//std::stringstream ssDesc;

public:
	Descriptions() { }

	Descriptions(std::string ssDesc, int charDesc, sf::Color colorDesc, sf::Vector2f posDesc);

	void setFont(sf::Font& font);
	void setNewDescription(std::string &value);


	void drawDescription(sf::RenderWindow& window);

};



class TextBox {
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false, hasLimit = false;
	int limit;

	void inputLogic(int charTyped);

	void deleteLastCharacter();

public:
	TextBox() {	}
	TextBox(int size, sf::Color color, bool selected);

	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f position);
	void setLimit(bool tf);
	void setLimit(bool tf, int lim);
	void setSelected(bool sel);
	std::string getText();
	void drawTextBox(sf::RenderWindow& window);
	void typedOn(sf::Event input);
};