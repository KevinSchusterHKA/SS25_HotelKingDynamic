#include "Logger.h"

int main() { 

	Logger log;
	
	log.newGame();
	log.newRound();
	log.newPlayer("Spieler1");
	log.playerRollingDice(4, 4);
	log.playerOnStreet("stra�e");
	log.playerRollingDice(3, 4);
	log.playerOnStreet("stra�e2");
	log.playerBuysObject("stra�e2");
	log.newPlayer("Spieler2");
	log.playerRollingDice(5, 4);
	log.playerOnStreet("stra�e6");
	log.newRound();

	Logger logn(1, "Spieler2");
	return 0;
}