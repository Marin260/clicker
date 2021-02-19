#include "Player.h"
Player::Player()
	:lvl(1), total_clicks(0), total_upgrades(0), name(15, sf::Color::White, false)//, name("Player")
{
	name.setPosition({ 500, 150 });
	name.setLimit(true, 20);
}

/*
Player::Player(std::string pName)
	: lvl(1), total_clicks(0), total_upgrades(0), name(15, sf::Color::White, false)//, name(pName)
{}
*/
	//textbox1(15, sf::Color::White, false);
	

void Player::drawPlayer(sf::RenderWindow& window)
{
	name.drawTextBox(window);
}
