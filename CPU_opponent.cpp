#include "CPU_opponent.h"
#include "Player.h"
#include <iostream>
#include <cstdlib> //rand()

cpu_player1::cpu_player1() : player() {}

float cpu_player1::handel(string r, int preowner) {
    if (preowner != -1) {
        std::cout << "[CPU] Kann die Straße '" << r << "' nicht kaufen (gehört schon jemandem).\n";
        return -1.0;
    }
   
    int min_percent = 25;
    int max_percent = 75;
    int percent_offer = min_percent + ((rand() % (max_percent - min_percent))+ 1)/100; // 25 to 74+1
    float angebot = (percent_offer / 100.0) * getBudget();
    std::cout << "[CPU] bietet " << angebot << " für die Straße '" << r << "'.\n";
    return angebot;
}
