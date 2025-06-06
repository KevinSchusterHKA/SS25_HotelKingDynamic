#include "Player.h"
#include "CPU_opponent.h"

player::player() {};
player::~player() {};
float player::getBudget() {
	return this->Budget;
}
void player::setBudget(float f) {
	this->Budget = f;
}

int player::getPosition() {
	return this->Position;
}
void player::setPosition(int p) {
	this->Position = p;
}

int player::getAugenzahl() {
	return this->Augenzahl;
}
void player::setAugenzahl(int a) {
	this->Augenzahl = a;
}

float player::handel(string r, int preowner) {
	string Strasse = r;
	float angebot = -1.0;
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

mt19937 Zufall(time(nullptr));
int player::wurfel() {
	int Zufallszahl;
	Zufallszahl = (Zufall() % 6) + 1;
	return Zufallszahl;
}



int main() {
	int number_cpu_level_1 = 1, number_human_players = 1;
	int current_player = 0;//how is playing right now 
	vector<player*> p;
	for (int i = 0; i < number_human_players; ++i) {
		p.push_back(new player());//Human players
	}
	for (int i = 0; i < number_cpu_level_1; ++i) {
		p.push_back(new cpu_player1());  //level 1 cpu players
	}
	

	while (true) {
		char k;
		cout << "Menue" << endl;
		cout << "1:\t Wuerfeln" << endl;
		cin >> k;
		switch (k) {

		case '1':{
			int temp = 0;
			for (int i = 0; i < 2; i++) {
				cout << "Wuerfel " << i+1 << ":\t " << p[current_player]->wurfel() << endl;
				temp += p[current_player]->wurfel();
			}
			p[current_player]->setAugenzahl(temp);
			cout << "Gesamtaugenzahl:\t" << p[current_player]->getAugenzahl() << endl;
			break;
		}
		case '2':
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
	return 0;

}