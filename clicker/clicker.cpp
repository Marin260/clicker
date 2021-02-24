#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "Button.h"
#include "Text.h"
#include "Business.h"
#include "Player.h"

int main()
{
	// Prozor:
	sf::RenderWindow window(sf::VideoMode(950, 768), "Money Clicker", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60); // FPS

	sf::Image favicon;
	favicon.loadFromFile("Textures/Icons/favicon.png");
	window.setIcon(32, 32, favicon.getPixelsPtr());

	// Grafike:
	sf::Texture t1, t2;
	t1.loadFromFile("Textures/Backgrounds/mainbg.png");
	t2.loadFromFile("Textures/animation.png");

	sf::Sprite sBackground(t1); // stavljanje teksture u sprite
	sf::Sprite sAnimated(t2); int rot = 0;

	/* Boje:
	Crvena (prijasnja red):		sf::Color(224, 41, 41)
	Plava (prijasnja green):	sf::Color(102, 180, 219)
	Siva (prijasnja magenta):	sf::Color(196, 196, 196)

	*/

	Business container[7] = {
		Business("Newspaper delivery", 10, 1, 1, 0, "Textures/Icons/Newspaper.png"),
		Business("T-shirt shop", 50, 0.9, 5, 25, "Textures/Icons/T-shirt.png"),
		Business("Cafe", 200, 0.8, 25, 100, "Textures/Icons/Cafe.png"),
		Business("Music studio", 1000, 0.7, 100, 500, "Textures/Icons/Music.png"),
		Business("Software company", 10000, 0.6, 1000, 5000, "Textures/Icons/Software.png"),
		Business("Oil company", 50000, 0.5, 5000, 25000, "Textures/Icons/Oil.png"),
		Business("Space company", 100000, 0.4, 10000, 100000, "Textures/Icons/Space.png")
	};

	// Igraci:
	Player player1;

	// Audio:
	sf::Music bgMusic, msAccepted;
	bgMusic.openFromFile("Audio/ORU-Orange_Dreamsicle.ogg");
	bgMusic.play(); // ostale funkcije: .stop(), .pause()
	bgMusic.setVolume(15); // 15
	bgMusic.setLoop(true);
	
	// Pravila i opis:
	std::string rules = "Run your businesses and grow...\n- Buy businesses.\n- Earn money by clicking your businesses.\n- Upgrade to get more money every click.\n- Automate your earnings.\nHave fun!";
	std::vector<Descriptions> gameDesc = {
		Descriptions("Wallet: " + std::to_string(Business::wallet), 15, sf::Color::Yellow, { 50, 710 }),
		Descriptions("Money Clicker", 30, sf::Color(21, 167, 18), { 50, 10 }),
		Descriptions("Can you overflow your wallet?", 15, sf::Color::Yellow, { 50, 50 }),
		Descriptions("Profile:", 30, sf::Color::Yellow, { 550, 110 }),
		Descriptions("Press ENTER to type your name and ESCAPE to stop.", 13, sf::Color::Yellow, { 552, 95 }),
		Descriptions("^ click", 13, sf::Color::Yellow, { 555, 220 }),
		Descriptions(rules, 15, sf::Color::Yellow, { 550, 500 })
	};

	//std::vector<Business> openBuis;

	// Time:
	sf::Clock timeClock; // postavljanje timera


	//									 ---------- Game Loop ----------									 //
	while (window.isOpen())
	{
		double timer = 0;
		timer = timeClock.getElapsedTime().asSeconds();
		timer = ceil(timer * 100) / 100; // normalne decimale
		
		std::stringstream ss;
		for (int j = 0; j < Business::autoBusinesses; j++) {
			if (container[j].getState() == 1)
				container[j].updateTimer(timer);
		}
		ss << "Elapsed time: " << timer;

		/* ispis vremena na ekran*/
		/*
		sf::Text clockTime;
		clockTime.setString(ss.str());
		clockTime.setCharacterSize(20); // in pixels, not points!
		clockTime.setFillColor(sf::Color::White);
		clockTime.setPosition(250, 710);
		//clockTime.setFont(ArialCyr);
		*/

		//										---- Event loop ----
		sf::Event event;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // ENTER key if pressed
			player1.name.setSelected(true); // text can be written
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))  // ESCAPE key if pressed
			player1.name.setSelected(false); // text can be written

		// LOGIKA IGRE
		while (window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved: // Hover efekt na gumbima... 
				for (int i = 0; i < Business::unlockedBusinesses + 1; i++) {
					if (i == 7)
						break;
					if(container[i].getOneBtn(0, window)){	// Prvi gumb u redu
						if (container[i].getUpgradePrice() > Business::wallet || container[i].getStatus() == 0) 
							container[i].updateBtnColor(0, sf::Color(224, 41, 41));
						else
							container[i].updateBtnColor(0, sf::Color(196, 196, 196));
					}
					else if (container[i].getOneBtn(1, window)) { // Drugi gumb u redu
						if (container[i].getUnlockPrice() > Business::wallet&& container[i].getStatus() == 0)
							container[i].updateBtnColor(1, sf::Color(224, 41, 41));
						else
							container[i].updateBtnColor(1, sf::Color(196, 196, 196));
					}
					else if (container[i].getOneBtn(2, window) && container[i].getState() == 0) {	// Treci gumb u redu
						if (container[i].getAutoPrice() > Business::wallet)
							container[i].updateBtnColor(2, sf::Color(224, 41, 41));
						else if (i != 0 && container[i-1].getState()==0)
							container[i].updateBtnColor(2, sf::Color(224, 41, 41));
						else
							container[i].updateBtnColor(2, sf::Color(196, 196, 196));
					}
					else {
						container[i].updateBtnColor(0, sf::Color::White); // and afterwards returned to normal
						container[i].updateBtnColor(1, sf::Color::White);
						container[i].getState() == 1 ? container[i].updateBtnColor(2, sf::Color(102, 180, 219)) : container[i].updateBtnColor(2, sf::Color::White);
					}
				}
				break;

			case sf::Event::MouseButtonPressed: // ako se gumb pritisne
				for (int i = 0; i < Business::unlockedBusinesses + 1; i++) {
					if (i == 7)
						break;
					if (container[i].getOneBtn(0, window) && container[i].getStatus() != 0) {// nadogradi button
						if (container[i].getUpgradePrice() <= Business::wallet) {
							container[i].upgrade();
							player1.addClick();
							player1.addUpgrade();
						}
						break;
					}
					else if (container[i].getOneBtn(1, window)) { // work button
						if (container[i].getStatus() == 0 && container[i].getUnlockPrice() <= Business::wallet) {
							container[i].unlock();
							player1.addClick();
						}
						else if (container[i].getStatus() == 1) {
							container[i].add_to_wallet();
							player1.addClick();
						}
						break;
					}
					else if (container[i].getOneBtn(2, window)) { // auto button
						if (container[i].getState() != 1 && container[i].getStatus() == 1 && container[i].getAutoPrice() <= Business::wallet) {
							if (i == 0) {
								container[i].automate(timer);
								player1.addClick();
							}
							else if (container[i - 1].getState() == 1) {
								container[i].automate(timer);
								player1.addClick();
							}
						}
					}
				}
				if (player1.isOnIcon(window))
					player1.changeIcon();
				break;
			case sf::Event::TextEntered: // kad je tekst unesen
				player1.name.typedOn(event);
			}
		}
		std::string balance = "Wallet: " + std::to_string(Business::wallet);

		// Animation:
		sAnimated.move(2.0f, 0.5f);
		rot += 1.5;
		sAnimated.setRotation(rot);

		// Display:
		window.clear();
		window.draw(sBackground);
		if (timer < 45) window.draw(sAnimated);

		//	TEKST NA EKRANU
		gameDesc[0].setNewDescription(balance);
		for (auto desc : gameDesc) 
			desc.drawDescription(window);

		//	PROFIL
		player1.drawPlayer(window);
		
		for (int i = 0; i < Business::unlockedBusinesses+1; i++) {// crtanje buttona
			if (i == 7)
				break;
			container[i].drawBusiness(window);
		}

		//window.draw(clockTime);
		window.display();
	}
	return 0;
}