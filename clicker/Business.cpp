#include "Business.h"




Business::Business() 
	: activate(0), state(0), multiplier(1), profit(1), unlock_price(1), profit_time(1), upgrade_price(1), lvl(1), startX(30), startY(30)
{
	ArialCyr.loadFromFile("Fonts/ArialCyr.ttf");
	
	btnText[0] = std::to_string(upgrade_price);

	for (int i = 0; i < 3; i++) {
		buttons.push_back(new Button(btnText[i], {150, 50}, sf::Color::White, sf::Color::Black, 20));
		buttons[i]->setFont(ArialCyr);
		buttons[i]->setPosition({startX, startY});
		startX += buttons[i]->getBtnSize('x') + 30;
	}

	startX = 30;
	startY += 80;
}
Business::Business(double bV, double mult, double prof, double unl, double timePro, float x, float y, float toAuto)
	: activate(0), state(0), multiplier(mult), profit(prof), unlock_price(unl), profit_time(timePro), 
	upgrade_price(bV), lvl(1), startX(x), startY(y), timer(0), automate_price(toAuto)
{
	ArialCyr.loadFromFile("Fonts/ArialCyr.ttf");

	btnText[0] = "Upgrade:\n-" + std::to_string(upgrade_price);

	for (int i = 0; i < 3; i++) {
		buttons.push_back(new Button(btnText[i], { 150, 50 }, sf::Color::White, sf::Color::Black, 10));
		buttons[i]->setFont(ArialCyr);
		buttons[i]->setPosition({ startX, startY });
		startX += buttons[i]->getBtnSize('x') + 30;
	}

	startX = 30;
	startY += 80; 
}

Business::~Business()
{
	for (int i = 0; i < 3; i++) {
		delete buttons[i];
		buttons[i] = 0;
	}

}

bool Business::getOneBtn(int index, sf::RenderWindow& window)
{
	if (buttons[index]->isMouseOverButton(window))
		return true;
	else
		return false;
}

double Business::getUpgradePrice()
{
	return upgrade_price;
}

double Business::getTotalProfit()
{
	return profit*multiplier;
}

double Business::getUnlockPrice()
{
	return unlock_price;
}

double Business::getAutoPrice()
{
	return automate_price;
}

bool Business::getState()
{
	return state;
}



void Business::automate(double& worldTime)
{
	// izmjena stanja
	state = 1;
	autoBusinesses += 1;
	timer = worldTime;
	wallet -= automate_price;
	updateBtnTxt(0, 0, 1);
}

void Business::add_to_wallet()
{
	wallet += profit * multiplier;
	//std::cout << timer << std::endl;
}

void Business::unlock()
{
	// otkljucaj Business
	if (activate == 0) activate = 1;
	wallet -= unlock_price;
	updateBtnTxt(0, 1, 0);
	unlockedBusinesses += 1;
	std::cout << std::endl;
	std::cout << unlockedBusinesses << std::endl;
}

void Business::upgrade()
{
	// povecaj profit Businessa
	wallet -= upgrade_price;
	upgrade_price *= 1.07;
	multiplier *= 1.02;
	lvl += 1;
	updateBtnTxt(1, 1, 0);
}

void Business::drawBusiness(sf::RenderWindow& window)
{
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->drawButton(window);
	}
}

void Business::updateBtnTxt(bool index1, bool index2, bool index3)
{
	if (index1 != 0)
		buttons[0]->setNewString("Upgrade:\n-" + std::to_string(upgrade_price));
	if (index2 != 0)
		buttons[1]->setNewString("+" + std::to_string(profit * multiplier));
	if (index3 != 0)
		buttons[2]->setNewString("AUTO: ON");
}

void Business::updateBtnColor(int index, sf::Color btnBgColor)
{
	buttons[index]->setBackgroundColor(btnBgColor);
}

void Business::updateTimer(double& worldTime)
{
	if (worldTime - timer > profit_time) {
		add_to_wallet();
		timer = worldTime;
	}
}

void Business::setNewBtnTxt(int index, std::string txt)
{
	buttons[index]->setNewString(txt);
}

bool Business::getStatus()
{
	return activate;
}

double Business::wallet = 0;
int Business::unlockedBusinesses = 0;
int Business::autoBusinesses = 0;