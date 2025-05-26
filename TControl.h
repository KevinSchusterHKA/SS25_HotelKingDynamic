#include <string>
#include <iostream>
//#include <ncurses.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <windows.h> 
#include <sstream>
#include <iomanip>
#include "LookUp.h"

#define KEY_UP 72     
#define KEY_DOWN 80   
#define KEY_LEFT 75   
#define KEY_RIGHT 77  
#define KEY_ENTER 13
#define TARGET_FPS 60
#define FRAME_DURATION 1000 / TARGET_FPS

class TControl{
private:
    enum class Farbe {
    Zuruecksetzen=0,
    Schwarz=30,
    Rot,
    Gruen,
    Gelb,
    Blau,
    Magenta,
    Cyan,
    Weiss,
    BG_Schwarz=40,
    BG_Rot,
    BG_Gruen,
    BG_Gelb,
    BG_Blau,
    BG_Magenta,
    BG_Cyan,
    BG_Weiss
    };
    //Menüs
    std::string MenueStartText[7] = {
        "###################################################",
        "#             Hotel King Dynamic                  #",
        "###################################################",
        "#               1. Spiel Starten                  #",
        "#               2. Highscore                      #",
        "#               3. Beenden                        #",
        "###################################################"
    };
    std::string MenueSpielStarten[7]={
        "###################################################",
        "#             Hotel King Dynamic                  #",
        "###################################################",
        "#               1. Neues Spiel                    #",
        "#               2. Spielstand laden               #",
        "#               3. Spielstand speichern           #",
        "###################################################"
    };
    std::string MenueSpiel[7] = {
        "###################################################",
        "#             Hotel King Dynamic                  #",
        "###################################################",
        "#               1. Kaufen                         #",
        "#               2. Bauen                          #",
        "#               3. Handeln                        #",
        "###################################################"
    };

    //Vielleicht mit Arrays verbessern
    std::vector<std::string> MenueStartOptionen = { "Start","Spiel starten","Highscore","Beenden","###################################################","#                                                 #","Menü"};
    std::vector<std::string> MenueSpielOptionen = { "Kaufen","Bauen","Handeln","###################################################","#                                                 #","Was willst du machen?" };

    std::string SpielerAusgabeTextMuster[7] = {
        "######################################",
        "#Spielername                         #",
        "######################################",
        "#Budget:                   XXXXXXXX  #",
        "#Anzahl gekaufter Objekte:       XX  #",
        "#Anzahl gebauter Objekte:        XX  #",
        "######################################"
    }; 

    std::string GetDigitsInt(int Zahl);
    std::string GetFarbe(Farbe farbe);
    void SetFarbe(Farbe farbe);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    void HideCursor(HANDLE hConsole);
    //BOOL WINAPI SetConsoleCursorPosition(_In_ HANDLE hConsoleOutput,_In_ COORD  dwCursorPosition);
    void AusgabeSpielerBox( std::string Namen,
                            int Budget,
                            int AnzahlGekaufterObjekte,
                            int AnzahlGebauterObjekte,
                            int x,
                            int y,
                            Farbe f);
public:
    TControl();
    ~TControl();
    int AusgabeStartMenu(int& option, int x, int y);
    void AusgabeFeld(std::string Feld[]);
    void AusgabeSpielerInformationen(   std::string Namen[4],
                                        int Budget[4],
                                        int AnzahlGekaufterObjekte[4],
                                        int AnzahlGebauterObjekte[4],
                                        int AnzSpieler);
    void AusgabeSpielerInformationenMitPosition(  std::string Namen[4],
                                                int Budget[4],
                                                int AnzahlGekaufterObjekte[4],
                                                int AnzahlGebauterObjekte[4],
                                                int AnzSpieler, 
                                                int x,
                                                int y);
    void AusgabeSpielOptionen(int& option, int x, int y);
    void AusgabeHighscore(std::string Namen[], int HighscoreWert[], int size, int x, int y);
    void ClearConsole();
};

