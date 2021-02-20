#include "Text.h"

Descriptions::Descriptions(std::string ssDesc, int charDesc, sf::Color colorDesc, sf::Vector2f posDesc) {
	description.setString(ssDesc);
	description.setCharacterSize(charDesc);
	description.setPosition(posDesc);
	description.setFillColor(colorDesc);
}

void Descriptions::setNewDescription(std::string& value)
{
	description.setString(value);
}

void Descriptions::drawDescription(sf::RenderWindow& window) {
	txtFont.loadFromFile("Fonts/ArialCyr.ttf");
	description.setFont(txtFont);
	window.draw(description);
}

void TextBox::inputLogic(int charTyped) {
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

void TextBox::deleteLastCharacter() {
	std::string t = text.str();
	std::string newT = "";

	for (int i = 0; i < t.length() - 1; i++) { // copy everything but the last key
		newT += t[i];
	}

	text.str(""); // clear before copy
	text << newT; // copy

	textbox.setString(text.str()); // set the variable
}

TextBox::TextBox(int size, sf::Color color, bool selected) {
	textbox.setString("Player");
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = selected;
	std::string x = textbox.getString();
	std::cout << x;
	if (selected) {
		textbox.setString(x);
	}
	else {
		textbox.setString(textbox.getString() + ""); // if not selected, nothing shows up
	}
}

void TextBox::setPosition(sf::Vector2f position) {
	textbox.setPosition(position); // set position in window
}

void TextBox::setLimit(bool tf) {
	hasLimit = tf; // character limit
}

void TextBox::setLimit(bool tf, int lim) {
	hasLimit = tf;
	limit = lim - 1; // deciding on limit
}

void TextBox::setSelected(bool sel) { // has the user clicked on the text box?
	isSelected = sel;

	if (!sel) {
		std::string t = text.str();
		std::string newT = "";

		if (t.length() == 0)
			textbox.setString("Player");
		else {
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
		
	}
}

std::string TextBox::getText() {
	return text.str(); // getting the text
}

void TextBox::drawTextBox(sf::RenderWindow& window) {
	txtFont.loadFromFile("Fonts/ArialCyr.ttf");
	textbox.setFont(txtFont);
	window.draw(textbox); // draw the textbox
}

void TextBox::typedOn(sf::Event input) {
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

void TextBox::setTxt(std::string txt)
{
	textbox.setString(txt);
}


