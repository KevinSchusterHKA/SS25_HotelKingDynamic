#include <string>
#include <algorithm>
#include "TControl.h"

TControl::TControl(){
    this->MenueStartText =  R"(
                                ###################################################\n
                                #             Hotel King Dynamic                  #\n
                                ###################################################\n
                                #               1. Spiel Starten                  #\n
                                #               2. Highscore                      #\n
                                #               3. Beenden                        #\n
                                ###################################################\n
                            )";
    this->MenueSpielText =  R"(
                                ###################################################\n
                                #             Hotel King Dynamic                  #\n
                                ###################################################\n
                                #               1. Kaufen                         #\n
                                #               2. Bauen                          #\n
                                #               3. Handeln                        #\n
                                ###################################################\n
                            )";
    this->SpielerAusgabeTextMuster=R"(
                                ######################################\n 
                                #Spielername                         #\n
                                ######################################\n
                                #Budget:                   XXXXXXXX  #\n
                                #Anzahl gekaufter Objekte: XX        #\n
                                #Anzahl gebauter Objekte:  XX        #\n
                                ######################################\n
                            )";//Anzahl Zeichen pro Zeile  = 39 mit \n

}
TControl::~TControl(){
    
}
void TControl::PrintMenu(){

    std::cout<<this->MenueStartText<<std::endl;

}
void TControl::PrintFeld(std::string Feld[]){

}
void TControl::PrintSpielerInformationen(std::string Namen[4],int Budget[4],int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4]){
    for (int i = 0;i<4; i++) {
        std::string tempS=this->SpielerAusgabeTextMuster;
        for (int j=0; j<11; j++) {
            if (Namen[i].length()<j) {
                //ändere die Leerzeichen nicht
            }
            else {
                tempS[40+j]=Namen[i].c_str()[j];
            }
        }
        for (int j=0; j<10; j++) {
        
        }
    }
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
    std::cout << "\033[" << y << ";" << x << "H";
}
void TControl::ClearConsole() {
    std::cout << "\033[2J\033[1;1H"; // Clear screen and move cursor to top-left
    std::cout.flush(); // Ensure the output is sent to the console immediately
}

std::string TControl::GetDigitsInt(int Zahl){
    std::string digits;

    while (Zahl > 0) {
        int digit = Zahl % 10; // Get the last digit
        digits.push_back(static_cast<char>(digit + '0')); // Convert to char
        Zahl /= 10; // Remove the last digit
    }
    // The digits are in reverse order, so reverse them
    std::reverse(digits.begin(), digits.end());
    return digits;
}