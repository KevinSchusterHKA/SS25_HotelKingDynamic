//#include "CPU_opponent.h"
//#include "Player.h"
//#include <iostream>
//#include <cstdlib> // rand()
//
//struct Property {//temp just for test
//    std::string name;
//    int price;
//};
//
//class Map {//temp just for test
//public:
//    int getStreetPrice(int pos) {
//        switch (pos) {
//        case 1:
//            return 200;
//        case 3:
//            return 201;
//             
//        case 5:
//            return 202;
//        case 6:
//            return 205;
//        default:
//            std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//            return -1;
//        }
//    }
//    bool buyStreet(int pos, int playerID) {
//        switch (pos) {
//        case 1:
//            std::cout << "a " << playerID << " kann kaufen\n";
//            return true;
//        case 3:
//            std::cout << "b " << playerID << " kann nicht gekauft\n";
//            return false;
//        case 5:
//            std::cout << "c " << playerID << " kann kaufen\n";
//            return true;
//        case 6:
//            std::cout << "d " << playerID << " kann kaufen\n";
//            return true;
//        default:
//            std::cout << "Keine kaufbare Strabe auf Position " << pos << ".\n";
//            return false;
//        }
//    }
//};
//
//std::vector<Property> getTempPropertiesForPlayer(int playerID) {//temp just for test
//    std::vector<Property> props;
//    if (playerID == 0) {
//        props.push_back({ "a0", 350 });
//        props.push_back({ "b0", 400 });
//    }
//    else if (playerID == 1) {
//        props.push_back({ "c1", 60 });
//    }
//    else if (playerID == 2) {
//        props.push_back({ "d2", 150 });
//        props.push_back({ "e2", 200 });
//    }
//    return props;
//}
//
//cpu_player1::cpu_player1() : player() {}
//
//// cpu to player
//int cpu_player1::handel(int cpuID, int totalPlayers, std::vector<player*>& p) {
//    if ((rand() % 100) > 5) {
//        std::cout << "CPU entscheidet sich gegen einen Handelsversuch.\n";
//        return -1;
//    }
//    int targetPlayer;
//    do {
//        targetPlayer = rand() % totalPlayers;
//    } while (targetPlayer == cpuID);
//
//    std::vector<Property> ownedProperties = getTempPropertiesForPlayer(targetPlayer);
//
//    if (ownedProperties.empty()) {
//        std::cout << "CPU Spieler " << targetPlayer << " besitzt keine Straben.\n";
//        return -1;
//    }
//
//    int randIndex = rand() % ownedProperties.size();
//    Property& prop = ownedProperties[randIndex];
//
//    int minPercent = 5;
//    int maxPercent = 15;
//    int offerPercent = minPercent + rand() % (maxPercent - minPercent + 1);
//    float offer = (1+offerPercent / 100.0) * prop.price;
//
//    if (offer > p[cpuID]->getBudget()) {
//        std::cout << "CPU Kann sich das Angebot von " << offer
//            << " fur '" << prop.name << "' nicht leisten.\n";
//        return -1;
//    }
//
//    std::cout << "CPU bietet " << offer << " (" << offerPercent << "% von "
//        << prop.price << ") fur '" << prop.name << "' von Spieler " << targetPlayer << ".\n";
//
//    return static_cast<int>(offer);
//}
//
//// player to cpu 
//bool cpu_player1::acceptTrade(Property& prop, int offer) {
//    int acceptThresholdPercent = 90 + (std::rand() % 21);// min of 90% to max of 110% 
//
//    if (offer <= prop.price * (acceptThresholdPercent / 100.0) && offer <= getBudget()) {
//        std::cout << "CPU akzeptiert das Angebot von " << offer << " fur '" << prop.name
//            << "' (Schwelle: " << acceptThresholdPercent << "%).\n";
//        return true;
//    }
//    else {
//        std::cout << "CPU lehnt das Angebot von " << offer << " fur '" << prop.name
//            << "' ab (Schwelle: " << acceptThresholdPercent << "%).\n";
//        return false;
//    }
//}
//
//// buy street
//bool cpu_player1::tryBuyStreet(Map& gameMap, std::vector<player*>& p) {
//    int pos = getPosition();
//    int price = gameMap.getStreetPrice(pos);
//
//    if (price <= 0) {
//        std::cout << "CPU Kein Kaufmoeglichkeit auf Position " << pos << ".\n";
//        return false;
//    }
//
//    if (getBudget() >= price) {
//        bool success = gameMap.buyStreet(pos, getID());
//        if (success) {
//            setBudget(getBudget() - price);
//            std::cout << "CPU kauft Strasse auf Position " << pos
//                << " fuer " << price << ".\n";
//            return true;
//        }
//        else {
//            std::cout << "CPU Kauf auf Position " << pos << " fehlgeschlagen.\n";
//        }
//    }
//    else {
//        std::cout << "CPU Kein Geld fuer Strasse auf Position " << pos << ".\n";
//    }
//    return false;
//}
//
//void UNITTEST_cpu() {
//    std::srand(std::time(nullptr));  // random seed 
//    std::vector<player*> players;
//
//    for (int i = 0; i < 2; ++i) {
//        players.push_back(new player());
//        players.back()->setID(i);
//        players.back()->setHuman(HUMAN);
//        players.back()->setBudget(1000);
//        players.back()->setPosition(i);
//    }
//
//    for (int i = 0; i < 5; ++i) {
//        players.push_back(new cpu_player1());
//        players.back()->setID(i + 2);
//        players.back()->setHuman(CPU1);
//        players.back()->setBudget(1000);
//        players.back()->setPosition(i + 3);
//    }
//
//    Map gameMap;
//    for (size_t i = 0; i < players.size(); ++i) {
//        if (players[i]->getHuman() == CPU1) {
//            cpu_player1* cpu = static_cast<cpu_player1*>(players[i]);
//            cpu->tryBuyStreet(gameMap, players);
//            cpu->handel(cpu->getID(), players.size(), players);
//            Property exampleProp = { "Teststrabe", 400 };
//            int offer = 390;
//            cpu->acceptTrade(exampleProp, offer);
//            cout << "##############" << endl;
//        }
//    }
//}
////int main() {
////    UNITTEST_cpu();
////  
////
////    return 0;
////}
