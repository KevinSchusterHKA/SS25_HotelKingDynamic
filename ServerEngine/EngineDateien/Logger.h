#pragma once
#include <string>


class Logger {
public:
	Logger();
	Logger(int round,std::string actualPlayer);
	void newRound();
	void newPlayer(std::string player);
	void playerRollingDice(int first, int second);
	void playerOnStreet(std::string streetName);
	void playerInPrison();
	void onChestField(std::string event);
	void onEventField(std::string event);
	void playerBuysObject(std::string object, int price);
	void playerBuildsBuilding(std::string building);
	void playerMoney(std::string player, int money);
	void payTax();
	void newGame();
	

private:
	int round;
	std::string actualPlayer;
	std::string path;
	void writeToFile(std::string text);

};