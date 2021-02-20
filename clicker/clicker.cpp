#include <iostream>
#include <string>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"Button.h"
#include"Text.h"
#include"Business.h"
#include"Player.h"

/*
	https://www.youtube.com/watch?v=T31MoLJws4U
	www.sfml-dev.org/documentation/2.5.1/classsf_1_1[IME_KLASE].php
	https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Color.php
*/

int main()
{
	// srand(time(0)); // setting up a randomizer
	// Window:
	sf::RenderWindow window(sf::VideoMode(950, 768), "Clicker"); // Final window size: 500, 850
	window.setFramerateLimit(60); // FPS

	// Graphics:
	sf::Texture t1;
	t1.loadFromFile("Textures/Backgrounds/mainbg.jpg");

	sf::Sprite sBackground(t1); // putting the texture into an element (sprite)

	/*
	Business container[7] = {
		Business("Newspaper delivery", 10, 1, 1, 0),
		Business("T-shirt shop", 50, 0.9, 5, 25),
		Business("Restaurant", 200, 0.8, 25, 100),
		Business("Music studio", 1000, 0.7, 100, 500),
		Business("Software company", 10000, 0.6, 1000, 5000),
		Business("Oil company", 50000, 0.5, 5000, 25000),
		Business("Space company", 100000, 0.4, 10000, 100000)
	};
	*/

	Business container[7] = {
		Business("Newspaper delivery", 10, 1, 1, 0, "Textures/Icons/Newspaper.png"),
		Business("T-shirt shop", 50, 0.9, 5, 0, "Textures/Icons/T-shirt.png"),
		Business("Cafe", 200, 0.8, 25, 0, "Textures/Icons/Cafe.png"),
		Business("Music studio", 1000, 0.7, 100, 0, "Textures/Icons/Music.png"),
		Business("Software company", 10000, 0.6, 1000, 0, "Textures/Icons/Software.png"),
		Business("Oil company", 50000, 0.5, 5000, 0, "Textures/Icons/Oil.png"),
		Business("Space company", 100000, 0.4, 10000, 0, "Textures/Icons/Space.png")
	};

	Player player1;


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
	sf::Font ArialCyr; // TO DO: check if you have to credit the author
	ArialCyr.loadFromFile("Fonts/ArialCyr.ttf");
	*/
	std::string rules = "Welcome to clicker. Run your businesses and grow.\n-Buying businesses\n-Earn money buy clicking on your businesses.\n-Upgrade for more money\n-Automate the earnings for extra cash\nHave fun!";
	std::vector<Descriptions> gameDesc = {
		Descriptions("Wallet: " + std::to_string(Business::wallet), 15, sf::Color::Yellow, { 50, 710 }),
		Descriptions("Clicker game", 30, sf::Color::Yellow, { 50, 10 }),
		Descriptions("Can you overflow your wallet?...", 20, sf::Color::Yellow, { 50, 50 }),
		Descriptions("Profile:", 30, sf::Color::Yellow, { 550, 110 }),
		Descriptions(rules, 15, sf::Color::Yellow, { 550, 500 })
	};

	//std::vector<Business> openBuis;

	// Time:
	sf::Clock timeClock; // setting the timer


	//									 ---------- Game Loop ----------									 //
	while (window.isOpen())
	{
		double timer = 0;
		timer = timeClock.getElapsedTime().asSeconds();
		timer = ceil(timer * 100) / 100; // turning it into normal lmao
		
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

		// Event loop:
		sf::Event event; // better not use lowercase event as a name

		
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
					/*
					if (container[i].getOneBtn(0, window) && (container[i].getUpgradePrice() > Business::wallet || container[i].getStatus() == 0)) // ako je hover i ako je upgrade kosta vise od onoga sto je u walletu
						container[i].updateBtnColor(0, sf::Color::Red); // postavi crnu boju
					else if (container[i].getOneBtn(0, window))
						container[i].updateBtnColor(0, sf::Color::Magenta); // inace stavi rozu
					else if(container[i].getOneBtn(1, window) && container[i].getUnlockPrice() > Business::wallet && container[i].getStatus() == 0)
						container[i].updateBtnColor(1, sf::Color::Red);
					else if (container[i].getOneBtn(1, window)) //ako je preko drugog gumba onda stavi postavi njemu rozu
						container[i].updateBtnColor(1, sf::Color::Magenta);
					else if (container[i].getOneBtn(2, window) && container[i].getAutoPrice() > Business::wallet && container[i].getState() == 0)
						container[i].updateBtnColor(2, sf::Color::Red);
					else if (container[i].getOneBtn(2, window) && container[i].getState() == 0)  //ako je preko drugog gumba onda stavi postavi njemu rozu
						container[i].updateBtnColor(2, sf::Color::Magenta);
					else {
						container[i].updateBtnColor(0, sf::Color::White); // and afterwards returned to normal
						container[i].updateBtnColor(1, sf::Color::White);
						if (container[i].getState() == 1)
							container[i].updateBtnColor(2, sf::Color::Green);
						else
							container[i].updateBtnColor(2, sf::Color::White);
					}
					*/
					if(container[i].getOneBtn(0, window)){	// Prvi gumb u redu
						if (container[i].getUpgradePrice() > Business::wallet || container[i].getStatus() == 0) 
							container[i].updateBtnColor(0, sf::Color::Red);
						else
							container[i].updateBtnColor(0, sf::Color::Magenta);		
					}
					else if (container[i].getOneBtn(1, window)) { // Drugi gumb u redu
						if (container[i].getUnlockPrice() > Business::wallet&& container[i].getStatus() == 0)
							container[i].updateBtnColor(1, sf::Color::Red);
						else
							container[i].updateBtnColor(1, sf::Color::Magenta);
					}
					else if (container[i].getOneBtn(2, window) && container[i].getState() == 0) {	// Treci gumb u redu
						if (container[i].getAutoPrice() > Business::wallet)
							container[i].updateBtnColor(2, sf::Color::Red);
						else if (i != 0 && container[i-1].getState()==0)
							container[i].updateBtnColor(2, sf::Color::Red);
						else
							container[i].updateBtnColor(2, sf::Color::Magenta);
					}
					else {
						container[i].updateBtnColor(0, sf::Color::White); // and afterwards returned to normal
						container[i].updateBtnColor(1, sf::Color::White);
						container[i].getState() == 1 ? container[i].updateBtnColor(2, sf::Color::Green) : container[i].updateBtnColor(2, sf::Color::White);
					}
				}
				break;

			case sf::Event::MouseButtonPressed: // ako se gumb pretisne
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
					else if (container[i].getOneBtn(1, window)) {// work button
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
			case sf::Event::TextEntered: // when text is entered
				player1.name.typedOn(event);
			}
		}
		std::string balance = "Wallet: " + std::to_string(Business::wallet);
		// Display:
		window.clear();
		window.draw(sBackground);

		//				TEXT NA EKRANU
		gameDesc[0].setNewDescription(balance);
		for (auto desc : gameDesc) 
			desc.drawDescription(window);
		//				PROFIL
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

/*
												+++++++++ TO DO +++++++++

- OCISTITI KOD:
	- Napraviti game klasu u koju mozemo strpati logiku (ako je moguce)
		- Ili nekako Optimizirati na neki nacin
	- Text nesmije biti hard coded nego loadati iz datoteke.txt
*/