#include "Business.h"

Business::Business() // Default constructor
	: activate(0), state(0), name("/"), upgrade_price(0), multiplier(1), profit(1), unlock_price(0),
	profit_time(1), lvl(1), timer(0), automate_price(profit * 1000), desc(name, 20, sf::Color::Yellow, { 120, startY - 30 })
{}

Business::Business(std::string bN, double bV, double mult, double prof, double unl, std::string texture)
	: activate(0), state(0), name(bN), upgrade_price(bV), multiplier(mult), profit(prof), unlock_price(unl),
	  profit_time(1), lvl(1), timer(0), automate_price(prof*1000), desc(name, 20, sf::Color::Yellow, { 120, startY-30 })
{
	ArialCyr.loadFromFile("Fonts/ArialCyr.ttf"); // loadaj font koji ce se koristit za text

	btnText[0] = "Upgrade:\n-" + std::to_string(upgrade_price); // text na upgrade buttonu

	for (int i = 0; i < 3; i++) { // kreiranje 3 buttona za svaki novi business
		buttons.push_back(new Button(btnText[i], { 120, 50 }, sf::Color::White, sf::Color::Black, 10));
		buttons[i]->setFont(ArialCyr);
		buttons[i]->setPosition({ startX, startY }); // postavljanje pozicije na ekranu sa staticnim atributima
		startX += buttons[i]->getBtnSize('x') + 30;  // osvijezi x koordinatu
	}
	// postavljanje icone Businessa
	icon.loadFromFile(texture);
	BusinessImg.setTexture(icon);
	BusinessImg.setPosition(50, startY);

	// osvijezi pozicijske atribute
	startX = 120;
	startY += 90;
}

Business::~Business()
{   // destruktor brise dinamicki alocirane gumbove
	for (int i = 0; i < 3; i++) {
		delete buttons[i];
		buttons[i] = 0;
	}
}

// FUNKCIJONALNOST....
void Business::unlock()
{   // otkljucaj Business
	if (activate == 0) activate = 1;
	wallet -= unlock_price;
	updateBtnTxt(0, 1, 0);
	unlockedBusinesses += 1;
}

void Business::upgrade()
{	// povecaj profit Businessa
	wallet -= upgrade_price;
	upgrade_price *= 1.07;
	multiplier *= 1.06;
	lvl += 1;
	updateBtnTxt(1, 1, 0);
}

void Business::add_to_wallet()
{
	wallet += profit * multiplier;
}

void Business::automate(double& worldTime)
{	// promjeni stanje automatske zarade
	state = 1;
	autoBusinesses += 1;
	timer = worldTime;
	wallet -= automate_price;
	updateBtnTxt(0, 0, 1);
}

void Business::updateTimer(double& worldTime)
{	// Automatizirana zarada
	if (worldTime - timer > profit_time) { // ako je proslo odredeno vrijeme...
		add_to_wallet();				   // dodaj
		timer = worldTime;				   // updateaj timer
	}
}


// Crtanje na ekran
void Business::drawBusiness(sf::RenderWindow& window)
{	// Ispis texta u buttonsa
	window.draw(BusinessImg);
	desc.drawDescription(window);
	for (auto button : buttons)
		button->drawButton(window);
}

void Business::updateBtnTxt(bool index1, bool index2, bool index3)
{	// Azuriranje texta na buttonu, argumenti su booleani koji oznacavaju koji text se mora promjenit
	if (index1 != 0)
		buttons[0]->setNewString("Upgrade:\n-" + std::to_string(upgrade_price));
	if (index2 != 0)
		buttons[1]->setNewString("+" + std::to_string(profit * multiplier) + "\n lvl: " + std::to_string(lvl));
	if (index3 != 0)
		buttons[2]->setNewString("AUTO: ON");
}

void Business::updateBtnColor(int index, sf::Color btnBgColor)
{	// Azuriranje boje buttona, argumenti su index koji oznacava button u vektoru i boja u koju se mijenja
	buttons[index]->setBackgroundColor(btnBgColor);
}

// setter
void Business::setNewBtnTxt(int index, std::string txt)
{	// Postavljanje texta na gumbu, argumenti su index koji oznacava button u vektoru i text u koji se mjenja
	buttons[index]->setNewString(txt);
}

// getteri
bool Business::getOneBtn(int index, sf::RenderWindow& window)
{	// vraca 1 ako je mis na buttonu 0 ako nije
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
{	// vraca 1 ako je business automatiziran
	return state;
}

bool Business::getStatus()
{	// vraca 1 ako je business kupljen
	return activate;
}

// staticne var
double Business::wallet = 0;			// Ukupan novac
int Business::unlockedBusinesses = 0;	// broj kupljenih businessa
int Business::autoBusinesses = 0;		// broj automatiziranih businessa
float Business::startX = 120;			// pecatak x koordinate
float Business::startY = 110;			// pecatak y koordinate