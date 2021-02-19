#pragma once
#include<iostream>
#include "Text.h"
class Player
{
private:
	//std::string name;
	int lvl, total_clicks, total_upgrades;
public:
	Player();
	//Player(std::string pName);
	~Player();
	TextBox name;

	void drawPlayer(sf::RenderWindow& window);
};

