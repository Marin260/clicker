#pragma once
#include<vector>
#include"Button.h"
#include"Text.h"
class Business{
private:
	bool state, activate;
	double base_value, multiplier, profit, unlock_price, profit_time, upgrade_price, timer, automate_price;
	int lvl;
	float startX, startY;
	std::vector<Button*> buttons;
	std::string btnText[3] = {"/", "BUY \n" + std::to_string(unlock_price), "AUTO Earning\n-" + std::to_string(automate_price) };
	
	// font je potreban ovdje... ako se koristi u funkciji nestane nakon izlazna iz nje = program ne radi

	sf::Font ArialCyr; // TO DO: check if you have to credit the author
public:
	static int unlockedBusinesses, autoBusinesses;
	static double wallet; 
	Business();
	Business(double bV, double mult, double prof, double unl, double timePro, float x, float y, float toAuto);
	~Business();


	void automate(double& worldTime);
	void add_to_wallet();
	void unlock();
	void upgrade();
	void drawBusiness(sf::RenderWindow& window);
	void updateBtnTxt(bool index1 = 0, bool index2 = 0, bool index3 = 0);
	void updateBtnColor(int index, sf::Color btnBgColor);

	void updateTimer(double& worldTime);

	void setNewBtnTxt(int index, std::string txt);

	bool getOneBtn(int index, sf::RenderWindow& window);
	double getUpgradePrice();
	double getTotalProfit();
	double getUnlockPrice();
	double getAutoPrice();
	bool getState();
	bool getStatus();
};

