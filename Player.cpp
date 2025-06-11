#include "Player.h"
#include "CPU_opponent.h"

player::player() {};
player::player(int id, int budget, int position) { this->ID = id; this->Budget = budget; this->Position = position; };
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
void player::setID(int id) { this->ID = id; }
int player::getID() { return this->ID; }

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
		cout << "Du besitzt diese Straße nicht.\n";
		return false;
	}
	cout << "Spieler " << zielspieler->getID() << ", akzeptierst du das Angebot von "
		<< betrag << " für die Straße " << strasse << "? (j/n)\n";
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

//void UNITTEST() {
//	int number_cpu_level_1 = 2, number_human_players = 2;
//	vector<player*> p;
//
//	// Spieler anlegen
//	for (int i = 0; i < number_human_players; ++i) {
//		p.push_back(new player());
//		p[i]->setID(i);
//		p[i]->setHuman(HUMAN);
//	}
//
//	for (int i = 0; i < number_cpu_level_1; ++i) {
//		p.push_back(new cpu_player1());
//		p[number_human_players + i]->setID(number_human_players + i);
//		p[number_human_players + i]->setHuman(CPU1);
//	}
//
//	// Testwerte zuweisen: Budget und Strassen
//	p[0]->setBudget(1500);
//	p[0]->addStrasse("Berliner Platz");
//	p[0]->addStrasse("Hauptstrasse");
//
//	p[1]->setBudget(1200);
//	p[1]->addStrasse("Bahnhofstrasse");
//
//	p[2]->setBudget(1000);
//	p[2]->addStrasse("Parkallee");
//
//	p[3]->setBudget(800);
//	p[3]->addStrasse("Schlossallee");
//
//	// Spielstart
//	int current_player = 0;
//	while (true) {
//		char k;
//		cout << "\n\nSpieler " << current_player << " Menue" << endl;
//		cout << "1:\t zufaelliges Wuerfeln\n";
//		cout << "2:\t pasch Wuerfeln\n";
//		cout << "3:\t Strassenhandel\n";
//		cout << "4:\t Daten Auslesen\n";
//		cin >> k;
//
//		switch (k) {
//
//		case '1':
//			do {
//				p[current_player]->Wurfelmechn();
//				for (int i = 0; i < 2; i++) {
//					cout << "Wuerfel " << i + 1 << ":\t " << p[current_player]->getWurfel(i) << endl;
//				}
//				cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
//				if (p[current_player]->paschcheck()) {
//					cout << "PASCH!\n";
//					p[current_player]->incPaschCounter();
//					if (p[current_player]->getPaschCounter() >= 2) {
//						p[current_player]->insGefaengnis();
//						cout << "Sie sind im Gefaengnis!\n";
//						p[current_player]->setPaschCounter(0);
//						break;
//					}
//					else {
//						cout << "Sie duerfen nochmal wuerfeln!\n";
//					}
//				}
//				else {
//					p[current_player]->setPaschCounter(0);
//					break;
//				}
//			} while (true);
//			break;
//		
//		case '2':
//			do {
//				p[current_player]->Paschwurf();
//				for (int i = 0; i < 2; i++) {
//					cout << "Wuerfel " << i + 1 << ":\t " << p[current_player]->getWurfel(i) << endl;
//				}
//				cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
//				if (p[current_player]->paschcheck()) {
//					cout << "PASCH!\n";
//					p[current_player]->incPaschCounter();
//					if (p[current_player]->getPaschCounter() >= 2) {
//						p[current_player]->insGefaengnis();
//						cout << "Sie sind im Gefaengnis!\n";
//						p[current_player]->setPaschCounter(0);
//						break;
//					}
//					else {
//						cout << "Sie duerfen nochmal wuerfeln!\n";
//					}
//				}
//				else {
//					p[current_player]->setPaschCounter(0);
//					break;
//				}
//			} while (true);
//			break;
//		
//		case '3':
//			cout << "Handels-Menue\n";
//			cout << "Welche Strasse moechten Sie anbieten?\n";
//			cin.ignore(); // Puffer leeren
//			string strasse;
//			getline(cin, strasse);
//
//			if (!p[current_player]->besitztStrasse(strasse)) {
//				cout << "Diese Strasse besitzen Sie nicht!\n";
//				break;
//			}
//
//			cout << "An welchen Spieler verkaufen? (ID eingeben)\n";
//			int zielID;
//			cin >> zielID;
//			if (zielID < 0 || zielID >= p.size() || zielID == current_player) {
//				cout << "Ungueltige Spieler-ID.\n";
//				break;
//			}
//
//			cout << "Zu welchem Preis verkaufen?\n";
//			int betrag;
//			cin >> betrag;
//
//			bool erfolg = p[current_player]->verkaufeStrasseAn(p[zielID], strasse, betrag);
//			if (erfolg) {
//				cout << "Handel abgeschlossen.\n";
//			}
//			else {
//				cout << "Handel nicht erfolgreich.\n";
//			}
//			break;
//
//		case '4':
//			cout << "Waehle den Spieler\n";
//			int x;
//			cin >> x;
//			p[x]->getData();
//			break;
//
//		default:
//			cout << "Wollen Sie keine Aufgabe durchfuehren?" << endl << endl;
//			break;
//		}
//		current_player = (current_player + 1) % p.size();
//	}
//}


//int main() {
//
//	UNITTEST();
//	return 0;
//}
