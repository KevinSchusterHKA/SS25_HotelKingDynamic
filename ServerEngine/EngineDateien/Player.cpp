#include "Player.h"
using namespace std;
TPlayer::TPlayer() {};
TPlayer::TPlayer(int id, int budget, int position) { this->ID = id; this->Budget = budget; this->Position = position; };
TPlayer::TPlayer(int id, string name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeser) { this->ID = id; this->Name = name; this->Budget = budget; this->Position = position; this->ImGefaengnis = imgefaengnis, this->GefaengnisRunden = gefaengnisrunden, this->GekaufteStrassen = gekauftestrassen, this->GebauteHaeuser = gebautehaeser; };

TPlayer::~TPlayer() {};

int TPlayer::Score(int runde, int anzGekGebObj, Map& map) {
	int score = this->getBudget();

	// Wert aller gekauften Straßen / Felder
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		int feldNr = this->GekaufteStrassen[i];
		score += getPreisStrasse(feldNr, map);
	}

	// Wert aller gebauten Häuser (Hauspreis des Feldes)
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		int feldNr = this->GebauteHaeuser[i];
		score += getPreisHaus(feldNr, map);
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
		cout << LUT(strasse) << ", ";
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
int TPlayer::getAugenzahl() { return this->Wurfelzahl[0] + this->Wurfelzahl[1]; }
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
	if (betrag >= 0) {
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

	// Prüfen ob das Feld eine Straße ist
	if (_boardarr[strasse].Type != TypeStreet) {
		cout << "Feld " << LUT(strasse) << " ist keine Strasse und kann nicht gekauft werden.\n";
		return;
	}

	// Prüfen ob Spieler die Straße bereits besitzt
	for (int s = 0; s < this->GekaufteStrassen.size(); s++) {
		if (s == strasse) {
			cout << "Strasse " << LUT(strasse) << " gehoert dir bereits.\n";
			return;
		}
	}

	// Falls nicht, hinzufügen
	GekaufteStrassen.push_back(strasse);
	cout << "Strasse " << LUT(strasse) << " wurde von Spieler " << this->ID << " gekauft.\n";
}

void TPlayer::deleteStrasse(int strasse) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			this->GekaufteStrassen.erase(this->GekaufteStrassen.begin() + i);
			cout << "Strasse " << LUT(strasse) << " wurde von Spieler " << this->ID << " verkauft.\n";
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

bool TPlayer::istStrassenSetHandelbar(int feld, vector<TPlayer*>& spielerListe) {
	int farbe = _boardarr[feld].Color;
	for (int i = 0; i < 40; ++i) {
		if (_boardarr[i].Type == TypeStreet && _boardarr[i].Color == farbe) {
			for (TPlayer* p : spielerListe) {
				if (p->anzahlHaeuserAuf(i) > 0) {
					return false;
				}
			}
		}
	}
	return true;
}

bool TPlayer::Handeln(vector<TPlayer*>& spielerListe, int feld, int angebot) {
	// Prüfen ob Käufer genug Budget hat
	if (this->getBudget() < angebot) {
		cout << "Du hast nicht genug Budget fuer dieses Angebot." << endl;
		return false;
	}
	// Prüfen ob Käufer die Straße bereits besitzt
	if (this->besitztStrasse(feld)) {
		cout << "Du besitzt diese Strasse bereits!" << endl;
		return false;
	}
	// Verkäufer suchen
	for (TPlayer* verkaufer : spielerListe) {
		if (verkaufer->getID() != this->getID() && verkaufer->besitztStrasse(feld)) {

			// Prüfen ob in der Farbgruppe Häuser stehen
			if (!istStrassenSetHandelbar(feld, spielerListe)) {
				cout << "Handel abgelehnt: In der Farbgruppe von " << LUT(feld)
					<< " stehen noch Haeuser." << endl;
				return false;
			}
			// Käufer bezahlt
			this->bezahle(angebot);

			// Verkäufer erhält Geld
			verkaufer->erhalte(angebot);

			// Straße übertragen
			verkaufer->deleteStrasse(feld);
			this->addStrasse(feld);

			cout << "Handel erfolgreich: Strasse " << LUT(feld) << " von Spieler " << verkaufer->getID() << " gekauft fuer " << angebot << ".\n";
			return true;
		}
	}

	cout << "Kein Verkaeufer fuer diese Strasse gefunden." << endl;
	return false;
}

void TPlayer::baueHaus(int strasse, Map& map) {
	if (map.ownsStreets(this->getID(), strasse)) {
		this->GebauteHaeuser.push_back(strasse);
		cout << "Ein Haus wurde auf " << LUT(strasse) << " gebaut.\n";
	}
	else {
		cout << "Sie besitzen nicht das Set von der " << LUT(strasse) << ".\n";
	}
}
void TPlayer::verkaufeHaus(int strasse) {
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		if (this->GebauteHaeuser[i] == strasse) {
			this->GebauteHaeuser.erase(this->GebauteHaeuser.begin() + i);
			cout << "Ein Haus auf " << LUT(strasse) << " wurde verkauft.\n";
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
		temp.push_back(LUT(this->GekaufteStrassen[i]));
	}
	return temp;
}
vector<string> TPlayer::getGebObjNamen() {
	vector<string> temp;
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		temp.push_back(LUT(this->GebauteHaeuser[i]));
	}
	return temp;
}

int TPlayer::getGekObjAnz() { return this->GekaufteStrassen.size(); }
int TPlayer::getGebObjAnz() { return this->GebauteHaeuser.size(); }

vector<int> TPlayer::getGekObjVector() {
	return this->GekaufteStrassen;
}
vector<int> TPlayer::getGebObjVector() {
	return this->GebauteHaeuser;
}
// cpu to player
int TPlayer::handelcpu(int cpuID, int totalPlayers, std::vector<TPlayer*>& p, int& targetPlayerOut, int& propertyIndexOut, Map& map) {
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

	std::vector<int> ownedProperties = p[targetPlayer]->getGekObjVector();
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
	int offer = (1 + offerPercent / 100.0) * map.getPropertyPrice(propIndex);

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
bool TPlayer::acceptTradecpu(int spaceIndex, int offer, Map& map) {
	int id = getID();
	int propPrice = map.getPropertyPrice(spaceIndex);
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
bool TPlayer::tryBuyStreetcpu(std::vector<TPlayer*>& p, Map& map) {
	int price = map.getPropertyPrice(getPosition());
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
		//std::cout << "CPU" << getID() << " hat nicht genug Geld für die Strasse auf Position " << getPosition() << ".\n";
		return false;
	}


}

//buildhouse for cpu
bool TPlayer::tryBuildHousecpu(std::vector<TPlayer*>& p, Map& map) {
	int myID = getID();
	std::vector<int> myProperties = p[myID]->getGekObjVector();

	for (size_t i = 0; i < myProperties.size(); i++) {
		int propIndex = myProperties[i];
		int colorGroup = colorcheck(myID, propIndex, myProperties);
		if (colorGroup == -1) continue;

		std::vector<int> built = p[myID]->getGebObjVector();

		int minHouses = 6; // max 6-1
		int bestProp = -1;

		for (int j = 0; j < 3 && _streetarr[colorGroup][j] != -1; ++j) {
			int groupProp = _streetarr[colorGroup][j];
			if (groupProp == -1) continue;

			int houseCount = std::count(built.begin(), built.end(), groupProp);
			if (houseCount < minHouses && houseCount < 5) {
				minHouses = houseCount;
				bestProp = groupProp;
			}
		}

		if (bestProp == -1) continue;

		int price = map.getHousePrice(bestProp);
		int maxPrice = this->getBudget() * ((30 + rand() % 11) / 100.0); // 30-40%

		if (price <= maxPrice) {
			bezahle(price);
			this->baueHaus(bestProp, map);
			//std::cout << "CPU " << myID << " builds a house on " << LUT(this->getPosition()) << "\n";
			return true;
		}
	}

	return false;
}


//test ob man  haus bauen darf
int colorcheck(int playerID, int space, std::vector<int>& ownedProperties) {
	int colorGroup = -1;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (_streetarr[i][j] == space) {
				colorGroup = i;
				break;
			}
		}
		if (colorGroup != -1) break;
	}

	for (int i = 0; i < 3; ++i) {
		int prop = _streetarr[colorGroup][i];
		if (prop == -1) continue;
		if (std::find(ownedProperties.begin(), ownedProperties.end(), prop) == ownedProperties.end()) {
			return -1;
		}
	}

	return colorGroup;
}

string LUT(int i) {
	return _boardarr[i].Name;
}

int getPreisStrasse(int i, Map& map) {
	return map.getPropertyPrice(i);
}

int getPreisHaus(int i, Map& map) {
	return map.getHousePrice(i);
}