#include <iostream>
#include <string>
#include <windows.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class TControl{
    private:
    std::string MenueStart;
    std::string MenueSpiel;
    void SetCursorPosition(int x, int y);
    public:
    TControl();
    ~TControl();
    void PrintMenu();
    void PrintFeld(TMap Feld[]);
    void PrintSpielerInformationen(TSpieler Spieler[4]);
    void AuswahlMenu(void);
};