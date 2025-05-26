#include "Player.h"

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
