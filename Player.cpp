#include "Player.h"
#include "CPU_opponent.h"

player::player() {};
player::player(int budget, int position) { this->Budget = budget; this->Position = position; };
player::~player() {};

void player::setID(int id) { this->ID = id; }
int player::getID() { return this->ID; }

void player::setHuman(bool h) { this->Human = h; }
bool player::getHuman() { return this->Human; }

int player::getBudget()			{return this->Budget;}
void player::setBudget(int b)	{this->Budget = b;}

int player::getPosition()		{return this->Position;}
void player::setPosition(int p) {this->Position = p;}

int player::getWurfel(int index)			{return this->Wurfelzahl[index];}
void player::setWurfel(int w, int index)	{this->Wurfelzahl[index] = w;}
void player::Wurfelmechn() {
	for (int i = 0; i < 2; i++) {
		this->setWurfel(this->wurfeln(), i);
	}
	this->setAugenzahl(this->getWurfel(0) + this->getWurfel(1));
}
void player::Paschwurf() {
	for (int i = 0; i < 2; i++) {
		this->setWurfel(1, i);
	}
	this->setAugenzahl(this->getWurfel(0)+this->getWurfel(1));
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

void UNITTEST(int numCPU, int numHUM, vector<player*> p) {
	int current_player = 0;
	while (true) {
		char k;
		cout << "\n\nMenue" << endl;
		cout << "1:\t zufaelliges Wuerfeln\n";
		cout << "2:\t pasch Wuerfeln\n";
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
						break;  // keine weiteren Würfe
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
		case '2':
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
						break;  // keine weiteren Würfe
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

		case '3':
			break;

		case '4':
			break;

		default:
			cout << "Wollen Sie keine Aufgabe durchfueren?" << endl << endl;
			break;
		}
		current_player = (current_player + 1) % p.size();//change player after turn
	}
}

//int main() {
//	int number_cpu_level_1 = 2, number_human_players = 2;
//	int current_player = 0;				// who is playing right now 
//	vector<player*> p;
//	for (int i = 0; i < number_human_players; ++i) {
//		p.push_back(new player());		// human players
//		p[i]->setID(i);
//		p[i]->setHuman(1);
//	}
//	for (int i = 0; i < number_cpu_level_1; ++i) {
//		p.push_back(new cpu_player1()); // level 1 cpu players
//		p[number_human_players+i]->setID(i);
//		p[number_human_players + i]->setHuman(0);
//	}
//	UNITTEST(number_cpu_level_1, number_human_players, p);
//	return 0;
//}

 
