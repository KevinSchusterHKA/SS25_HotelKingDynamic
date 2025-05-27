#include "TControl.h"

int main(){
    TControl ControlEngine;
    std::string playerNames[4] = {"a","bbbb","ccccc","ddddddddddddddddddddddddddddddddddddddddddddddddddd"};
    int budget[4]={100,10000,100000,99999999};
    int gekObj[4]={5,15,2,3};
    int gebObj[4]={0,2,3,99};
    int option=3;
    int Spiellaueft = 1;
    int ClearScreenCounter = 0;
    

    while (Spiellaueft!=5) //5 ist Beenden Code
    {
        DWORD start_time = GetTickCount64();
        Spiellaueft = ControlEngine.AusgabeStartMenu(option, 0, 0);

        //ControlEngine.AusgabeSpielerInformationen(playerNames, budget, gekObj, gebObj,4,12,70);
        //ControlEngine.AusgabeHighscore(playerNames, budget, 4, 30, 30); 
        //ControlEngine.AusgabeSpielOptionen(option,0, 10);
        
        ControlEngine.AusgabeStartBildschirm(TRUE, 50, 50);

        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
        ClearScreenCounter++;
        if (ClearScreenCounter ==12*1)//*t in Sekunden
        {
            ClearScreenCounter = 0;
            system("cls");
        } 
        ControlEngine.ClearConsole();
    }

    return 0;
}
