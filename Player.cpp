#include "Player.h"
using namespace std;
player::player() {};
player::player(int id, int budget, int position) { this->ID = id; this->Budget = budget; this->Position = position; };
player::player(int id, int name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeser) { this->ID = id; this->Name = name; this->Budget = budget; this->Position = position; this->ImGefaengnis = imgefaengnis, this->GefaengnisRunden = gefaengnisrunden, this->GekaufteStrassen = gekauftestrassen, this->GebauteHaeuser = gebautehaeser; };

player::~player() {};

int player::Score(int runde, int anzGekGebObj) {
	int score = this->getBudget();

	// Wert aller gekauften Straﬂen / Felder
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		int feldNr = this->GekaufteStrassen[i];
		score += getPreisStrasse(feldNr, anzGekGebObj);
	}

	// Wert aller gebauten H‰user (Hauspreis des Feldes)
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		int feldNr = this->GebauteHaeuser[i];
		score += getPreisHaus(feldNr, anzGekGebObj);
	}

	return score;
}
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
void player::setID(int id) { this->ID = id; }
int player::getID() { return this->ID; }
string player::getName() { return this->Name; }
void player::setName(string name) { this->Name = name; }

void player::setHuman(int h) { this->Human = h; }
int player::getHuman() { return this->Human; }

int player::getBudget() { return this->Budget; }
void player::setBudget(int b) { this->Budget = b; }

int player::getPosition() { return this->Position; }
void player::setPosition(int p) { this->Position = p; }
void player::incPosition(int p) {
	this->Position += p;
	if (this->Position == 30) { // Ins Gef‰ngnis gehen
		this->insGefaengnis();
	}
	if (this->Position >= 40) { // Eine Runde ‹bergangen
		this->Position -= 40;
	}
}

int player::getWurfel(int index) { return this->Wurfelzahl[index]; }
void player::setWurfel(int w, int index) { this->Wurfelzahl[index] = w; }
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
	this->setAugenzahl(this->getWurfel(0) + this->getWurfel(1));
	this->incPosition(this->getAugenzahl());
}
int player::getAugenzahl() { return this->Wurfelzahl[0]+ this->Wurfelzahl[1]; }
void player::setAugenzahl(int a) { this->Augenzahl = a; }
int player::getPaschCounter() { return this->PaschCounter; }
void player::setPaschCounter(int p) { this->PaschCounter = p; }
void player::incPaschCounter() {
	this->PaschCounter++;
	if (this->PaschCounter >= 3) {
		this->insGefaengnis();
	}
}

void player::insGefaengnis() {
	this->ImGefaengnis = true;
	this->GefaengnisRunden = 1;
	this->Position = 10; // Gef‰ngnisfeld
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
	if (this->Wurfelzahl[0] == this->Wurfelzahl[1]) { return true; }
	return false;
}

void player::bezahle(int betrag) {
	if (betrag >= 0) {
		if (this->Budget - betrag >= 0) {
			this->Budget -= betrag;
		}
		else {
			cout << "Sie koennen nicht bezahlen" << endl;
		}
	}
}
void player::erhalte(int betrag) { this->Budget += betrag; }
bool player::istPleite() { if (this->Budget <= 0) { return true; } return false; }
void player::geheZu(int feld) {
	if (feld < 0 || feld >= 40) {
		return;					// Ung¸ltiges Feld, nichts tun	
	}
	this->Position = feld;
}

void player::addStrasse(int strasse) {
	if (this->GekaufteStrassen.size() == 0) {
		GekaufteStrassen.push_back(strasse);
	}
	else
	{
		for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
			if (this->GekaufteStrassen[i] == strasse) {
			}
			else {
				GekaufteStrassen.push_back(strasse);
			}
		}
	}
	cout << "Strasse " << LUT(strasse) << " wurde von Spieler " << this->ID << " gekauft.\n";
}
void player::deleteStrasse(int strasse) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			this->GekaufteStrassen.erase(this->GekaufteStrassen.begin() + i);
			cout << "Strasse " << LUT(strasse) << " wurde von Spieler " << this->ID << " verkauft.\n";
			return;
		}
	}
	cout << "Diese Strasse besitzen Sie nicht.\n";
}
bool player::besitztStrasse(int strasse) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			return true;
		}
	}
	return false;
}
bool player::besitztStrassenSet() {
	// Sets als Array von Vektoren definieren
	vector<int> set1 = { 1, 3 };
	vector<int> set2 = { 6, 8, 9 };
	vector<int> set3 = { 11, 13, 14 };
	vector<int> set4 = { 16, 18, 19 };
	vector<int> set5 = { 21, 23, 24 };
	vector<int> set6 = { 26, 27, 29 };
	vector<int> set7 = { 31, 32, 34 };
	vector<int> set8 = { 37, 39 };

	// Liste mit allen Sets
	vector<vector<int>> sets;
	sets.push_back(set1);
	sets.push_back(set2);
	sets.push_back(set3);
	sets.push_back(set4);
	sets.push_back(set5);
	sets.push_back(set6);
	sets.push_back(set7);
	sets.push_back(set8);

	// ‹berpr¸fen ob Spieler ein Set vollst‰ndig hat
	for (int i = 0; i < sets.size(); i++) {
		int zaehler = 0;

		for (int j = 0; j < sets[i].size(); j++) {
			// Pr¸fen ob die Straﬂe in GekaufteStrassen ist
			for (int k = 0; k < this->GekaufteStrassen.size(); k++) {
				if (this->GekaufteStrassen[k] == sets[i][j]) {
					zaehler++;
					break; // weiter zur n‰chsten Straﬂe im Set
				}
			}
		}

		// Wenn Anzahl gefundener Straﬂen gleich der Anzahl im Set ist
		if (zaehler == sets[i].size()) {
			return true;
		}
	}

	// Wenn kein vollst‰ndiges Set gefunden wurde
	return false;
}
int player::handel(int r, int preowner) {
	int Strasse = r;
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
bool player::kaufeStrasseVon(player* von, int strasse, int betrag) {
	if (!von->besitztStrasse(strasse)) {
		cout << "Der Spieler besitzt diese Strasse nicht.\n";
		return false;
	}
	cout << "Spieler " << von->getID() << ", akzeptierst du das Angebot von "
		<< betrag << " fuer die Strasse " << strasse << "? (j/n)\n";
	char antwort;
	cin >> antwort;
	if (antwort == 'j' || antwort == 'J') {
		von->deleteStrasse(strasse);
		von->setBudget(von->getBudget() + betrag);

		this->addStrasse(strasse);
		this->setBudget(this->getBudget() - betrag);

		cout << "Handel abgeschlossen.\n";
		return true;
	}
	cout << "Handel abgelehnt.\n";
	return false;
}
bool player::verkaufeStrasseAn(player* zielspieler, int strasse, int betrag) {
	if (!this->besitztStrasse(strasse)) {
		cout << "Du besitzt diese Strasse nicht.\n";
		return false;
	}
	cout << "Spieler " << zielspieler->getID() << ", akzeptierst du das Angebot von "
		<< betrag << " f¸r die Strasse " << strasse << "? (j/n)\n";
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

void player::baueHaus(int strasse) {
	if (this->besitztStrassenSet()) {
		this->GebauteHaeuser.push_back(strasse);
		cout << "Ein Haus wurde auf " << LUT(strasse) << " gebaut.\n";
	}
	else {
		cout << "Sie besitzen nicht das Set von der " << LUT(strasse) << ".\n";
	}
}
void player::verkaufeHaus(int strasse) {
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			this->GebauteHaeuser.erase(this->GebauteHaeuser.begin() + i);
			cout << "Ein Haus auf " << LUT(strasse) << " wurde verkauft.\n";
			return;
		}
	}
	cout << "Sie besitzen kein Haus auf " << strasse << ".\n";
}
int player::anzahlHaeuserAuf(int strasse) {
	int count = 0;
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			count++;
		}
	}
	return count;
}

vector<string> player::getGekObjNamen() {
	vector<string> temp;
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		temp.push_back(LUT(this->GekaufteStrassen[i]));
	}
	return temp;
}
vector<string> player::getGebObjNamen() {
	vector<string> temp;
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		temp.push_back(LUT(this->GebauteHaeuser[i]));
	}
	return temp;
}

int player::getGekObjAnz() { return this->GekaufteStrassen.size(); }
int player::getGebObjAnz() { return this->GebauteHaeuser.size(); }

cpu_player1::cpu_player1() : player() {}
vector<int> player::getGekaufteStrassen() {
	return this->GekaufteStrassen;
}
vector<int> player::getGebauteHaeuser() {
	return this->GebauteHaeuser;
}
// cpu to player
int cpu_player1::handel(int cpuID, int totalPlayers, std::vector<player*>& p, int& targetPlayerOut, int& propertyIndexOut) {
	if ((rand() % 101) > 15) {
		//std::cout << "CPU entscheidet sich gegen einen Handelsversuch.\n";
		targetPlayerOut = -1;
		propertyIndexOut = -1;
		return -1;
	}
	int targetPlayer;
	do {
		targetPlayer = rand() % totalPlayers;
	} while (targetPlayer == cpuID);

	std::vector<int> ownedProperties = p[targetPlayer]->getGekaufteStrassen();
	if (ownedProperties.empty()) {
		//std::cout << "CPU Spieler " << targetPlayer << " besitzt keine Straben.\n";
		targetPlayerOut = -1;
		propertyIndexOut = -1;
		return -1;
	}

	int randIndex = rand() % ownedProperties.size();
	int propIndex = ownedProperties[randIndex];

	int minPercent = 5;
	int maxPercent = 15;
	int offerPercent = minPercent + rand() % (maxPercent - minPercent + 1);
	int offer = (1 + offerPercent / 100.0) * getPreisStrasse(propIndex,0);

	if (offer > p[cpuID]->getBudget()) {
		/*  std::cout << "CPU Kann sich das Angebot von " << offer
			   << "' nicht leisten.\n";*/
		return -1;
	}

	//std::cout << "CPU bietet " << offer << /*" (" << offerPercent << */"% von "
	//    << offer << ") fur '" << prop.name << "' von Spieler " << targetPlayer << ".\n";
	targetPlayerOut = targetPlayer;
	propertyIndexOut = propIndex;
	return offer;
}

// player to cpu 
bool cpu_player1::acceptTrade(int spaceIndex, int offer) {
	int id = getID();
	int propPrice = getPreisStrasse(spaceIndex,0);
	int acceptThresholdPercent = 90 + (std::rand() % 21);// min of 90% to max of 110% 
	int bud = getBudget();
	if ((offer >= propPrice * (acceptThresholdPercent / 100.0))) {
		//std::cout << "CPU" << id << "akzeptiert das Angebot von " << offer /*<< "' (Schwelle: " << acceptThresholdPercent << "%).\n"*/;
		return true;
	}
	else {
		//std::cout << "CPU" << id << "lehnt das Angebot von " << offer;/*<< "' ab (Schwelle: " << acceptThresholdPercent << "%).\n";*/
		return false;
	}
}

// buy street
bool cpu_player1::tryBuyStreet(std::vector<player*>& p) {
	int price = getPreisStrasse(getPosition(),0);
	int id = getID();
	int pos = getPosition();
	if (price <= 0) {
		//std::cout << "CPU"<< id <<"Kein Kaufmoeglichkeit auf Position " << pos << ".\n";
		return false;
	}
	if ((getBudget() * (20 + rand() % 66)) / 100.0 >= price) { //nur wenn price ist 20% - 65% das budgets
		this->bezahle(price);
		this->addStrasse(getPosition());
		return true;
	}
	else {
		//std::cout << "CPU" << getID() << " hat nicht genug Geld f¸r die Strasse auf Position " << getPosition() << ".\n";
		return false;
	}
}




string LUT(int i) {
	switch (i) {
	case 1:  return "Kaiserstrasse";
	case 3:  return "Erbprinzenstrasse";
	case 6:  return "Ettlinger_Tor";
	case 8:  return "Amalienstrasse";
	case 9:  return "Waldstrasse";
	case 11: return "Durlacher_Allee";
	case 13: return "Rueppurrer_Strasse";
	case 14: return "Moltkestrasse";
	case 16: return "Herrenstrasse";
	case 18: return "Kronenstrasse";
	case 19: return "Kriegsstrasse";
	case 21: return "Kanalweg";
	case 23: return "Sophienstrasse";
	case 24: return "Karlstrasse";
	case 26: return "Tullastrasse";
	case 27: return "Hardtstrasse";
	case 29: return "Rintheimer_Strasse";
	case 31: return "Wolfartsweierer_Strasse";
	case 32: return "Nordendstrasse";
	case 34: return "Lorenzstrasse";
	case 37: return "Kuehler_Krug";
	case 39: return "Europaplatz";
	default: return "Unbekannte_Strasse";
	}
}

int getPreisStrasse(int i, int AnzahlGekGebObj) {
	switch (i) {
	case 1:  return int(60*pow(1.02, AnzahlGekGebObj));
	case 3:  return int(60 * pow(1.02, AnzahlGekGebObj));
	case 6:  return int(100 * pow(1.02, AnzahlGekGebObj));
	case 8:  return int(100 * pow(1.02, AnzahlGekGebObj));
	case 9:  return int(120 * pow(1.02, AnzahlGekGebObj));
	case 11: return int(140 * pow(1.02, AnzahlGekGebObj));
	case 13: return int(140 * pow(1.02, AnzahlGekGebObj));
	case 14: return int(160 * pow(1.02, AnzahlGekGebObj));
	case 16: return int(180 * pow(1.02, AnzahlGekGebObj));
	case 18: return int(180 * pow(1.02, AnzahlGekGebObj));
	case 19: return int(200 * pow(1.02, AnzahlGekGebObj));
	case 21: return int(220 * pow(1.02, AnzahlGekGebObj));
	case 23: return int(220 * pow(1.02, AnzahlGekGebObj));
	case 24: return int(240 * pow(1.02, AnzahlGekGebObj));
	case 26: return int(260 * pow(1.02, AnzahlGekGebObj));
	case 27: return int(260 * pow(1.02, AnzahlGekGebObj));
	case 29: return int(280 * pow(1.02, AnzahlGekGebObj));
	case 31: return int(300 * pow(1.02, AnzahlGekGebObj));
	case 32: return int(300 * pow(1.02, AnzahlGekGebObj));
	case 34: return int(320 * pow(1.02, AnzahlGekGebObj));
	case 37: return int(350 * pow(1.02, AnzahlGekGebObj));
	case 39: return int(400 * pow(1.02, AnzahlGekGebObj));
	default: return 0;
	}
}
int getPreisHaus(int i, int AnzahlGekGebObj) {
}




