#include "Player.h"
void UNITTEST() {
	int AnzPlayer = 4;
	vector<player*> p;
	Map map; // Temporäre Map-Instanz, um die Funktionalität zu testen

	// Spieler anlegen
	for (int i = 0; i < AnzPlayer; ++i) {
		p.push_back(new player());
		p[i]->setID(i);
		p[i]->setHuman(HUMAN);
		p[i]->setBudget(1000);
	}
	// Testwerte zuweisen: Budget und Strassen
	p[0]->addStrasse(0);
	p[0]->addStrasse(1);
	p[0]->addStrasse(3);
	p[1]->addStrasse(6);
	p[2]->addStrasse(8);
	p[3]->addStrasse(9);

	// Spielstart
	int current_player = 0;
	int runde = 1;

	while (true) {
		char k;
		cout << "\n\n####################################################################################################\n";
		cout << "Runde " << runde << " , Spieler " << current_player << " Menue" << endl;


		if (p[current_player]->imGefaengnis()) {
			cout << "Sie sind im Gefaengnis und koennen nicht wuerfeln.\n";
			p[current_player]->decGefaengnisRunden();
		}
		else {
			bool hatGewuerfelt = false;
			while (!hatGewuerfelt) {
				cout << "\n0:\t Alle Spieler Infos\n";
				cout << "1:\t zufaelliges Wuerfeln\n";
				cout << "2:\t pasch Wuerfeln\n";
				cout << "3:\t Strasse von anderem Spieler kaufen\n";
				cout << "4:\t Haus bauen\n";
				
				cin >> k;

				switch (k) {

				case '0': {
					for (int i = 0; i < p.size(); ++i) {
						p[i]->getData();
					}
					cout << endl;
					break;
				}

				case '1': {
					do {
						p[current_player]->Wurfelmechn();
						for (int i = 0; i < 2; i++) { cout << "Wuerfel " << i + 1 << ":\t " << p[current_player]->getWurfel(i) << endl; }
						cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
						if (p[current_player]->paschcheck()) {
							cout << "PASCH!\n";
							p[current_player]->incPaschCounter();
							if (p[current_player]->getPaschCounter() >= 3) {
								p[current_player]->insGefaengnis();
								cout << "Sie sind im Gefaengnis!\n";
								p[current_player]->setPaschCounter(0);
								break;
							}
							else {
								cout << "Sie duerfen nochmal wuerfeln!\n";
							}
						}
						else {
							p[current_player]->setPaschCounter(0);
							break;
						}
					} while (true);
					hatGewuerfelt = true;
					break;
				}

				case '2': {
					do {
						p[current_player]->Paschwurf();
						for (int i = 0; i < 2; i++) { cout << "Wuerfel " << i + 1 << ":\t " << p[current_player]->getWurfel(i) << endl; }
						cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
						if (p[current_player]->paschcheck()) {
							cout << "PASCH!\n";
							p[current_player]->incPaschCounter();
							if (p[current_player]->getPaschCounter() >= 3) {
								p[current_player]->insGefaengnis();
								cout << "Sie sind im Gefaengnis!\n";
								p[current_player]->setPaschCounter(0);
								break;
							}
							else {
								cout << "Sie duerfen nochmal wuerfeln!\n";
							}
						}
						else {
							p[current_player]->setPaschCounter(0);
							break;
						}
					} while (true);
					hatGewuerfelt = true;
					break;
				}

				case '3': {
					int feld, angebot;
					char c;
					cout << "Welche Strasse wollen Sie kaufen? (0-39) \n";
					cin >> feld;
					cout << "Wie viel wollen Sie dafuer bezahlen? \n";
					cin >> angebot;
					cout << "Nehmen Sie das Angebot von " << angebot << " an? (j/n) \n";
					cin >> c;
					if (c == 'j' || c == 'J') {
						p[current_player]->Handeln(p, feld, angebot);
					}
					else {
						cout << "Handel abgelehnt.\n";
					}
					break;
				}
				case '4': {
					int feld;
					cout << "Auf welcher Strasse wollen Sie bauen? (0-39) \n";
					cin >> feld;
					p[current_player]->baueHaus(feld, map);
				}
					
				default:
					cout << "Wollen Sie keine Aufgabe durchfuehren?" << endl << endl;
					break;
				}
				cout << endl;
				cout << "####################################################################################################\n";

			}

		}
		current_player = (current_player + 1) % p.size();
		if (current_player == 0) runde++;
	}
}
void UNITTEST_cpu() {
	std::srand(std::time(nullptr));  // random seed 
	std::vector<player*> players;

	for (int i = 0; i < 2; ++i) {
		players.push_back(new player());
		players.back()->setID(i);
		players.back()->setHuman(HUMAN);
		players.back()->setBudget(1000);
		players.back()->setPosition(i);
	}

	for (int i = 0; i < 10; ++i) {
		players.push_back(new cpu_player1());
		players.back()->setID(i + 2);
		players.back()->setHuman(CPU1);
		players.back()->setBudget(10000000);
		players.back()->setPosition(i);
	
	} 
	players[2]->addStrasse(1); //strasse handel test und farbe set 
	players[2]->addStrasse(3);
	players[3]->addStrasse(11);
	players[3]->addStrasse(13);
	players[3]->addStrasse(14);
	players[4]->addStrasse(21);
	players[5]->addStrasse(23);
	players[5]->addStrasse(24);
	Map map;//map 
	int testPositions[40] = {};
	for (size_t i = 0; i < 40; i++)
	{
		 testPositions[i] = i;
	}


	for (size_t i = 0; i < players.size(); ++i) {
		if (players[i]->getHuman() == CPU1) {
			cpu_player1* cpu = static_cast<cpu_player1*>(players[i]);
			//build house test
			for (int build = 0; build < 6; ++build) {
				bool built = cpu->tryBuildHouse(players, map);
				std::cout << "try " << build + 1 << ": CPU" << cpu->getID()
					<< (built ? " built a house." : " did not build a house.") << std::endl;
			}

			//street buy
			bool bought = cpu->tryBuyStreet(players, map);
			std::cout << "CPU" << cpu->getID() << (bought ? " bought a street." : " did not buy a street.") << std::endl;

			//Handel cpu to player
			int targetPlayer = -1;
			int propertyIndex = -1;
			int offer = cpu->handel(cpu->getID(), players.size(), players, targetPlayer, propertyIndex, map);
			if (offer != -1 && targetPlayer != -1 && propertyIndex != -1) {
				std::cout << "CPU" << cpu->getID() << " offers " << offer << " for property "
					<< propertyIndex << " from player " << targetPlayer << std::endl;
				//player to cpu 
				if (players[targetPlayer]->getHuman() == CPU1) {
					cpu_player1* targetCPU = static_cast<cpu_player1*>(players[targetPlayer]);
					bool accepted = targetCPU->acceptTrade(propertyIndex, offer, map);
					std::cout << "CPU" << targetCPU->getID() << (accepted ? " accepted the trade." : " rejected the trade.") << std::endl;
				}
				else {
					std::cout << "Human player " << targetPlayer << " needs to decide on the offer." << std::endl;
				}
			}
			else {
				std::cout << "CPU" << cpu->getID() << " did not make a trade offer." << std::endl;
			}

			std::cout << "##############" << std::endl;
		}
	}
}


int main() {
	UNITTEST_cpu();
	UNITTEST();
	return 0;
}

