#include <string>
#include <iostream>
//#include <ncurses.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <windows.h> 
#include <sstream>
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
    std::string MenueStartText[7] = {
        "###################################################",
        "#             Hotel King Dynamic                  #",
        "###################################################",
        "#               1. Spiel Starten                  #",
        "#               2. Highscore                      #",
        "#               3. Beenden                        #",
        "###################################################"
    };

    // Array of std::string for the game menu
    std::string MenueSpielText[7] = {
        "###################################################",
        "#             Hotel King Dynamic                  #",
        "###################################################",
        "#               1. Kaufen                         #",
        "#               2. Bauen                          #",
        "#               3. Handeln                        #",
        "###################################################"
    };
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
public:
    TControl();
    ~TControl();
    int PrintMenu(int& option);
    void PrintFeld(std::string Feld[]);
    void PrintSpielerInformationen( std::string Namen[4],
                                    int Budget[4],
                                    int AnzahlGekaufterObjekte[4],
                                    int AnzahlGebauterObjekte[4],
                                    int AnzSpieler);
    void ClearConsole();
};

