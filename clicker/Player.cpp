#include "Player.h"
Player::Player()
	:lvl(1), total_clicks(0), total_upgrades(0), name(30, sf::Color::White, false), forImg(1),
	profile("Level: " + std::to_string(lvl) + "\nTotal clicks: " + std::to_string(total_clicks) + "\nTotal upgrades: " + std::to_string(total_upgrades), 15, sf::Color::Yellow, { 630, 160 })//, name("Player")
{
	name.setPosition({ 657, 110 });
	name.setLimit(true, 17);
	
	icon.loadFromFile("Textures/Icons/Male.png");
	PlayerIcon.setTexture(icon);
	
	PlayerIcon.setPosition(550, 164);
}

/*
Player::Player(std::string pName)
	: lvl(1), total_clicks(0), total_upgrades(0), name(15, sf::Color::White, false)//, name(pName)
{}
*/
	//textbox1(15, sf::Color::White, false);
	

void Player::drawPlayer(sf::RenderWindow& window)
{
	window.draw(PlayerIcon);
	profile.drawDescription(window);
	name.drawTextBox(window);
}

void Player::addClick()
{
	total_clicks += 1;
	if (total_clicks % 1000 == 0)
		lvl += 1;
	updatePlayer();
}

void Player::addUpgrade()
{
	total_upgrades += 1;
	if (total_upgrades % 50 == 0)
		lvl += 1;
	updatePlayer();
}

bool Player::isOnIcon(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = PlayerIcon.getPosition().x;
	float btnPosY = PlayerIcon.getPosition().y;

	float btnPositionWidth = btnPosX + PlayerIcon.getLocalBounds().width;
	float btnPositionHeight = btnPosY + PlayerIcon.getLocalBounds().height;

	if (mouseX < btnPositionWidth && mouseX > btnPosX&& mouseY < btnPositionHeight && mouseY > btnPosY) {
		return true;
	}
	else return false;
}

void Player::changeIcon()
{
	if (forImg == 1){
		icon.loadFromFile("Textures/Icons/Female.png");
		forImg = 0;
	}
	else {
		icon.loadFromFile("Textures/Icons/Male.png");
		forImg = 1;
	}
}

void Player::updatePlayer()
{
	std::string update = "Level: " + std::to_string(lvl) + "\nTotal clicks: " + std::to_string(total_clicks) + "\nTotal upgrades: " + std::to_string(total_upgrades);
	profile.setNewDescription(update);
}
