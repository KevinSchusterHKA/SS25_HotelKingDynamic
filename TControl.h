#include <string>
#include <iostream>
//#include <curses.h>
#include <conio.h>
#include <algorithm>
 #define KEY_UP 72
 #define KEY_DOWN 80
 #define KEY_LEFT 75
 #define KEY_RIGHT 77

class TControl{
private:
    std::string MenueStartText;
    std::string MenueSpielText;
    std::string SpielerAusgabeTextMuster; 
    void SetCursorPosition(int x, int y);
    void ClearConsole();
    std::string GetDigitsInt(int Zahl);
public:
    TControl();
    ~TControl();
    void PrintMenu();
    void PrintFeld(std::string Feld[]);
    void PrintSpielerInformationen(std::string Namen[4],int Budget[4],int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4]);
    void AuswahlMenu(void);
};

