#include "Logger.h"

int main() { 

	Logger log;
	
	log.newGame();
	log.newRound();
	log.newPlayer("Spieler1");
	log.playerRollingDice(4, 4);
	log.playerOnStreet("straﬂe");
	log.playerRollingDice(3, 4);
	log.playerOnStreet("straﬂe2");
	log.playerBuysObject("straﬂe2");
	log.newPlayer("Spieler2");
	log.playerRollingDice(5, 4);
	log.playerOnStreet("straﬂe6");
	log.newRound();

	Logger logn(1, "Spieler2");
	return 0;
}