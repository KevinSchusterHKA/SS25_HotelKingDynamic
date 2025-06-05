#include "TControl.h"

int main(){
    std::locale::global(std::locale("de_DE.utf-8"));

    TControl ControlEngine;
    ControlEngine.UnitTest();

    return 0;
}
