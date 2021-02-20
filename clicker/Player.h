#pragma once
#include<iostream>
#include "Text.h"
class Player
{
private:
	//std::string name;
	int lvl, total_clicks, total_upgrades;
	bool forImg;
	Descriptions profile;

	sf::Texture icon;
	sf::Sprite PlayerIcon;
	// samo sa unutarnju uporabu
	void updatePlayer();
public:
	Player();
	//Player(std::string pName);
	TextBox name;

	void drawPlayer(sf::RenderWindow& window);
	void addClick();
	void addUpgrade();

	// funkcije za ikonu
	bool isOnIcon(sf::RenderWindow& window);
	void changeIcon();
};

