#include "Logger.h"

int main() {

	Logger log(1, "Fabian", "2025-06-10_00-22-50");
	log.playerRollingDice(3, 4);

	log.newRound();
	log.newPlayer("Fabian");
	log.playerRollingDice(3, 4);
	log.playerRollingDice(4, 4);
	log.playerOnStreet("straﬂe");
	log.playerOnStreet("weg");
	return 0;
}