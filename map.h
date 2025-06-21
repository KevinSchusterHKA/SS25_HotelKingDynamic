#pragma once 
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <cstdlib>

class Map {
public:
    int _streetarr[8][3] = {
        {1, 3, 6},       
        {8, 9, 11},      
        {13, 14, 16},    
        {18, 19, 21},    
        {23, 24, 26},    
        {27, 29, 31},    
        {32, 34, 37},    
        {39, -1, -1}     
    };

    int houseCounts[40] = { 0 };  
    int housePrices[40] = { 40 };  
    int owners[40] = { -1 };     

    Map() {
        
        for (int i = 0; i < 40; i++) housePrices[i] = 40;
      
        for (int i = 0; i < 3; ++i) owners[_streetarr[0][i]] = 0; 
        for (int i = 0; i < 3; ++i) owners[_streetarr[1][i]] = 1; 
      
    }

    std::string getPropertyName(int space) {
        switch (space) {
        case 1:  return "Kaiserstrasse";
        case 3:  return "Erbprinzenstrasse";
        case 6:  return "Ettlinger_Tor";
        case 8:  return "Amalienstrasse";
        case 9:  return "Waldstrasse";
        case 11: return "Durlacher_Allee";
        case 13: return "Rueppurrer_Strasse";
        case 14: return "Moltkestrasse";
        case 16: return "Herrenstrasse";
        case 18: return "Kronenstrasse";
        case 19: return "Kriegsstrasse";
        case 21: return "Kanalweg";
        case 23: return "Sophienstrasse";
        case 24: return "Karlstrasse";
        case 26: return "Tullastrasse";
        case 27: return "Hardtstrasse";
        case 29: return "Rintheimer_Strasse";
        case 31: return "Wolfartsweierer_Strasse";
        case 32: return "Nordendstrasse";
        case 34: return "Lorenzstrasse";
        case 37: return "Kuehler_Krug";
        case 39: return "Europaplatz";
        default: return "Unbekannte_Strasse";
        }
    }

    int getHouseCount(int i) {
        return houseCounts[i];
    }

    int getHousePrice(int i) {
        return housePrices[i];
    }

    void addHouse(int i) {
        if (houseCounts[i] < 5) { 
            houseCounts[i]++;
            std::cout << "Added house on " << getPropertyName(i) << ", total houses now: " << houseCounts[i] << "\n";
        }
    }

    int ownsStreets(int player, int space) {
        if (player == 2 && space == 1) //for 1,3,6
        {
            return 1;
        }
        return 0;
    }

    int getOwner(int id) {
        return owners[id];
    }
};





//old code
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