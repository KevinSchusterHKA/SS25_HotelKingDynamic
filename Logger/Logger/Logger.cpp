#include "Logger.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

Logger::Logger() {
    std::time_t now = std::time(nullptr);
    std::tm localTimeStruct; 

    
    if (localtime_s(&localTimeStruct, &now) == 0) { 
        std::ostringstream oss;
        oss << std::put_time(&localTimeStruct, "%Y-%m-%d_%H-%M-%S");
        path = oss.str();
        
    }
    else {
        std::cerr << "LoggerFehler: Zeit konnte nicht ermittelt werden" << std::endl;
    }
    
    
    round = 0;
    
}

Logger::Logger(int round, std::string actualPlayer, std::string path) {
    this->round = round;
    this->actualPlayer = actualPlayer;
    this->path = path;

    writeToFile("\nSpielstand wurde geladen!\n\n");
    writeToFile("Runde " + std::to_string(round) + ":\n\t");
    writeToFile("\n\t" + actualPlayer + ":\n\t\t");

}

void Logger::writeToFile(std::string text) {
    std::ofstream file(path+".txt", std::ios::app);

    if (!file.is_open()) {
        std::cerr << "LoggerFehler: Datei konnte nicht geöffnet werden!" << std::endl;
    }
          
    
    file << text;
    file.close();
}

void Logger::newRound() {
    round++;

    writeToFile("Runde " + std::to_string(round)+":\n\t");
}

void Logger::newPlayer(std::string player) {
    actualPlayer = player;
    writeToFile("\n\t"+ actualPlayer + ":\n\t\t");
}

void Logger::playerRollingDice(int first, int second) {
    writeToFile( "Spieler hat eine " + std::to_string(first)+" und eine " + std::to_string(second)+ " gewürfelt. ");

    if (first == second) {
        writeToFile("Somit hat er ein pasch.");
    }

    writeToFile("\n\t\t");
}

void Logger::playerOnStreet(std::string streetName) {
    writeToFile("Spieler ist nun auf " + streetName + "\n\t\t");
}

void Logger::playerInPrison() {
    writeToFile("Spieler muss ins Gefängnis \n\t\t");

    
}
void Logger::onEventField(std::string event) {
    writeToFile("Spieler hat eine Ereigniskarte: " + event+" \n\t\t");
}


void Logger::playerBuysObject(std::string object) {

    writeToFile("Spieler hat Das Objekt " + object + " gekauft \n\t\t");
}

void Logger::playerBuildsBuilding(std::string building) {
    writeToFile("Spieler hat ein " + building + " gebaut \n\t\t");
}