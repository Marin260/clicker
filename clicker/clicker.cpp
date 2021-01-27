// clicker_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"Button.h"
#include"Text.h"

/*
	Marine, pisao sam komentare na engleskom jer si i ti, al mozda bi ipak trebali na hrvatskom.
	Inace sam pokusao objasniti svaki dio, pisi i ti komentare da skuzim sto si ti radio.
	Koristio sam ovaj video: https://www.youtube.com/watch?v=T31MoLJws4U i svoj kod od onog svog projekta.
	Da se tu dosta toga izmijeniti, kao i nazivi varijabli koje bih isto preporucio da radimo na hrvatskom.

	Ima par 8-bit pjesmi u Audio folderu, treba prvo grafike napraviti pa onda odabrati stil,
	ti si nesto govorio 8-bit pa sam to stavio.

	Dosta dokumentacije za SFML klase se moze lako naci na
						www.sfml-dev.org/documentation/2.5.1/classsf_1_1[IME_KLASE].php
	Recimo npr. https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Color.php

	Kod onog mog programa je na
	https://discord.com/channels/697351184415195156/697351184415195159/704442224125018192

	Isto tako, planiram napraviti Button.cpp i Text.cpp i tamo sve napisati sto sam u headerima.

	Brojac vremena i text input su testovi.
*/

int main()
{
	srand(time(0)); // setting up a randomizer

	// Window:
	sf::RenderWindow window(sf::VideoMode(500, 750), "SFML works!"); // Final window size: 500, 850
	window.setFramerateLimit(60); // FPS

	// Graphics:
	sf::Texture t1;
	t1.loadFromFile("Textures/Backgrounds/mainbg.jpg");

	sf::Sprite sBackground(t1); // putting the texture into an element (sprite)

	// Audio:
	sf::Music bgMusic;
	bgMusic.openFromFile("Audio/ORU-Orange_Dreamsicle.ogg"); // SFML doesn't support mp3
	bgMusic.play(); // .stop(), .pause()
	bgMusic.setVolume(40); // just set this to 0 if you don't want to hear it
	bgMusic.setLoop(true);
	// other simpler tunes can just be used with sf::Sound

	// Fonts:
	sf::Font ArialCyr; // TO DO: check if you have to credit the author
	ArialCyr.loadFromFile("Fonts/ArialCyr.ttf");

	// Buttons:
	Button buttonClick("Click me", { 200, 50 }, sf::Color::White, sf::Color::Black, 20); // <Button.h>
	buttonClick.setPosition({ 150, 350 }); // numbers represent lower boundary, i.e. center is (window-button)/2
	buttonClick.setFont(ArialCyr);

	// Text:
	TextBox textbox1(15, sf::Color::White, false); // <Text.h>, see Event loop for how to initialize
	textbox1.setPosition({ 170, 150 });
	textbox1.setFont(ArialCyr);
	textbox1.setLimit(true, 20); // hasLimit = true, and the limit is 20 characters

	Descriptions desc1("Press ENTER to type your name and ESCAPE to leave:", 15, sf::Color::Yellow, { 60, 100 });
	desc1.setFont(ArialCyr); // initializing the font in the constructor will crash the program [FUCKING TESTED]

	// Time:
	sf::Clock timeClock; // setting the timer


	//									 ---------- Game Loop ----------									 //
	while (window.isOpen())
	{
		float timer = 0;
		float time = 0;
		timer = timeClock.getElapsedTime().asSeconds();
		timer = ceilf(timer * 100) / 100; // turning it into normal lmao
		time += timer;

		std::stringstream ss;
		ss << "Elapsed time: " << timer;

		sf::Text clockTime;
		clockTime.setFont(ArialCyr);
		clockTime.setString(ss.str());
		clockTime.setCharacterSize(20); // in pixels, not points!
		clockTime.setFillColor(sf::Color::White);
		//clockTime.setStyle(Text::Bold);
		clockTime.setPosition(250, 600);


		// Event loop:
		sf::Event Event; // better not use lowercase event as a name

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // ENTER key if pressed
			textbox1.setSelected(true); // text can be written
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // ESCAPE key if pressed
			textbox1.setSelected(false); // exits selection
		}

		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();

			case sf::Event::MouseMoved: // if the mouse is moved 
				if (buttonClick.isMouseOverButton(window)) { // over the button = background color changes
					buttonClick.setBackgroundColor(sf::Color::Magenta);
				}
				else {
					buttonClick.setBackgroundColor(sf::Color::White); // and afterwards returned to normal
				}
			case sf::Event::TextEntered: // when text is entered
				textbox1.typedOn(Event);
			}
		}

		// Display:
		window.clear();
		window.draw(sBackground);
		desc1.drawDescription(window);
		textbox1.drawTextBox(window);
		buttonClick.drawButton(window);
		window.draw(clockTime);
		window.display();
	}

	return 0;
}

/*
												+++++++++ TO DO +++++++++

- Button popping up and disappearing based on criterium
- Implement .cpp's for .h's
- Figure out how to deal with fullscreen
- Figure out why text is randomly written into the text box at times

*/