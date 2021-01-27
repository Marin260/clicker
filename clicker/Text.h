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

	Descriptions(std::string ssDesc, int charDesc, sf::Color colorDesc, sf::Vector2f posDesc) {
		description.setString(ssDesc);
		description.setCharacterSize(charDesc);
		description.setPosition(posDesc);
		description.setFillColor(colorDesc);
	}

	void setFont(sf::Font& font) {
		description.setFont(font);
	}



	void drawDescription(sf::RenderWindow& window) {
		window.draw(description);
	}

};



class TextBox {
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false, hasLimit = false;
	int limit;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			text << static_cast<char>(charTyped); // if not special key, add to the text variable
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) { // only allow delete if there has been input
				deleteLastCharacter();
			}
		}

		textbox.setString(text.str() + "|"); // indicator of next character
	}

	void deleteLastCharacter() {
		std::string t = text.str();
		std::string newT = "";

		for (int i = 0; i < t.length() - 1; i++) { // copy everything but the last key
			newT += t[i];
		}

		text.str(""); // clear before copy
		text << newT; // copy

		textbox.setString(text.str()); // set the variable
	}

public:
	TextBox() {	}

	TextBox(int size, sf::Color color, bool selected) {
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = selected;

		if (selected) {
			textbox.setString("|");
		}

		else {
			textbox.setString(""); // if not selected, nothing shows up
		}
	}

	void setFont(sf::Font& font) {
		textbox.setFont(font); // set font
	}

	void setPosition(sf::Vector2f position) {
		textbox.setPosition(position); // set position in window
	}

	void setLimit(bool tf) {
		hasLimit = tf; // character limit
	}

	void setLimit(bool tf, int lim) {
		hasLimit = tf;
		limit = lim - 1; // deciding on limit
	}

	void setSelected(bool sel) { // has the user clicked on the text box?
		isSelected = sel;

		if (!sel) {
			std::string t = text.str();
			std::string newT = "";

			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}

			textbox.setString(newT);
		}
	}

	std::string getText() {
		return text.str(); // getting the text
	}

	void drawTextBox(sf::RenderWindow& window) {
		window.draw(textbox); // draw the textbox
	}

	void typedOn(sf::Event input) {
		if (isSelected) { // only if the user has decided to type in the text box
			int charTyped = input.text.unicode;
			if (charTyped < 128) { // only basic characters, edit later
				if (hasLimit) { // if the limit has been set
					if (text.str().length() <= limit) {
						inputLogic(charTyped); // if limit not passed, add
					}
					else if (text.str().length() > limit&& charTyped == DELETE_KEY) {
						deleteLastCharacter(); // allowing the user to delete even after reaching limit
					}
				}
				else {
					inputLogic(charTyped); // without limit
				}
			}
		}
	}
};