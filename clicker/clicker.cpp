// clicker_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"Button.h"
#include"Text.h"
#include"Business.h"

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
	/*
	*/
	Business container[7] = {
		Business(10, 1, 1, 0, 1, 30, 30, 100),
		Business(50, 0.9, 5, 25, 1, 30, 110, 1000),
		Business(200, 0.8, 25, 100, 1, 30, 190, 10000),
		Business(1000, 0.7, 100, 500, 1, 30, 270, 100000),
		Business(10000, 0.6, 1000, 5000, 1, 30, 350, 1000000),
		Business(50000, 0.5, 5000, 25000, 1, 30, 430, 10000000),
		Business(100000, 0.4, 10000, 500000, 1, 30, 510, 100000000)
	};

	
	srand(time(0)); // setting up a randomizer

	// Window:
	sf::RenderWindow window(sf::VideoMode(570, 750), "Clicker"); // Final window size: 500, 850
	window.setFramerateLimit(60); // FPS

	// Graphics:
	sf::Texture t1;
	t1.loadFromFile("Textures/Backgrounds/mainbg.jpg");

	sf::Sprite sBackground(t1); // putting the texture into an element (sprite)

	// Audio:
	//TODO KASNIJE
	/*
	sf::Music bgMusic;
	bgMusic.openFromFile("Audio/ORU-Orange_Dreamsicle.ogg"); // SFML doesn't support mp3
	bgMusic.play(); // .stop(), .pause()
	bgMusic.setVolume(40); // just set this to 0 if you don't want to hear it
	bgMusic.setLoop(true);
	*/
	// other simpler tunes can just be used with sf::Sound

	// Fonts:
	/*
	*/
	sf::Font ArialCyr; // TO DO: check if you have to credit the author
	ArialCyr.loadFromFile("Fonts/ArialCyr.ttf");

	// Text:
	/*TODO KASNIJE
	TextBox textbox1(15, sf::Color::White, false); // <Text.h>, see Event loop for how to initialize
	textbox1.setPosition({ 170, 150 });
	textbox1.setFont(ArialCyr);
	textbox1.setLimit(true, 20); // hasLimit = true, and the limit is 20 characters
	*/

	std::string balance = "Balance: " + std::to_string(Business::wallet);
	std::cout<<balance;
	Descriptions desc1(balance, 15, sf::Color::Yellow, { 30, 590 });
	desc1.setFont(ArialCyr); // initializing the font in the constructor will crash the program [FUCKING TESTED]

	// Time:
	sf::Clock timeClock; // setting the timer


	//									 ---------- Game Loop ----------									 //
	while (window.isOpen())
	{
		double timer = 0;
		timer = timeClock.getElapsedTime().asSeconds();
		timer = ceilf(timer * 100) / 100; // turning it into normal lmao
		
		std::stringstream ss;
		for (int j = 0; j < Business::autoBusinesses; j++) {
			if (container[j].getState() == 1) {
				container[j].updateTimer(timer);
				
			}
		}
		ss << "Elapsed time: " << timer;

		/* ispis vremena na ekran*/
		sf::Text clockTime;
		clockTime.setFont(ArialCyr);
		clockTime.setString(ss.str());
		clockTime.setCharacterSize(20); // in pixels, not points!
		clockTime.setFillColor(sf::Color::White);
		//clockTime.setStyle(Text::Bold);
		clockTime.setPosition(250, 600);


		// Event loop:
		sf::Event event; // better not use lowercase event as a name

		/*TODO KASNIJE
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // ENTER key if pressed
			textbox1.setSelected(true); // text can be written
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // ESCAPE key if pressed
			textbox1.setSelected(false); // exits selection
		}
		*/
		// Klikovi i hoveri
		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved: // if the mouse is moved 
				for (int i = 0; i < 7; i++) {
					if (container[i].getOneBtn(0, window) && (container[i].getUpgradePrice() > Business::wallet || container[i].getStatus() == 0)) { // ako je hover i ako je upgrade kosta vise od onoga sto je u walletu
						container[i].updateBtnColor(0, sf::Color::Black); // postavi crnu boju
					}
					else if(container[i].getOneBtn(1, window) && container[i].getUnlockPrice() > Business::wallet && container[i].getStatus() == 0)
						container[i].updateBtnColor(1, sf::Color::Black);
					else if (container[i].getOneBtn(2, window) && container[i].getAutoPrice() > Business::wallet && container[i].getState() == 0)
						container[i].updateBtnColor(2, sf::Color::Black);

					else if (container[i].getOneBtn(0, window)) {
						container[i].updateBtnColor(0, sf::Color::Magenta); // inace stavi rozu
					}
					else if (container[i].getOneBtn(1, window)) { //ako je preko drugog gumba onda stavi postavi njemu rozu
						container[i].updateBtnColor(1, sf::Color::Magenta);
					}
					else if (container[i].getOneBtn(2, window) && container[i].getState() == 0) { //ako je preko drugog gumba onda stavi postavi njemu rozu
						container[i].updateBtnColor(2, sf::Color::Magenta);
					}
					else {
						container[i].updateBtnColor(0, sf::Color::White); // and afterwards returned to normal
						container[i].updateBtnColor(1, sf::Color::White);
						if (container[i].getState() == 1)
							container[i].updateBtnColor(2, sf::Color::Green);
						else
							container[i].updateBtnColor(2, sf::Color::White);
					}
				}
				break;
			case sf::Event::MouseButtonPressed: // ako se gumb pretisne
				for (int i = 0; i < Business::unlockedBusinesses + 1; i++) {
					if (i == 8)
						break;
					if (container[i].getOneBtn(0, window) && container[i].getStatus() != 0) {// nadogradi button
						if (container[i].getUpgradePrice() <= Business::wallet) {
							container[i].upgrade();
						}
						break;
					}
					else if (container[i].getOneBtn(1, window)) {// work button
						if (container[i].getStatus() == 0 && container[i].getUnlockPrice() <= Business::wallet) {
							container[i].unlock();
						}
						else if (container[i].getStatus() == 1) {
							container[i].add_to_wallet();
						}
						break;
					}
					else if (container[i].getOneBtn(2, window)) {
						if (container[i].getState() != 1 && container[i].getStatus() == 1 && container[i].getAutoPrice() <= Business::wallet)
							container[i].automate(timer);
					}
				}
			/*TODO
			case sf::Event::TextEntered: // when text is entered
				textbox1.typedOn(Event);
			*/
			}
		}
		balance = "Balance: " + std::to_string(Business::wallet);
		// Display:
		window.clear();
		window.draw(sBackground);
		desc1.setNewDescription(balance);
		desc1.drawDescription(window);
		//textbox1.drawTextBox(window);
		
		for (int i = 0; i < Business::unlockedBusinesses+1; i++) {
			if (i == 7)
				break;
			container[i].drawBusiness(window);
		}
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