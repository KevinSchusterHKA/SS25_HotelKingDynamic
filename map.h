//#pragma once //useless now because of  from map.h
//#include "Player.h"
//class Map {//temp just for test
//public:
//	int getPropertyPrice(int pos) {
//		switch (pos) {
//		case 1: return 200;
//		case 3: return 201;
//		case 5: return 202;
//		case 6: return 205;
//		default:
//			std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//			return -1;
//		}
//	}
//	std::vector<int> getOwnedProperties(int playerID) {
//		if (playerID == 0) return { 1, 5 };
//		if (playerID == 1) return { 3 };
//		if (playerID == 2) return { 6 };
//		return {};
//	}
//	int getStreetPrice(int pos) {
//		switch (pos) {
//		case 1:
//			return 200;
//		case 3:
//			return 201;
//		case 5:
//			return 202;
//		case 6:
//			return 205;
//		default:
//			std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//			return -1;
//		}
//	}
//	bool buyStreet(int pos, int playerID) {
//		switch (pos) {
//		case 1:
//			std::cout << "a " << playerID << " kann kaufen\n";
//			return true;
//		case 3:
//			std::cout << "b " << playerID << " kann nicht gekauft\n";
//			return false;
//		case 5:
//			std::cout << "c " << playerID << " kann kaufen\n";
//			return true;
//		case 6:
//			std::cout << "d " << playerID << " kann kaufen\n";
//			return true;
//		default:
//			std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//			return false;
//		}
//	}
//};