#pragma once
#include<vector>
#include"Button.h"
#include"Text.h"
class Business{
private:
	bool state, activate;
	double base_value, multiplier, profit, unlock_price, profit_time, upgrade_price;
	int lvl;
	float startX, startY;
	std::vector<Button*> buttons;
	std::string btnText[3] = {"/", "BUY \n" + std::to_string(unlock_price), "AUTO"};
	
	// font je potreban ovdje... ako se koristi u funkciji nestane nakon izlazna iz nje = program ne radi

	sf::Font ArialCyr; // TO DO: check if you have to credit the author
public:
	static int unlockedBusinesses;
	static double wallet; 
	Business();
	Business(double bV, double mult, double prof, double unl, double timePro, float x, float y);
	~Business();


	void automate();
	void add_to_wallet();
	void unlock();
	void work();
	void upgrade();
	void drawBusiness(sf::RenderWindow& window);
	void updateBtnTxt(bool index1 = 0, bool index2 = 0);
	void updateBtnColor(int index, sf::Color btnBgColor);

	void setNewBtnTxt(int index, std::string txt);

	bool getOneBtn(int index, sf::RenderWindow& window);
	double getUpgradePrice();
	double getTotalProfit();
	double getUnlockPrice();
	bool getState();
	bool getStatus();
};

