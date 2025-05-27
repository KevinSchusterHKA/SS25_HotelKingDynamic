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
    std::string arr[2][3] = {
    { "A", "B", "C" },
    { "D", "E", "F" }
    };
    std::string Hotelking[2][22] = {
          {
          "$$\   $$\            $$\               $$\       $$\   $$\ $$\                     ",
          "$$ |  $$ |           $$ |              $$ |      $$ | $$  |\__|                    ",
          "$$ |  $$ | $$$$$$\ $$$$$$\    $$$$$$\  $$ |      $$ |$$  / $$\ $$$$$$$\   $$$$$$\  ",
          "$$$$$$$$ |$$  __$$\\_$$  _|  $$  __$$\ $$ |      $$$$$  /  $$ |$$  __$$\ $$  __$$\ ",
          "$$  __$$ |$$ /  $$ | $$ |    $$$$$$$$ |$$ |      $$  $$<   $$ |$$ |  $$ |$$ /  $$ |",
          "$$ |  $$ |$$ |  $$ | $$ |$$\ $$   ____|$$ |      $$ |\$$\  $$ |$$ |  $$ |$$ |  $$ |",
          "$$ |  $$ |\$$$$$$  | \$$$$  |\$$$$$$$\ $$ |      $$ | \$$\ $$ |$$ |  $$ |\$$$$$$$ |",
          "\__|  \__| \______/   \____/  \_______|\__|      \__|  \__|\__|\__|  \__| \____$$ |",
          "                                                                         $$\   $$ |",
          "                                                                         \$$$$$$  |",
          "                                                                          \______/ ",
          "$$$$$$$\                                              $$\                          ",
          "$$  __$$\                                             \__|                         ",
          "$$ |  $$ |$$\   $$\ $$$$$$$\   $$$$$$\  $$$$$$\$$$$\  $$\  $$$$$$$\                ",
          "$$ |  $$ |$$ |  $$ |$$  __$$\  \____$$\ $$  _$$  _$$\ $$ |$$  _____|               ",
          "$$ |  $$ |$$ |  $$ |$$ |  $$ | $$$$$$$ |$$ / $$ / $$ |$$ |$$ /                     ",
          "$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$ |$$ |                     ",
          "$$$$$$$  |\$$$$$$$ |$$ |  $$ |\$$$$$$$ |$$ | $$ | $$ |$$ |\$$$$$$$\                ",
          "\_______/  \____$$ |\__|  \__| \_______|\__| \__| \__|\__| \_______|               ",
          "          $$\   $$ |                                                               ",
          "          \$$$$$$  |                                                               ",
          "           \______/                                                                "},
           {
           "  /$$   /$$             /$$               /$$       /$$   /$$ /$$                    ",
           " | $$  | $$            | $$              | $$      | $$  /$$/|__/                    ",
           " | $$  | $$  /$$$$$$  /$$$$$$    /$$$$$$ | $$      | $$ /$$/  /$$ /$$$$$$$   /$$$$$$ ",
           " | $$$$$$$$ /$$__  $$|_  $$_/   /$$__  $$| $$      | $$$$$/  | $$| $$__  $$ /$$__  $$",
           " | $$__  $$| $$  \ $$  | $$    | $$$$$$$$| $$      | $$  $$  | $$| $$  \ $$| $$  \ $$",
           " | $$  | $$| $$  | $$  | $$ /$$| $$_____/| $$      | $$\  $$ | $$| $$  | $$| $$  | $$",
           " | $$  | $$|  $$$$$$/  |  $$$$/|  $$$$$$$| $$      | $$ \  $$| $$| $$  | $$|  $$$$$$$",
           " |__/  |__/ \______/    \___/   \_______/|__/      |__/  \__/|__/|__/  |__/ \____  $$",
           "                                                                            /$$  \ $$",
           "                                                                           |  $$$$$$/",
           "                                                                            \______/ ",
           "  /$$$$$$$                                              /$$                          ",
           " | $$__  $$                                            |__/                          ",
           " | $$  \ $$ /$$   /$$ /$$$$$$$   /$$$$$$  /$$$$$$/$$$$  /$$  /$$$$$$$                ",
           " | $$  | $$| $$  | $$| $$__  $$ |____  $$| $$_  $$_  $$| $$ /$$_____/                ",
           " | $$  | $$| $$  | $$| $$  \ $$  /$$$$$$$| $$ \ $$ \ $$| $$| $$                      ",
           " | $$  | $$| $$  | $$| $$  | $$ /$$__  $$| $$ | $$ | $$| $$| $$                      ",
           " | $$$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$| $$ | $$ | $$| $$|  $$$$$$$                ",
           " |_______/  \____  $$|__/  |__/ \_______/|__/ |__/ |__/|__/ \_______/                ",
           "            /$$  | $$                                                                ",
           "           |  $$$$$$/                                                                ",
           "            \______/                                                                 "}



        };
    std::string MenueStartText[7] = {
        "###################################################",
        "#              Hotel King Dynamic                 #",
        "###################################################",
        "#               [1] Spiel Starten                 #",
        "#               [2] Highscore                     #",
        "#               [3] Beenden                       #",
        "###################################################"
    };

    //Vielleicht mit Arrays verbessern
    std::vector<std::string> MenueStartOptionen = { "Spiel starten","Highscore","Beenden","###################################################","#                                                 #","Was willst du machen?"};
    std::vector<std::string> MenueSpielOptionen = { "Kaufen","Bauen","Handeln","###################################################","#                                                 #","Was willst du machen?" };
    std::vector<std::string> SpielerInformationen = { "Budget","Anzahl gekaufter Objekte","Anzahl gebauter Objekte","###################################################","#                                                 #","Was willst du machen?" };

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
    void SetConsoleFontSize(int size);
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
    void AusgabeSpielerInformationen(  std::string Namen[4],
                                                int Budget[4],
                                                int AnzahlGekaufterObjekte[4],
                                                int AnzahlGebauterObjekte[4],
                                                int AnzSpieler, 
                                                int x,
                                                int y);
    void AusgabeSpielOptionen(int& option, int x, int y);
    void AusgabeHighscore(std::string Namen[], int HighscoreWert[], int size, int x, int y);
    void AusgabeStartBildschirm(bool flip, int x, int y);
    void ClearConsole();
};

