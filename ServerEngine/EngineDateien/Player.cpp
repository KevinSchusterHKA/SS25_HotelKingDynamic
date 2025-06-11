#include "Player.h"
//#include "CPU_opponent.h"
//######################################################################################################################################Temp
//struct Property {//temp just for test
//	std::string name;
//	int price;
//};
//class Map {//temp just for test
//public:
//	int getPropertyPrice(int pos) {
//		switch (pos) {
//		case 1: return 200;
//		case 3: return 201;
//		case 5: return 202;
//		case 6: return 205;
//		default:
//			std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//			return -1;
//		}
//	}
//	std::vector<int> getOwnedProperties(int playerID) {
//		if (playerID == 0) return { 1, 5 };
//		if (playerID == 1) return { 3 };
//		if (playerID == 2) return { 6 };
//		return {};
//	}
//	int getStreetPrice(int pos) {
//		switch (pos) {
//		case 1:
//			return 200;
//		case 3:
//			return 201;
//		case 5:
//			return 202;
//		case 6:
//			return 205;
//		default:
//			std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//			return -1;
//		}
//	}
//	bool buyStreet(int pos, int playerID) {
//		switch (pos) {
//		case 1:
//			std::cout << "a " << playerID << " kann kaufen\n";
//			return true;
//		case 3:
//			std::cout << "b " << playerID << " kann nicht gekauft\n";
//			return false;
//		case 5:
//			std::cout << "c " << playerID << " kann kaufen\n";
//			return true;
//		case 6:
//			std::cout << "d " << playerID << " kann kaufen\n";
//			return true;
//		default:
//			std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//			return false;
//		}
//	}
//};
//
//std::vector<Property> getTempPropertiesForPlayer(int playerID) {//temp just for test
//	std::vector<Property> props;
//	if (playerID == 0) {
//		props.push_back({ "a0", 350 });
//		props.push_back({ "b0", 400 });
//	}
//	else if (playerID == 1) {
//		props.push_back({ "c1", 60 });
//	}
//	else if (playerID == 2) {
//		props.push_back({ "d2", 150 });
//		props.push_back({ "e2", 200 });
//	}
//	return props;
//}

//######################################################################################################################################Temp
player::player() {};
player::player(int id, int budget, int position) { this->ID = id; this->Budget = budget; this->Position = position; };
player::player(int id, int name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<string> gekauftestrassen, vector<string> gebautehaeser) { this->ID = id; this->Name = name; this->Budget = budget; this->Position = position; this->ImGefaengnis = imgefaengnis, this->GefaengnisRunden = gefaengnisrunden, this->GekaufteStrassen = gekauftestrassen, this->GebauteHaeuser = gebautehaeser; };

player::~player() {};

void player::getData() {
	cout << "Spieler-ID: " << this->ID << endl;
	cout << "Budget: " << this->Budget << endl;
	cout << "Position: " << this->Position << endl;
	cout << "Augenzahl: " << this->Augenzahl << endl;
	cout << "Pasch Counter: " << this->PaschCounter << endl;
	cout << "Im Gefaengnis: " << (this->ImGefaengnis ? "Ja" : "Nein") << endl;
	cout << "Gefaengnis Runden: " << this->GefaengnisRunden << endl;
	cout << "Gekaufte Strassen: ";
	for (const auto& strasse : GekaufteStrassen) {
		cout << strasse << ", ";
	}
	cout << endl << endl;
}
void player::setID(int id)	{ this->ID = id; }
int player::getID()			{ return this->ID; }
string player::getName()			{ return this->Name; }
void player::setName(string name)	{ this->Name = name; }

void player::setHuman(int h) { this->Human = h; }
int player::getHuman() { return this->Human; }

int player::getBudget()			{return this->Budget;}
void player::setBudget(int b)	{this->Budget = b;}

int player::getPosition()		{return this->Position;}
void player::setPosition(int p) {this->Position = p;}
void player::incPosition(int p) {
	this->Position += p;
	if (this->Position >= 40) { // Eine Runde Übergangen
		this->Position -= 40;
	}
}

int player::getWurfel(int index)			{return this->Wurfelzahl[index];}
void player::setWurfel(int w, int index)	{this->Wurfelzahl[index] = w;}
void player::Wurfelmechn() {
	for (int i = 0; i < 2; i++) {
		this->setWurfel(this->wurfeln(), i);
	}
	this->setAugenzahl(this->getWurfel(0) + this->getWurfel(1));
	this->incPosition(this->getAugenzahl());
}
void player::Paschwurf() {
	for (int i = 0; i < 2; i++) {
		this->setWurfel(1, i);
	}
	this->setAugenzahl(this->getWurfel(0)+this->getWurfel(1));
	this->incPosition(this->getAugenzahl());
}

int player::getAugenzahl()			{return this->Augenzahl;}
void player::setAugenzahl(int a)	{this->Augenzahl = a;}

int player::getPaschCounter()		{return this->PaschCounter;}
void player::setPaschCounter(int p) {this->PaschCounter = p;}
void player::incPaschCounter()		{this->PaschCounter++;}

void player::insGefaengnis() {
	this->ImGefaengnis = true;
	this->GefaengnisRunden = 3;
	this->Position = 10; // Gefängnisfeld
}
void player::decGefaengnisRunden() {
	if (this->GefaengnisRunden > 0) {
		this->GefaengnisRunden--;
	}
	if (this->GefaengnisRunden == 0) {
		this->ImGefaengnis = false;
	}
}
bool player::imGefaengnis() { return this->ImGefaengnis; }

mt19937 Zufall(time(nullptr));
int player::wurfeln() {
	int Zufallszahl;
	Zufallszahl = (Zufall() % 6) + 1;
	return Zufallszahl;
}

bool player::paschcheck() {
	if (this->Wurfelzahl[0] == this->Wurfelzahl[1]) {return true;}
	return false;
}

void player::bezahle(int betrag) {
	if(this->Budget - betrag >= 0) {
		this->Budget -= betrag;
	} else {
		cout << "Sie koennen nicht bezahlen" << endl;
	}
}
void player::erhalte(int betrag)	{ this->Budget += betrag; }
bool player::istPleite() { if (this->Budget <= 0) { return true; } return false; }
void player::geheZu(int feld){
	if (feld < 0 || feld >= 40) {
		return;					// Ungültiges Feld, nichts tun	
	}
	this->Position = feld;
}

void player::addStrasse(string strasse) {
	GekaufteStrassen.push_back(strasse);
	cout << "Strasse " << strasse << " wurde von Spieler " << this->ID << " gekauft.\n";
}
void player::deleteStrasse(string strasse) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			this->GekaufteStrassen.erase(this->GekaufteStrassen.begin() + i);
			cout << "Strasse " << strasse << " wurde von Spieler " << this->ID << " verkauft.\n";
			return;
		}
	}
	cout << "Diese Strasse besitzen Sie nicht.\n";
}
bool player::besitztStrasse(string strasse) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			return true;
		}
	}
	return false;
}
int player::handel(string r, int preowner) {
	string Strasse = r;
	int angebot = -1;
	if (preowner != -1) {
		cout << "Sie koennen diese Strasse nicht kaufen, Sie gehoert niemandem.\n";
	}
	else {
		cout << "Wie viel Geld moechten Sie fuer diese Strasse anbieten?\n";
		while (angebot <= 0) {
			cin >> angebot;
			if (angebot <= 0) { cout << "Geben Sie bitte ein gueltiges Angebot an.\n"; }
		}
	}
	return angebot;
}
bool player::verkaufeStrasseAn(player* zielspieler, string strasse, int betrag) {
	if (!this->besitztStrasse(strasse)) {
		cout << "Du besitzt diese Strasse nicht.\n";
		return false;
	}
	cout << "Spieler " << zielspieler->getID() << ", akzeptierst du das Angebot von "
		<< betrag << " für die Strasse " << strasse << "? (j/n)\n";
	char antwort;
	cin >> antwort;
	if (antwort == 'j' || antwort == 'J') {
		this->deleteStrasse(strasse);
		this->setBudget(this->getBudget() + betrag);

		zielspieler->addStrasse(strasse);
		zielspieler->setBudget(zielspieler->getBudget() - betrag);

		cout << "Handel abgeschlossen.\n";
		return true;
	}
	cout << "Handel abgelehnt.\n";
	return false;
}

void player::baueHaus(string strasse) {
	if (this->besitztStrasse(strasse)) {
		this->GebauteHaeuser.push_back(strasse);
		cout << "Ein Haus wurde auf " << strasse << " gebaut.\n";
	}
	else {
		cout << "Sie besitzen die Strasse " << strasse << " nicht.\n";
	}
}
void player::verkaufeHaus(string strasse) {
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			this->GebauteHaeuser.erase(this->GebauteHaeuser.begin() + i);
			cout << "Ein Haus auf " << strasse << " wurde verkauft.\n";
			return;
		}
	}
	cout << "Sie besitzen kein Haus auf " << strasse << ".\n";
}
int player::anzahlHaeuser(string strasse) {
	int count = 0;
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			count++;
		}
	}
	return count;
}
cpu_player1::cpu_player1() : player() {}

// cpu to player
int cpu_player1::handel(Map& gameMap, int cpuID, int totalPlayers, std::vector<player*>& p) {
	if ((rand() % 100) > 5) {
		//std::cout << "CPU entscheidet sich gegen einen Handelsversuch.\n";
		return -1;
	}
	int targetPlayer;
	do {
		targetPlayer = rand() % totalPlayers;
	} while (targetPlayer == cpuID);

	std::vector<int> ownedProperties = gameMap.getOwnedProperties(targetPlayer);
	if (ownedProperties.empty()) {
		//std::cout << "CPU Spieler " << targetPlayer << " besitzt keine Straben.\n";
		return -1;
	}

	int randIndex = rand() % ownedProperties.size();
	int propIndex = ownedProperties[randIndex];

	int minPercent = 5;
	int maxPercent = 15;
	int offerPercent = minPercent + rand() % (maxPercent - minPercent + 1);
	int  offer = (1 + offerPercent / 100.0) * gameMap.getPropertyPrice(propIndex);

	if (offer > p[cpuID]->getBudget()) {
		/*  std::cout << "CPU Kann sich das Angebot von " << offer
			   << "' nicht leisten.\n";*/
		return -1;
	}

	//std::cout << "CPU bietet " << offer << /*" (" << offerPercent << */"% von "
	//    << offer << ") fur '" << prop.name << "' von Spieler " << targetPlayer << ".\n";

	return offer;
}

// player to cpu 
bool cpu_player1::acceptTrade(Map& gameMap, int spaceIndex, int offer) {
	int id = getID();
	int propPrice = gameMap.getPropertyPrice(spaceIndex);
	int acceptThresholdPercent = 90 + (std::rand() % 21);// min of 90% to max of 110% 

	if (offer <= propPrice * (acceptThresholdPercent / 100.0) && offer <= getBudget()) {
		std::cout << "CPU" << id << "akzeptiert das Angebot von " << offer /*<< "' (Schwelle: " << acceptThresholdPercent << "%).\n"*/;
		return true;
	}
	else {
		std::cout << "CPU" << id << "lehnt das Angebot von " << offer;/*<< "' ab (Schwelle: " << acceptThresholdPercent << "%).\n";*/
		return false;
	}
}

// buy street
bool cpu_player1::tryBuyStreet(Map& gameMap, std::vector<player*>& p) {
	int price = gameMap.getStreetPrice(getPosition());
	int id = getID();
	int pos = getPosition();
	if (price < 0) {
		//std::cout << "CPU"<< id <<"Kein Kaufmoeglichkeit auf Position " << pos << ".\n";
		return false;
	}

	if (getBudget() >= price) {
		bool success = gameMap.buyStreet(getID(), getBudget());
		if (success) {
			setBudget(getBudget() - price);
			//std::cout << "CPU"<< id << "kauft Strasse auf Position " << pos << " fuer " << price << ".\n";
			return true;
		}
		else {
			std::cout << "CPU" << id << "Kauf auf Position " << pos << " fehlgeschlagen.\n";
		}
	}
	else {
		std::cout << "CPU" << id << " Kein Geld fuer Strasse auf Position " << pos << ".\n";
	}
	return false;
}


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
	p[0]->setBudget(1500);
	p[0]->addStrasse("Berliner Platz");
	p[0]->addStrasse("Hauptstrasse");

	p[1]->setBudget(1200);
	p[1]->addStrasse("Bahnhofstrasse");

	p[2]->setBudget(1000);
	p[2]->addStrasse("Parkallee");

	p[3]->setBudget(800);
	p[3]->addStrasse("Schlossallee");

	// Spielstart
	int current_player = 0;
	while (true) {
		char k;
		cout << "\n\nSpieler " << current_player << " Menue" << endl;
		cout << "1:\t zufaelliges Wuerfeln\n";
		cout << "2:\t pasch Wuerfeln\n";
		cout << "3:\t Strassenhandel\n";
		cout << "4:\t Daten Auslesen\n";
		cin >> k;

		switch (k) {

		case '1': {
			do {
				p[current_player]->Wurfelmechn();
				for (int i = 0; i < 2; i++) {
					cout << "Wuerfel " << i + 1 << ":\t " << p[current_player]->getWurfel(i) << endl;
				}
				cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
				if (p[current_player]->paschcheck()) {
					cout << "PASCH!\n";
					p[current_player]->incPaschCounter();
					if (p[current_player]->getPaschCounter() >= 2) {
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
			break;
		}
		
		case '2': {
			do {
				p[current_player]->Paschwurf();
				for (int i = 0; i < 2; i++) {
					cout << "Wuerfel " << i + 1 << ":\t " << p[current_player]->getWurfel(i) << endl;
				}
				cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
				if (p[current_player]->paschcheck()) {
					cout << "PASCH!\n";
					p[current_player]->incPaschCounter();
					if (p[current_player]->getPaschCounter() >= 2) {
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
			break;
		}
		
		case '3': {
			cout << "Handels-Menue\n";
			cout << "Welche Strasse moechten Sie anbieten?\n";
			cin.ignore(); // Puffer leeren
			string strasse;
			getline(cin, strasse);

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
			cout << "Waehle den Spieler\n";
			int x;
			cin >> x;
			p[x]->getData();
			break;
		}


		default:
			cout << "Wollen Sie keine Aufgabe durchfuehren?" << endl << endl;
			break;
		}
		current_player = (current_player + 1) % p.size();
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

	for (int i = 0; i < 5; ++i) {
		players.push_back(new cpu_player1());
		players.back()->setID(i + 2);
		players.back()->setHuman(CPU1);
		players.back()->setBudget(1000);
		players.back()->setPosition(i + 3);
	}

	Map gameMap;
	int testPositions[] = { 400, 10, 0 };   

	for (size_t i = 0; i < players.size(); ++i) {
		if (players[i]->getHuman() == CPU1) {
			cpu_player1* cpu = static_cast<cpu_player1*>(players[i]);
			cpu->tryBuyStreet(gameMap, players);
			cpu->handel(gameMap, cpu->getID(), players.size(), players);
			int pos = testPositions[i % (sizeof(testPositions) / sizeof(testPositions[0]))];
			int offer = 390;
			cpu->acceptTrade(gameMap, pos, offer);
			std::cout << "##############" << std::endl;
		}
	}
}





//int main() {
//	UNITTEST_cpu();
//	UNITTEST();
//	return 0;
//}

