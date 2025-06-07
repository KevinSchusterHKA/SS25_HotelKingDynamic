#include "TControl.h"

int main(){
    std::locale::global(std::locale("German"));
    
    TControl ControlEngine;
    ControlEngine.UnitTest();

    return 0;
}
