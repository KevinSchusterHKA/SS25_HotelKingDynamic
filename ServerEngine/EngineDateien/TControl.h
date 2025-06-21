#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <windows.h> 
#include <sstream>
#include <iomanip>
#include <tlhelp32.h>
#include <random>
#include <limits>
#include "LookUp.h"

#define KEY_UP 72     
#define KEY_DOWN 80   
#define KEY_LEFT 75   
#define KEY_RIGHT 77  
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_SPACE 32  
#define KEY_W 119  
#define KEY_S 115 
#define KEY_A 97   
#define KEY_D 100  


#define TARGET_FPS 60
#define FRAME_DURATION 1000 / TARGET_FPS
enum class Farbe {
    Zuruecksetzen = 0,
    Schwarz = 30,
    Rot = 91,
    Gruen,
    Gelb,
    Blau,
    Magenta,
    Cyan,
    Weiss,
    BG_Schwarz = 40,
    BG_Rot = 101,
    BG_Gruen,
    BG_Gelb,
    BG_Blau,
    BG_Magenta,
    BG_Cyan,
    BG_Weiss
};



class TControl{
private:
    

    

    
    int ZeitKorrekturKonstante = 30;

	//ASCII Art
    std::string Hotelking[2][22] = {
        {
"$$\\   $$\\            $$\\               $$\\       $$\\   $$\\ $$\\                     ",
"$$ |  $$ |           $$ |              $$ |      $$ | $$  |\\__|                    ",
"$$ |  $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\  $$ |      $$ |$$  / $$\\ $$$$$$$\\   $$$$$$\\  ",
"$$$$$$$$ |$$  __$$\\\\_$$  _|  $$  __$$\\ $$ |      $$$$$  /  $$ |$$  __$$\\ $$  __$$\\ ",
"$$  __$$ |$$ /  $$ | $$ |    $$$$$$$$ |$$ |      $$  $$<   $$ |$$ |  $$ |$$ /  $$ |",
"$$ |  $$ |$$ |  $$ | $$ |$$\\ $$   ____|$$ |      $$ |\\$$\\  $$ |$$ |  $$ |$$ |  $$ |",
"$$ |  $$ |\\$$$$$$  | \\$$$$  |\\$$$$$$$\\ $$ |      $$ | \\$$\\ $$ |$$ |  $$ |\\$$$$$$$ |",
"\\__|  \\__| \\______/   \\____/  \\_______|\\__|      \\__|  \\__|\\__|\\__|  \\__| \\____$$ |",
"                                                                         $$\\   $$ |",
"                                                                         \\$$$$$$  |",
"                                                                          \\______/ ",
"$$$$$$$\\                                              $$\\                          ",
"$$  __$$\\                                             \\__|                         ",
"$$ |  $$ |$$\\   $$\\ $$$$$$$\\   $$$$$$\\  $$$$$$\\$$$$\\  $$\\  $$$$$$$\\                ",
"$$ |  $$ |$$ |  $$ |$$  __$$\\  \\____$$\\ $$  _$$  _$$\\ $$ |$$  _____|               ",
"$$ |  $$ |$$ |  $$ |$$ |  $$ | $$$$$$$ |$$ / $$ / $$ |$$ |$$ /                     ",
"$$ |  $$ |$$ |  $$ |$$ |  $$ |$$  __$$ |$$ | $$ | $$ |$$ |$$ |                     ",
"$$$$$$$  |\\$$$$$$$ |$$ |  $$ |\\$$$$$$$ |$$ | $$ | $$ |$$ |\\$$$$$$$\\                ",
"\\_______/  \\____$$ |\\__|  \\__| \\_______|\\__| \\__| \\__|\\__| \\_______|               ",
"          $$\\   $$ |                                                               ",
"          \\$$$$$$  |                                                               ",
"           \\______/                 Press any key                                  "},
        {
 "  /$$   /$$             /$$               /$$       /$$   /$$ /$$                    ",
 " | $$  | $$            | $$              | $$      | $$  /$$/|__/                    ",
 " | $$  | $$  /$$$$$$  /$$$$$$    /$$$$$$ | $$      | $$ /$$/  /$$ /$$$$$$$   /$$$$$$ ",
 " | $$$$$$$$ /$$__  $$|_  $$_/   /$$__  $$| $$      | $$$$$/  | $$| $$__  $$ /$$__  $$",
 " | $$__  $$| $$  \\ $$  | $$    | $$$$$$$$| $$      | $$  $$  | $$| $$  \\ $$| $$  \\ $$",
 " | $$  | $$| $$  | $$  | $$ /$$| $$_____/| $$      | $$\\  $$ | $$| $$  | $$| $$  | $$",
 " | $$  | $$|  $$$$$$/  |  $$$$/|  $$$$$$$| $$      | $$ \\  $$| $$| $$  | $$|  $$$$$$$",
 " |__/  |__/ \\______/    \\___/   \\_______/|__/      |__/  \\__/|__/|__/  |__/ \\____  $$",
 "                                                                            /$$  \\ $$",
 "                                                                           |  $$$$$$/",
 "                                                                            \\______/ ",
 "  /$$$$$$$                                              /$$                          ",
 " | $$__  $$                                            |__/                          ",
 " | $$  \\ $$ /$$   /$$ /$$$$$$$   /$$$$$$  /$$$$$$/$$$$  /$$  /$$$$$$$                ",
 " | $$  | $$| $$  | $$| $$__  $$ |____  $$| $$_  $$_  $$| $$ /$$_____/                ",
 " | $$  | $$| $$  | $$| $$  \\ $$  /$$$$$$$| $$ \\ $$ \\ $$| $$| $$                      ",
 " | $$  | $$| $$  | $$| $$  | $$ /$$__  $$| $$ | $$ | $$| $$| $$                      ",
 " | $$$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$| $$ | $$ | $$| $$|  $$$$$$$                ",
 " |_______/  \\____  $$|__/  |__/ \\_______/|__/ |__/ |__/|__/ \\_______/                ",
 "            /$$  | $$                                                                ",
 "           |  $$$$$$/                                                                ",
 "            \\______/                Press any key                                    "}
    };

    //Menüs
    std::vector<std::string> MenueStartOptionen = { "Spiel starten","Highscore","Optionen","Beenden","##################################################","Startmenue"};
    std::vector<std::string> MenueSpielerOptionen = { "Wuerfeln","Kaufen","Bauen","Handeln","Runde Beenden","##################################################","Spielermenue"};
    std::vector<std::string> MenueSpielOptionen = { "Fortfahren","Spiel Speichern","Spiel Laden","Spielregeln","Beenden","Highscore","Zurueck","##################################################","Spielmenue"};
    std::vector<std::string> SpielerInformationen = { "Budget","Anzahl gekaufter Objekte","Anzahl gebauter Objekte","#############################################","Was willst du machen?" };

    
    std::string GetDigitsInt(int Zahl);
    std::string GetFarbe(Farbe farbe);
    void SetFarbe(Farbe farbe);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    void HideCursor();
    void ShowCursor();
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
    void GetMaximizedConsoleSize(int& width, int& height);
    void AusgabeStartMenu(int& option, int x, int y);
	
    void AusgabeJaNeinOption(int& option, int x, int y, Farbe f, std::string Ueberschrift);
    void AusgabeStrasseHandeln(int& option,int& WelcheStrasse, int& Angebot, int x, int y, Farbe f);
    void AusgabeGebaeudeBauen(int& option, int& WelcheStrasse, int x, int y, Farbe f);
	void AusgabeAuswahlSpieler(int& option, int x, int y, Farbe f, int& AnzahlSpieler, int& AnzahlCpuGegner, std::vector<std::string>& SpielerNamen);
    void AusgabeSpielOptionen(int& option, int x, int y);
    void AusgabeSpielerOptionen(int& option, int x, int y, Farbe f);
    void AusgabeSpielRegeln(std::vector<std::string> s, int x, int y);
	void AusgabeHandelsMenu(int& option, int x, int y, Farbe f);
    void AusgabeStartBildschirm(bool flip, int x, int y);
    void AusgabeFeld(std::string Feld, int x, int y);
    void AusgabeSpielerInformationen(   std::string Namen[4],int Budget[4],
                                        int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4],
                                        int AnzSpieler,
                                        int x,int y,
                                        std::vector<std::vector<std::string>> GekaufteObjekte,
                                        std::vector<std::vector<std::string>> GebauteObjekte);

	void AusgabeSpielerInventarAnzeige( std::string Namen,std::vector<std::string> GekaufteObjekte,std::vector<std::string> GebauteObjekte,int x,int y,Farbe f);
    void AusgabeTestFeld(int x, int y);
    void AusgabeHighscore(std::string Namen[], int HighscoreWert[], int size, int x, int y);
	void AusgabeWuerfel(int wuerfel, int x, int y, Farbe f);
    void UnitTest();
    int GetLaengstenStringMenueStartOptionen(void);
    int GetLaengstenStringMenueSpielOptionen(void);
    int GetLaengstenStringMenueSpielerOptionen(void);
	int GetAnzMenuepunkteStartOptionen(void);
    int GetAnzMenuepunkteSpielOptionen(void);
    int GetAnzMenuepunkteSpielerOptionen(void);
    void UpdateCursorPosition(COORD Pos);
    void SetConsoleFontSize(int fontSize);
    bool isRunningInWindowsTerminal();
};