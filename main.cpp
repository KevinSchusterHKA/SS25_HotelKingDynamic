#include "TControl.h"

int main(){
    TControl ControlEngine;
    std::string playerNames[4] = {"a","bbbb","ccccc","ddddddddddddddddddddddddddddddddddddddddddddddddddd"};
    int budget[4]={100,10000,100000,99999999};
    int gekObj[4]={5,15,2,3};
    int gebObj[4]={0,2,3,99};
    int option=3;
    while (true)
    {
        DWORD start_time = GetTickCount64();

        ControlEngine.PrintSpielerInformationen(playerNames, budget, gekObj, gebObj, 4);
        ControlEngine.PrintMenu(option);

        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
        ControlEngine.ClearConsole();

    }

    return 0;
}
