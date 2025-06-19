#include "Player.h"
void UNITTEST() {
	int number_cpu_level_1 = 2, number_human_players = 2;
	vector<player*> p;

	// Spieler anlegen
	for (int i = 0; i < number_human_players; ++i) {
		p.push_back(new player());
		p[i]->setID(i);
		p[i]->setHuman(HUMAN);
	}

	for (int i = 0; i < number_cpu_level_1; ++i) {
		p.push_back(new cpu_player1());
		p[number_human_players + i]->setID(number_human_players + i);
		p[number_human_players + i]->setHuman(CPU1);
	}

	// Testwerte zuweisen: Budget und Strassen
	p[0]->setBudget(1000);
	p[0]->addStrasse(1);
	p[0]->addStrasse(3);

	p[1]->setBudget(1000);
	p[1]->addStrasse(6);

	p[2]->setBudget(1000);
	p[2]->addStrasse(8);

	p[3]->setBudget(1000);
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
				cout << "\n1:\t zufaelliges Wuerfeln\n";
				cout << "2:\t pasch Wuerfeln\n";
				cout << "3:\t Strasse an anderen Spieler verkaufen\n";
				cout << "4:\t Strasse von anderem Spieler kaufen\n";
				cin >> k;

				switch (k) {

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
					cout << "Handels-Menue\n";
					cout << "Welche Strasse moechten Sie anbieten?\n";
					int strasse;
					cin >> strasse;

					if (!p[current_player]->besitztStrasse(strasse)) {
						cout << "Diese Strasse besitzen Sie nicht!\n";
						break;
					}

					cout << "An welchen Spieler verkaufen? (ID eingeben)\n";
					int zielID;
					cin >> zielID;
					if (zielID < 0 || zielID >= p.size() || zielID == current_player) {
						cout << "Ungueltige Spieler-ID.\n";
						break;
					}

					cout << "Zu welchem Preis verkaufen?\n";
					int betrag;
					cin >> betrag;

					bool erfolg = p[current_player]->verkaufeStrasseAn(p[zielID], strasse, betrag);
					if (erfolg) {
						cout << "Handel abgeschlossen.\n";
					}
					else {
						cout << "Handel nicht erfolgreich.\n";
					}
					break;
				}

				case '4': {
					cout << "Kauf-Menue\n";
					cout << "Von welchem Spieler moechten Sie eine Strasse kaufen? (ID eingeben)\n";
					int vonID;
					cin >> vonID;
					if (vonID < 0 || vonID >= p.size() || vonID == current_player) {
						cout << "Ungueltige Spieler-ID.\n";
						break;
					}

					cout << "Welche Strasse moechten Sie kaufen?\n";
					int strasse;
					cin >> strasse;

					if (!p[vonID]->besitztStrasse(strasse)) {
						cout << "Der Spieler besitzt diese Strasse nicht!\n";
						break;
					}

					cout << "Zu welchem Preis moechten Sie kaufen?\n";
					int betrag;
					cin >> betrag;

					bool erfolg = p[current_player]->kaufeStrasseVon(p[vonID], strasse, betrag);
					if (erfolg) {
						cout << "Handel abgeschlossen.\n";
					}
					else {
						cout << "Handel nicht erfolgreich.\n";
					}
					break;
				}

				default:
					cout << "Wollen Sie keine Aufgabe durchfuehren?" << endl << endl;
					break;
				}
				cout << endl;
				p[current_player]->getData();
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
		players.back()->setBudget(1000);
		players.back()->setPosition(i);
	
	} 
	players[2]->addStrasse(13); //strasse handel test 
	players[2]->addStrasse(14);
	players[3]->addStrasse(16);
	players[3]->addStrasse(18);
	players[4]->addStrasse(19);
	players[4]->addStrasse(21);
	players[5]->addStrasse(23);
	players[5]->addStrasse(24);
	int testPositions[40] = {};
	for (size_t i = 0; i < 40; i++)
	{
		 testPositions[i] = i;
	}

	for (size_t i = 0; i < players.size(); ++i) {
		if (players[i]->getHuman() == CPU1) {
			cpu_player1* cpu = static_cast<cpu_player1*>(players[i]);

			//street buy
			bool bought = cpu->tryBuyStreet(players);
			std::cout << "CPU" << cpu->getID() << (bought ? " bought a street." : " did not buy a street.") << std::endl;

			//Handel cpu to player
			int targetPlayer = -1;
			int propertyIndex = -1;
			int offer = cpu->handel(cpu->getID(), players.size(), players, targetPlayer, propertyIndex);
			if (offer != -1 && targetPlayer != -1 && propertyIndex != -1) {
				std::cout << "CPU" << cpu->getID() << " offers " << offer << " for property "
					<< propertyIndex << " from player " << targetPlayer << std::endl;
				//player to cpu 
				if (players[targetPlayer]->getHuman() == CPU1) {
					cpu_player1* targetCPU = static_cast<cpu_player1*>(players[targetPlayer]);
					bool accepted = targetCPU->acceptTrade(propertyIndex, offer);
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