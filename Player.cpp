#include "Player.h"


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
	vector<player*> p;
	p.push_back(new player());

	while (true) {
		char k;
		cout << "Menue" << endl;
		cout << "1:\t Wuerfeln" << endl;
		cin >> k;
		switch (k) {

		case '1':
			int temp = 0;
			for (int i = 0; i < 2; i++) {
				cout << "Wuerfel " << i+1 << ":\t " << p[0]->wurfel() << endl;
				temp += p[0]->wurfel();
			}
			p[0]->setAugenzahl(temp);
			cout << "Gesamtaugenzahl:\t" << p[0]->getAugenzahl() << endl;
			break;

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
	}
	return 0;
}
