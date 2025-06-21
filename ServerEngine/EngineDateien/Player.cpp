#include "Player.h"

using namespace std;
TPlayer::TPlayer() {};
TPlayer::TPlayer(int id, int budget, int position) { this->ID = id; this->Budget = budget; this->Position = position; };
TPlayer::TPlayer( int id, int name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, 
                vector<int> gekauftestrassen, vector<int> gebautehaeser) 
                { this->ID = id; this->Name = name; this->Budget = budget; this->Position = position; 
                    this->ImGefaengnis = imgefaengnis, this->GefaengnisRunden = gefaengnisrunden, this->GekaufteStrassen = gekauftestrassen, 
                    this->GebauteHaeuser = gebautehaeser; };

TPlayer::~TPlayer() {};

int TPlayer::Score() {
	int score = this->getBudget();
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		score += _boardarr[i].Price;
	}
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		score += 50;
	}
	return score;
}
void TPlayer::getData() {
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
void TPlayer::setID(int id) { this->ID = id; }
int TPlayer::getID() { return this->ID; }
string TPlayer::getName() { return this->Name; }
void TPlayer::setName(string name) { this->Name = name; }

void TPlayer::setHuman(int h) { this->Human = h; }
int TPlayer::getHuman() { return this->Human; }

int TPlayer::getBudget() { return this->Budget; }
void TPlayer::setBudget(int b) { this->Budget = b; }

int TPlayer::getPosition() { return this->Position; }
void TPlayer::setPosition(int p) { this->Position = p; }
void TPlayer::incPosition(int p) {
	this->Position += p;
	if (this->Position == 30) { // Ins Gefängnis gehen
		this->insGefaengnis();
	}
	if (this->Position >= 40) { // Eine Runde Übergangen
		this->Position -= 40;
	}
}

int TPlayer::getWurfel(int index) { return this->Wurfelzahl[index]; }
void TPlayer::setWurfel(int w, int index) { this->Wurfelzahl[index] = w; }
void TPlayer::Wurfelmechn() {
	for (int i = 0; i < 2; i++) {
		this->setWurfel(this->wurfeln(), i);
	}
	this->setAugenzahl(this->getWurfel(0) + this->getWurfel(1));
	this->incPosition(this->getAugenzahl());
}
void TPlayer::Paschwurf() {
	for (int i = 0; i < 2; i++) {
		this->setWurfel(1, i);
	}
	this->setAugenzahl(this->getWurfel(0) + this->getWurfel(1));
	this->incPosition(this->getAugenzahl());
}
int TPlayer::getAugenzahl() { return this->getWurfel(0)+ this->getWurfel(1); }
void TPlayer::setAugenzahl(int a) { this->Augenzahl = a; }
int TPlayer::getPaschCounter() { return this->PaschCounter; }
void TPlayer::setPaschCounter(int p) { this->PaschCounter = p; }
void TPlayer::incPaschCounter() {
	this->PaschCounter++;
	if (this->PaschCounter >= 3) {
		this->insGefaengnis();
	}
}

void TPlayer::insGefaengnis() {
	this->ImGefaengnis = true;
	this->GefaengnisRunden = 1;
	this->Position = 10; // Gefängnisfeld
}
void TPlayer::decGefaengnisRunden() {
	if (this->GefaengnisRunden > 0) {
		this->GefaengnisRunden--;
	}
	if (this->GefaengnisRunden == 0) {
		this->ImGefaengnis = false;
	}
}
bool TPlayer::imGefaengnis() { return this->ImGefaengnis; }

mt19937 Zufall(time(nullptr));
int TPlayer::wurfeln() {
	int Zufallszahl;
	Zufallszahl = (Zufall() % 6) + 1;
	return Zufallszahl;
}

bool TPlayer::paschcheck() {
	if (this->Wurfelzahl[0] == this->Wurfelzahl[1]) { return true; }
	return false;
}

void TPlayer::bezahle(int betrag) {
	if (betrag != -1) {
		if (this->Budget - betrag >= 0) {
			this->Budget -= betrag;
		}
		else {
			cout << "Sie koennen nicht bezahlen" << endl;
		}
	}
}
void TPlayer::erhalte(int betrag) { this->Budget += betrag; }
bool TPlayer::istPleite() { if (this->Budget <= 0) { return true; } return false; }
void TPlayer::geheZu(int feld) {
	if (feld < 0 || feld >= 40) {
		return;					// Ungültiges Feld, nichts tun	
	}
	this->Position = feld;
}

void TPlayer::addStrasse(int strasse) {
	//if (this->GekaufteStrassen.size() == 0) {
	//	GekaufteStrassen.push_back(strasse);
	//}
	bool owned = false;
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		owned |= (this->GekaufteStrassen[i] == strasse);
	}
	if (!owned) {
		GekaufteStrassen.push_back(strasse);
	}
	cout << "Spieler " << this->ID+1 << " hat " << _boardarr[strasse].Name << " gekauft.\n";
} 
void TPlayer::deleteStrasse(int strasse) {

	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			this->GekaufteStrassen.erase(this->GekaufteStrassen.begin() + i);
			cout << "Strasse " << _boardarr[strasse].Name<< " wurde von Spieler " << this->ID << " verkauft.\n";
			return;
		}
	}
	cout << "Diese Strasse besitzen Sie nicht.\n";
}
bool TPlayer::besitztStrasse(int strasse) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			return true;
		}
	}
	return false;
}
bool TPlayer::besitztStrassenSet() {
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

	// Überprüfen ob Spieler ein Set vollständig hat
	for (int i = 0; i < sets.size(); i++) {
		int zaehler = 0;

		for (int j = 0; j < sets[i].size(); j++) {
			// Prüfen ob die Straße in GekaufteStrassen ist
			for (int k = 0; k < this->GekaufteStrassen.size(); k++) {
				if (this->GekaufteStrassen[k] == sets[i][j]) {
					zaehler++;
					break; // weiter zur nächsten Straße im Set
				}
			}
		}

		// Wenn Anzahl gefundener Straßen gleich der Anzahl im Set ist
		if (zaehler == sets[i].size()) {
			return true;
		}
	}

	// Wenn kein vollständiges Set gefunden wurde
	return false;
}

int TPlayer::handel(int r, int preowner) {
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
bool TPlayer::kaufeStrasseVon(TPlayer* von, int strasse, int betrag) {
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
bool TPlayer::verkaufeStrasseAn(TPlayer* zielspieler, int strasse, int betrag) {
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

void TPlayer::baueHaus(int strasse) {
	if (this->besitztStrassenSet()) {
		this->GebauteHaeuser.push_back(strasse);
		cout << "Ein Haus wurde auf " << strasse << " gebaut.\n";
	}
	else {
		cout << "Sie besitzen die Strasse " << strasse << " nicht.\n";
	}
}
void TPlayer::verkaufeHaus(int strasse) {
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			this->GebauteHaeuser.erase(this->GebauteHaeuser.begin() + i);
			cout << "Ein Haus auf " << strasse << " wurde verkauft.\n";
			return;
		}
	}
	cout << "Sie besitzen kein Haus auf " << strasse << ".\n";
}
int TPlayer::anzahlHaeuserAuf(int strasse) {
	int count = 0;
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			count++;
		}
	}
	return count;
}

vector<string> TPlayer::getGekObjNamen() {
	vector<string> temp;
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		temp.push_back(_boardarr[this->GekaufteStrassen[i]].Name);
	}
	return temp;
}
vector<string> TPlayer::getGebObjNamen() {
	vector<string> temp;
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		temp.push_back(_boardarr[this->GebauteHaeuser[i]].Name);
	}
	return temp;
}

int TPlayer::getGekObjAnz() { return this->GekaufteStrassen.size(); }
int TPlayer::getGebObjAnz() { return this->GebauteHaeuser.size(); }

cpu_player1::cpu_player1() : TPlayer() {}

// cpu to player
int cpu_player1::handel(Map& gameMap, int cpuID, int totalPlayers, std::vector<TPlayer*>& p) {
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
	int bud = getBudget();
	if ((offer >= propPrice * (acceptThresholdPercent / 100.0))) {
		std::cout << "CPU" << id << "akzeptiert das Angebot von " << offer /*<< "' (Schwelle: " << acceptThresholdPercent << "%).\n"*/;
		return true;
	}
	else {
		std::cout << "CPU" << id << "lehnt das Angebot von " << offer;/*<< "' ab (Schwelle: " << acceptThresholdPercent << "%).\n";*/
		return false;
	}
}

// buy street
bool cpu_player1::tryBuyStreet(Map& gameMap, std::vector<TPlayer*>& p) {
	int price = gameMap.getPropertyPrice(getPosition());
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