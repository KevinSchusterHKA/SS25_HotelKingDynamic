#include "Player.h"

mt19937 Zufall(time(nullptr));
int Player::wurfel() {
	int Zufallszahl;
	Zufallszahl = (Zufall() % 6) + 1;
	return Zufallszahl;
}


int main() {
	vector<player> p1, p2;


	while (true) {
		char k;
		cout << "Menue" << endl;
		cout << "1:\t Wuerfeln" << endl;
		cin >> k;
		switch (k) {

		case '1':
			int temp = 0;
			for (int i = 0; i < 2; i++) {
				cout << "Wuerfel " << i+1 << ":\t " << p1->wurfel() << endl;
				temp += p1.wurfel()
			}
			p1->setAugenzahl(temp);
			cout << "Gesamtaugenzahl:\t" << p1->getAugenzahl << endl;
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
