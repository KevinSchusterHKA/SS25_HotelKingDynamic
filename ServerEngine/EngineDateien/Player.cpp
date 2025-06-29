#include "Player.h"
using namespace std;
TPlayer::TPlayer() {};
TPlayer::TPlayer(int id, int budget, int position) { this->ID = id; this->Budget = budget; this->Position = position; };
TPlayer::TPlayer(int id, string name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeuser) { this->ID = id; this->Name = name; this->Budget = budget; this->Position = position; this->ImGefaengnis = imgefaengnis, this->GefaengnisRunden = gefaengnisrunden, this->GekaufteStrassen = gekauftestrassen, this->GebauteHaeuserSpeicherFormat = gebautehaeuser; };
TPlayer::TPlayer(int id, string name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeuserspeicher, vector<int> gebautehaeuser) {
	this->ID = id; this->Name = name; this->Budget = budget; this->Position = position; this->ImGefaengnis = imgefaengnis, this->GefaengnisRunden = gefaengnisrunden, this->GekaufteStrassen = gekauftestrassen, this->GebauteHaeuserSpeicherFormat = gebautehaeuserspeicher, this->GebauteHaeuser = gebautehaeuser;
};

TPlayer::~TPlayer() {};

int TPlayer::Score(vector<TPlayer*>& spielerListe) {
	int score = this->getBudget();

	// Wert aller gekauften Straßen / Felder
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		int feldNr = this->GekaufteStrassen[i];
		score += streetpricewith2(feldNr, spielerListe);
	}

	// Wert aller gebauten Häuser (Hauspreis des Feldes)
	for (int i = 0; i < this->GebauteHaeuser.size(); i++) {
		int feldNr = this->GebauteHaeuser[i];
		score += housepricewith2(feldNr, spielerListe);
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
	if (this->Position == 30 && this->getGefaengnisFreiKarte() == 0) { // Ins Gefängnis gehen
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

int TPlayer::getGefaengnisFreiKarte()			{ return this->GefaengnisFreiKarte; }
void TPlayer::setGefaengnisFreiKarte(int k)		{ this->GefaengnisFreiKarte = k; }
void TPlayer::insGefaengnis() {
	if (this->GefaengnisFreiKarte == 0) {
		this->ImGefaengnis = true;
		this->GefaengnisRunden = 2;
		this->Position = 10; // Gefängnisfeld
	}
	else {
		this->setGefaengnisFreiKarte(this->getGefaengnisFreiKarte() - 1);
	}
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
	//if (betrag >= 0) {
		//if (this->Budget - betrag >= 0) {
			this->Budget -= betrag;
		//}
		//else {
		//	cout << "Sie koennen nicht bezahlen" << endl;
		//}
	//}
}
void TPlayer::erhalte(int betrag) { this->Budget += betrag; }
bool TPlayer::istPleite() { if (this->Budget <= 0) { return true; } return false; }

void TPlayer::addStrasse(int strasse, string& Nachricht) {

	// Prüfen ob das Feld eine Straße ist
	if (_boardarr[strasse].Type != TypeStreet) {
		Nachricht = "Feld " + LUT(strasse) + " ist keine Strasse und kann nicht gekauft werden.";
		return;
	}

	// Prüfen ob Spieler die Straße bereits besitzt
	for (int s = 0; s < this->GekaufteStrassen.size(); s++) {
		if (GekaufteStrassen[s] == strasse) {
			Nachricht = "Strasse " + LUT(strasse) + " gehoert dir bereits.";
			return;
		}
	}

	// Falls nicht, hinzufügen
	GekaufteStrassen.push_back(strasse);
	Nachricht = "Strasse " + LUT(strasse) + " wurde von Spieler " + to_string(this->ID) + " gekauft.";
}
void TPlayer::deleteStrasse(int strasse, string& Nachricht) {
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			this->GekaufteStrassen.erase(this->GekaufteStrassen.begin() + i);
			Nachricht = "Strasse " + LUT(strasse) + " wurde von Spieler " + to_string(this->ID) + " verkauft.";
			return;
		}
	}
	Nachricht = "Diese Strasse besitzen Sie nicht.";
}
void TPlayer::verkaufeStrasse(int strasse, vector<TPlayer*>& spielerListe, string& Nachricht) {
	if (this->WieVieleHaueserAufSet(strasse) > 0) {
		Nachricht = "Sie koennen keine Strasse verkaufen, auf der Sie Haeuser gebaut haben.";
		return;
	}
	for (int i = 0; i < this->GekaufteStrassen.size(); i++) {
		if (this->GekaufteStrassen[i] == strasse) {
			this->GekaufteStrassen.erase(this->GekaufteStrassen.begin() + i);
			this->erhalte(int(streetpricewith2(strasse, spielerListe) / 2)); // Geld für Strasse zurückerhalten (aber nur die Hälfte des Preises)
			Nachricht = "Die Strasse " + LUT(strasse) + " wurde verkauft.";
			return;
		}
	}
	Nachricht = "Sie besitzen nicht die Strasse " + LUT(strasse) + ".";
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
int TPlayer::WieVieleHaueserAufSet(int feld) {
	int count = 0;
	int farbe = _boardarr[feld].Color;
	for (int i = 0; i < 40; ++i) {
		if (_boardarr[i].Type == TypeStreet && _boardarr[i].Color == farbe) {
			if (this->anzahlHaeuserAuf(i)) {
				count++;
			}
		}
	}
	return count;
}

int TPlayer::Handeln(vector<TPlayer*>& spielerListe, int feld, int angebot, string& Nachricht, Map& map) {
	// Prüfen ob Käufer genug Budget hat
	if (this->getBudget() < angebot) {
		Nachricht = "Du hast nicht genug Budget fuer dieses Angebot.";
		return -1;
	}
	// Prüfen ob Käufer die Straße bereits besitzt
	if (this->besitztStrasse(feld)) {
		Nachricht = "Du besitzt diese Strasse bereits!";
		return -1;
	}
	// Verkäufer suchen
	for (TPlayer* verkaufer : spielerListe) {

		if (verkaufer->besitztStrasse(feld)) {

			// Prüfen ob in der Farbgruppe Häuser stehen
			if (!istStrassenSetHandelbar(feld, spielerListe)) {
				Nachricht = "Handel abgelehnt: In der Farbgruppe von " + LUT(feld) + " stehen noch Haeuser.";
				return -1;
			}

			// Käufer bezahlt
			this->bezahle(angebot);

			// Verkäufer erhält Geld
			verkaufer->erhalte(angebot);

			// Straße übertragen
			verkaufer->deleteStrasse(feld, Nachricht);
			this->addStrasse(feld, Nachricht);
			map.setOwner(verkaufer->getID(), this->getID(), feld);

			Nachricht = "Handel erfolgreich: Strasse " + LUT(feld) + " von Spieler " + to_string(verkaufer->getID()) + " gekauft fuer " + to_string(angebot) + ".";
			return verkaufer->getID();
		}
	}

	Nachricht = "Kein Verkaeufer fuer diese Strasse gefunden.";
	return -1;
}

int TPlayer::baueHaus(int strasse, vector<TPlayer*>& spielerListe, string& Nachricht) {
	// Prüfen ob das Feld eine Straße ist
	if (_boardarr[strasse].Type != TypeStreet) {
		Nachricht = "Feld " + LUT(strasse) + " ist keine Strasse und kann nicht gekauft werden.";
		return -1;
	}
	if (this->anzahlHaeuserAuf(strasse) < 5) {
		if (AlleStrassenVerkauft(spielerListe)) {
			if (this->getBudget() - housepricewith2(strasse, spielerListe) >= 0) {
				// Haus bauen
				this->GebauteHaeuser.push_back(strasse);
				this->GebauteHaeuserSpeicherFormat[strasse]++;
				this->bezahle(housepricewith2(strasse, spielerListe));
				Nachricht = "Ein Haus wurde auf " + LUT(strasse) + " gebaut.";
				return 1;
			}
			else {
				Nachricht = "Sie haben nicht genug Geld, um ein Haus auf " + LUT(strasse) + " zu bauen.";
				return -1;
			}
		}
		else {
			Nachricht = "Es wurden noch nicht alle Strassen verkauft.";
			return -1;
		}
	}
	else {
		Nachricht = "Sie koennen kein weiteres Haus auf " + LUT(strasse) + " bauen, da bereits 5 Haeuser vorhanden sind.";
		return -1;
	}
}
void TPlayer::verkaufeHaus(int strasse, int anz, vector<TPlayer*>& spielerListe, string& Nachricht) {
	if (anz <= 0 || anz >= 6) {
		Nachricht = "Ungueltige Anzahl von Haeusern.";
		return; // Ungültige Anzahl von Häusern
	}
	/*if (anz == 0) {
		this->verkaufeStrasse(strasse, spielerListe, Nachricht);
		return;
	}*/
	int verkauft = 0;

	for (int i = 0; i < this->GebauteHaeuser.size(); ) {
		if (this->GebauteHaeuser[i] == strasse) {
			this->GebauteHaeuser.erase(this->GebauteHaeuser.begin() + i);
			this->GebauteHaeuserSpeicherFormat[strasse]--;
			this->erhalte(int(housepricewith2(strasse, spielerListe) / 2));
			verkauft++;
			if (verkauft == anz) {
				break;
			}
		}
		else {
			i++;
		}
	}

	if (verkauft == 0) {
		Nachricht = "Sie besitzen kein Haus auf " + LUT(strasse) + ".";
	}
	else {
		Nachricht = to_string(verkauft) + " Haeuser auf " + LUT(strasse) + " wurden verkauft.";
	}
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
	vector<int> sortedStrassen = this->GekaufteStrassen;
	insertionsort(sortedStrassen, 0); // 0 = aufsteigend

	vector<string> temp;
	for (int i = 0; i < sortedStrassen.size(); i++) {
		temp.push_back(LUT(sortedStrassen[i]));
	}
	return temp;
}
vector<string> TPlayer::getGebObjNamen() {
	vector<string> temp;
	for (int i = 0; i < this->GebauteHaeuserSpeicherFormat.size(); i++) {
		if (GebauteHaeuserSpeicherFormat[i] != 0) {
			if (GebauteHaeuserSpeicherFormat[i] == 5) {
				temp.push_back(LUT(i) + ", Hotel");
			}
			temp.push_back(LUT(i)+", Anz: "+to_string(GebauteHaeuserSpeicherFormat[i]));
		}
	}
	return temp;
}

int TPlayer::getGekObjAnz() { return this->GekaufteStrassen.size(); }
int TPlayer::getGebObjAnz() { 
	int count = 0;
	for(int i = 0; i < this->GebauteHaeuserSpeicherFormat.size(); i++) {
		count += this->GebauteHaeuserSpeicherFormat[i];
	}
	return count;
}

vector<int> TPlayer::getGekObjVector() {
	return this->GekaufteStrassen;
}
vector<int> TPlayer::getHaueser() {
	return this->GebauteHaeuserSpeicherFormat;
}
vector<int> TPlayer::getGebObjVector() {
	return this->GebauteHaeuser;
}
// cpu to player
int TPlayer::handelcpu(int cpuID, int totalPlayers, vector<TPlayer*>& p, int& targetPlayerOut, int& propertyIndexOut, Map& map) {
	if ((rand() % 101) > 35) {
		//std::cout << "CPU entscheidet sich gegen einen Handelsversuch.\n";
		targetPlayerOut = -1;
		propertyIndexOut = -1;
		return -1;
	}
	int totalOwnedStreets = 0;
	for (std::size_t i = 0; i < p.size(); ++i) {
		if (p[i] != nullptr) {
			totalOwnedStreets += p[i]->getGekObjAnz();
		}
	} 
	if (totalOwnedStreets==0)
	{
		return -1;
	}
	std::vector<int> targetPlayervec;
	for (int i = 0; i < totalPlayers; ++i) {
		if (i != cpuID && (p[i]->getGekObjAnz() > 0)) {
			targetPlayervec.push_back(i);
		}
	}
	if (targetPlayervec.size()==0)
	{
		return -1;
	}
	int randomplayer = rand() % targetPlayervec.size();
	int targetPlayer = targetPlayervec[randomplayer];
	std::vector<int> ownedProperties = p[targetPlayer]->getGekObjVector();
	int randIndex = rand() % ownedProperties.size();
	int propIndex = ownedProperties[randIndex];
	if (anzahlHaeuserAuf(propIndex) > 0)
	{
		return -1;
	}
	int minPercent = 5;
	int maxPercent = 15;
	int offerPercent = minPercent + rand() % (maxPercent - minPercent + 1);
	int offer = (1 + offerPercent / 100.0) * streetpricewith2(propIndex, p);

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
bool TPlayer::acceptTradecpu(int spaceIndex, int offer, int kaufer, vector<TPlayer*>& spielerListe, Map& map, string& Nachricht) {
	int propPrice = streetpricewith2(spaceIndex, spielerListe);
	int acceptThresholdPercent = 90 + (std::rand() % 21);// min of 90% to max of 110% 
	int bud = getBudget();
	if ((offer >= propPrice * (acceptThresholdPercent / 100.0)) && (spielerListe[kaufer]->getBudget() - offer >= 0)) {
		//std::cout << "CPU" << id << "akzeptiert das Angebot von " << offer /*<< "' (Schwelle: " << acceptThresholdPercent << "%).\n"*/;
		if (WieVieleHaueserAufSet(spaceIndex) > 0) {
			return false;
		}
		this->erhalte(offer);
		this->deleteStrasse(spaceIndex, Nachricht);
		spielerListe[kaufer]->addStrasse(spaceIndex, Nachricht);
		spielerListe[kaufer]->bezahle(offer);
		map.setOwner(this->getID(), kaufer, spaceIndex);
		return true;
	}
	else {
		//std::cout << "CPU" << id << "lehnt das Angebot von " << offer;/*<< "' ab (Schwelle: " << acceptThresholdPercent << "%).\n";*/
		return false;
	}
}

// buy street
bool TPlayer::tryBuyStreetcpu(Map& map) {
	int price = map.getPropertyPrice(getPosition());
	int id = getID();
	int pos = getPosition();
	if (price <= 0) {
		//std::cout << "CPU"<< id <<"Kein Kaufmoeglichkeit auf Position " << pos << ".\n";
		return false;
	}
	if ((getBudget() * (20 + rand() % 66)) / 100.0 >= price) { //nur wenn price ist 20% - 65% das budgets
		return true;
	}
	else {
		//std::cout << "CPU" << getID() << " hat nicht genug Geld für die Strasse auf Position " << getPosition() << ".\n";
		return false;
	}


}

//buildhouse for cpu
bool TPlayer::tryBuildHousecpu(vector<TPlayer*>& player, Map& map, string& Nachricht) {
	int myID = getID();
	std::vector<int> myProperties = player[myID]->getGekObjVector();
 	std::vector<int> builtobj = player[myID]->getGebObjVector();
	bool built = false;

	for (int colorGroup = 0; colorGroup < 8; ++colorGroup) {
		bool ownsAll = true;
		for (int i = 0; i < 3; ++i) {
			int prop = _streetarr[colorGroup][i];
			if (prop == -1) continue;
			if (std::find(myProperties.begin(), myProperties.end(), prop) == myProperties.end()) {
				ownsAll = false;
				break;
			}
		}

		if (!ownsAll) continue;

		int minHouses = 6; // 5+1
		int bestProp = -1;

		for (int i = 0; i < 3; ++i) {
			int groupProp = _streetarr[colorGroup][i];
			if (groupProp == -1) continue;

			int houseCount = std::count(builtobj.begin(), builtobj.end(), groupProp);
			if (houseCount < minHouses && houseCount < 5) {
				minHouses = houseCount;
				bestProp = groupProp;
			}
		}

		if (bestProp == -1) continue;
		int price = housepricewith2(bestProp, player);
		int maxPrice = player[myID]->getBudget() * ((30 + rand() % 11) / 100.0); // 30–40%

		if (price <= maxPrice) {
			bezahle(price);
			player[myID]->baueHaus(bestProp, player, Nachricht);
			built = true;
			break;
		}
	}
	return built;
}
//take zug for cpu
bool TPlayer::takebahn(vector<TPlayer*>& player, int costofbahn, int bahnpos,int nextbahnpos,int anzahlplayers, Map& map) {
	if (bahnpos==-1)
	{
		return false;
	}
	int myID = this->getID();
	int weightedprob = rand() % (player[myID]->getAugenzahl());
 	if (player[myID]->getBudget() < costofbahn)
		return false;
	for (int i = 0; i < anzahlplayers; ++i) {
		if (player[i]->getID() == myID) continue;
		if (player[i]->besitztStrasse(bahnpos+weightedprob))
			return false;
	}
	bool free_street = true;

	if (map.getPropertyPrice(nextbahnpos + weightedprob)>0)
	{
		free_street = true;

	}
	else {
		free_street = false;

	}
	if (!player[myID]->besitztStrasse(nextbahnpos + weightedprob) && free_street) {
		return true;
	}

	return false;
}
//cpu verkauf haus 
void TPlayer::cpuHausVerkauf(vector<TPlayer*>& spielerListe, Map& map, string& Nachricht) {
	int benoetigt = 100 + (rand() % 200);
	if (getBudget() >= benoetigt) return;
	//cout << "CPU [" << getName() << "] hat nur $" << getBudget() << " und braucht $" << benoetigt << ".\n";
	std::vector<int> meineStrassen = getGekObjVector();
	for (int space : meineStrassen) {
		int hausAnzahl = anzahlHaeuserAuf(space);
		if (hausAnzahl >= 1) {
			for (int i = 0; i < hausAnzahl; ++i) {
				int geld = housepricewith2(space, spielerListe)/2;
				erhalte(geld);
				this->GebauteHaeuserSpeicherFormat[space]--;
				std::vector<int>::iterator  it = std::find(GebauteHaeuser.begin(), GebauteHaeuser.end(), space);
				if (it != GebauteHaeuser.end()) GebauteHaeuser.erase(it);
				//cout << "Verkaufe Haus auf \"" << map.getName(space)<< "\" für $" << geld << ".\n";
				if (getBudget() >= benoetigt) return;
			}
		}
	}
	//for (int id : meineStrassen) {
	//	if (besitztStrasse(id)) {
	//		if (getBudget() >= benoetigt) return;
	//		verkaufeStrasse(id, spielerListe, Nachricht);
	//		//cout << "→ Verkaufe Haus auf \"" << map.getName(id)<< "\" für $" << map.getPropertyPrice(id) << ".\n";
	//	}
	//}
	//cout << "CPU [" << getName() << "] konnte nicht genug Geld aufbringen.\n";
}


//test ob man  haus bauen darf
bool AlleStrassenVerkauft(vector<TPlayer*>& spielerListe) {
	int totalOwnedStreets = 0;
	for (std::size_t i = 0; i < spielerListe.size(); ++i) {
		if (spielerListe[i] != nullptr) {
			totalOwnedStreets += spielerListe[i]->getGekObjAnz();
		}
	}
	if (totalOwnedStreets == 22) {
		return true;
	}
	else {
		return false;
	}
}
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
string LUT(int i) { return _boardarr[i].Name; }
void insertionsort(vector<int>& vec, int Sortierrichtung) {
	for (int i = 1; i < vec.size(); ++i) {
		int temp = vec[i];
		int j = i - 1;

		while (j >= 0 &&
			((Sortierrichtung == 0 && vec[j] > temp) ||			// Aufsteigend
				(Sortierrichtung == 1 && vec[j] < temp))) {		// Absteigend
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = temp;
	}
}

int streetpricewith2(int position, vector<TPlayer*>& spielerListe) {
	int basePrice = -1;

	switch (position) {
	case 1:  basePrice = 60;  break; // Oberreut
	case 3:  basePrice = 80;  break; // Gruenwinkel
	case 6:  basePrice = 100; break; // Neureut
	case 8:  basePrice = 100; break; // Waldstadt
	case 9:  basePrice = 120; break; // Hagsfeld
	case 11: basePrice = 140; break; // Palmbach
	case 13: basePrice = 140; break; // Stupferich
	case 14: basePrice = 160; break; // Bergdoerfer
	case 16: basePrice = 180; break; // Rintheim
	case 18: basePrice = 180; break; // Rueppurr
	case 19: basePrice = 180; break; // Muehlburg
	case 21: basePrice = 220; break; // Nordstadt
	case 23: basePrice = 220; break; // Nordweststadt
	case 24: basePrice = 240; break; // Weststadt
	case 26: basePrice = 260; break; // Durlach
	case 27: basePrice = 260; break; // Suedstadt
	case 29: basePrice = 280; break; // Oststadt
	case 31: basePrice = 300; break; // Suedweststadt
	case 32: basePrice = 300; break; // Innenstadt Ost
	case 34: basePrice = 320; break; // Innenstadt West
	case 37: basePrice = 350; break; // Geigersberg
	case 39: basePrice = 400; break; // Schlossplatz
	default:
		return -1;
	}
	int totalOwnedStreets = 0;
	for (std::size_t i = 0; i < spielerListe.size(); ++i) {
		if (spielerListe[i] != nullptr) {
			totalOwnedStreets += spielerListe[i]->getGekObjAnz();
		}
	}

	double finalPrice = basePrice * std::pow(1.02, totalOwnedStreets);
	return static_cast<int>(finalPrice);
}
int housepricewith2(int position, vector<TPlayer*>& spielerListe) {
	int basePrice = -1;

	switch (position) {
	case 1:  basePrice = 50; break;  // Oberreut
	case 3:  basePrice = 50; break;  // Gruenwinkel
	case 6:  basePrice = 50; break;  // Neureut
	case 8:  basePrice = 50; break;  // Waldstadt
	case 9:  basePrice = 50; break;  // Hagsfeld
	case 11: basePrice = 100; break; // Palmbach
	case 13: basePrice = 100; break; // Stupferich
	case 14: basePrice = 100; break; // Bergdoerfer
	case 16: basePrice = 100; break; // Rintheim
	case 18: basePrice = 100; break; // Rueppurr
	case 19: basePrice = 100; break; // Muehlburg
	case 21: basePrice = 150; break; // Nordstadt
	case 23: basePrice = 150; break; // Nordweststadt
	case 24: basePrice = 150; break; // Weststadt
	case 26: basePrice = 150; break; // Durlach
	case 27: basePrice = 150; break; // Suedstadt
	case 29: basePrice = 150; break; // Oststadt
	case 31: basePrice = 200; break; // Suedweststadt
	case 32: basePrice = 200; break; // Innenstadt Ost
	case 34: basePrice = 200; break; // Innenstadt West
	case 37: basePrice = 200; break; // Geigersberg
	case 39: basePrice = 200; break; // Schlossplatz
	default:
		return -1;
	}
	int totalOwnedStreets = 0;
	for (std::size_t i = 0; i < spielerListe.size(); ++i) {
		if (spielerListe[i] != nullptr) {
			totalOwnedStreets += spielerListe[i]->getGebObjAnz();
		}
	}
	double finalPrice = basePrice * pow(1.02, totalOwnedStreets);
	return static_cast<int>(finalPrice);
}
vector<int> SpeicherZuInternFormat(vector<int> gebauteHaueserSpeicher) {
	vector<int> temp;
	for (int i = 0; i < gebauteHaueserSpeicher.size(); i++) {
		if (i != 0) {
			for (int j = 0; j < gebauteHaueserSpeicher[i]; j++) {
				temp.push_back(i);
			}
		}
	}
	return temp;
}

int WemGehoertStrasse(int feld, vector<TPlayer*>& spielerListe) {
	for (TPlayer* p : spielerListe) {
		if (p->besitztStrasse(feld)) {
			return p->getID();
		}
	}
	return -1; // Keine Straße gefunden
}
int LUT_nextBahn(int bahnpost) {

	switch (bahnpost) {
		//KIT Campus|-> Durlach BF
	case 5:
		return 25;
		break;
		//Zuendhuetle|-> Entenfang
	case 12:
		return 28;
		break;
		//Europaplatz|-> Hauptbahnhof
	case 15:
		return 35;
		break;
		//Durlach BF|-> KIT Campus
	case 25:
		return 5;
		break;
		//Entenfang|-> Zuendhuetle
	case 28:
		return 12;

		break;
		//Hauptbahnhof | ->Europaplatz
	case 35:
		return 15;
		break;
	default:
		return -1;
	}
}

