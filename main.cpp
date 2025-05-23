#include "TControl.h"

int main(){
    TControl ControlEngine;
    std::string playerNames[4] = {"aaa","bbbb","ccccc","dddddd"};
    int budget[4]={100,10000,100000,99999999};
    int gekObj[4]={5,15,2,3};
    int gebObj[4]={1,2,3,15};
    ControlEngine.PrintSpielerInformationen(playerNames,budget,gekObj,gebObj);
    return 0;
}
