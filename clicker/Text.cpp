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
		text << static_cast<char>(charTyped); // ako nije SPECIAL KEY, onda dodaj tekstu
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) { // delete samo ako ima inputa
			deleteLastCharacter();
		}
	}

	textbox.setString(text.str() + "|"); // indikator za iduci character
}

void TextBox::deleteLastCharacter() {
	std::string t = text.str();
	std::string newT = "";

	for (int i = 0; i < t.length() - 1; i++) { // kopiraj sve osim zadnjeg charactera
		newT += t[i];
	}

	text.str(""); // ocisti prije kopiranja
	text << newT; // kopiraj

	textbox.setString(text.str()); // postavi varijablu
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
		textbox.setString(textbox.getString() + ""); // ako nije selektirano, nista se pojavljuje
	}
}

void TextBox::setPosition(sf::Vector2f position) {
	textbox.setPosition(position); // postavi poziciju u prozoru
}

void TextBox::setLimit(bool tf) {
	hasLimit = tf; // character limit
}

void TextBox::setLimit(bool tf, int lim) {
	hasLimit = tf;
	limit = lim - 1; // odluka za limit
}

void TextBox::setSelected(bool sel) { // je li korisnik u textboxu?
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
	if (isSelected) { // samo ako je korisnik odlucio nesto unesti u textbox
		int charTyped = input.text.unicode;
		if (charTyped < 128) { // samo basic characters
			if (hasLimit) { // ako limit postoji
				if (text.str().length() <= limit) {
					inputLogic(charTyped); // dodaj ako limit nije prekoracen
				}
				else if (text.str().length() > limit&& charTyped == DELETE_KEY) {
					deleteLastCharacter(); // delete nakon dolaska do limita
				}
			}
			else {
				inputLogic(charTyped); // bez limita
			}
		}
	}
}

void TextBox::setTxt(std::string txt)
{
	textbox.setString(txt);
}


