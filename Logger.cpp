#include "Logger.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>

Logger::Logger() {
    
    path = "log";
    
    round = 0;
    
}

Logger::Logger(int round, std::string actualPlayer) {
    this->round = round;
    this->actualPlayer = actualPlayer;
    path= "log";



    std::time_t now = std::time(nullptr);
    std::tm localTimeStruct;


    if (localtime_s(&localTimeStruct, &now) == 0) {
        std::ostringstream oss;
        oss << std::put_time(&localTimeStruct, "%Y-%m-%d_%H-%M-%S");
        writeToFile("\n-----------------------Spielstand wurde geladen! " + oss.str() + "--------------------------\n");

    }
    else {
        std::cerr << "LoggerFehler: Zeit konnte nicht ermittelt werden" << std::endl;
    }
   
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


void Logger::newGame() {
    std::time_t now = std::time(nullptr);
    std::tm localTimeStruct;


    if (localtime_s(&localTimeStruct, &now) == 0) {
        std::ostringstream oss;
        oss << std::put_time(&localTimeStruct, "%Y-%m-%d_%H-%M-%S");
        writeToFile("\n-----------------------Neues Spiel " +oss.str()+"--------------------------\n");

    }
    else {
        std::cerr << "LoggerFehler: Zeit konnte nicht ermittelt werden" << std::endl;
    }
}
void Logger::newRound() {
    round++;
    writeToFile("\n");
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

void Logger::playerMoney(std::string player, int money) {
    writeToFile("Der Spieler " + player + " besitzt "+ std::to_string(money) +"€ \n\t\t");

}