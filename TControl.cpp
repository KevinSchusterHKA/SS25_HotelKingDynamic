#include "TControl.h"



TControl::TControl(){
    this->MenueStart =  R"(
                                ###################################################\n
                                #             Hotel King Dynamic                  #\n
                                ###################################################\n
                                #               1. Spiel Starten                  #\n
                                #               2. Highscore                      #\n
                                #               3. Beenden                        #\n
                                ###################################################\n
                            )";
    this->MenueSpiel =  R"(
                                ###################################################\n
                                #             Hotel King Dynamic                  #\n
                                ###################################################\n
                                #               1. Kaufen                         #\n
                                #               2. Bauen                          #\n
                                #               3. Handeln                        #\n
                                ###################################################\n
                            )";

}
TControl::~TControl(){
    
}
void TControl::PrintMenu(){

    std::cout<<this->MenueStart<<std::endl;

}
void TControl::PrintFeld(TMap Feld[]){

}
void TControl::PrintSpielerInformationen(TSpieler Spieler[4]){

}
void TControl::AuswahlMenu(void){       
    
        c = 0;
        switch((c=getch())) {
        case KEY_UP:
            cout << endl << "Up" << endl;//key up
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl;   // key down
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl;  // key left
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl;  // key right
            break;
        default:
            cout << endl << "null" << endl;  // not arrow
            break;
        }

}
void TControl::SetCursorPosition(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}