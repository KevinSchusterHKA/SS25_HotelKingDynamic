
#include "TControl.h"
#include <iterator>

TControl::TControl(){
    // Initialize ncurses
    // initscr();            // Start PDCurses mode
    // keypad(stdscr, TRUE); // Enable special keys
    // noecho();             // Don't echo pressed keys

}
TControl::~TControl(){
    
}
void TControl::PrintMenu(){

    std::cout<<this->MenueStartText<<std::endl;
}
void TControl::PrintFeld(std::string Feld[]){

}
void TControl::PrintSpielerInformationen(std::string Namen[4],int Budget[4],int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4],int AnzSpieler){    
    //Ausgabe #-Zeichen
    for (int j=0;j<AnzSpieler;j++) {
        std::cout<<this->SpielerAusgabeTextMuster[0];
    }
    std::cout<<std::endl;
    //Ausgabe Spielernamen
    for (int j=0;j<AnzSpieler; j++) {
        if (Namen[j].length()<36) {
            Namen[j].insert(Namen[j].length(),36-Namen[j].length(),' ');
        }
        std::cout<<"#"+Namen[j].substr(0,36)+"#";
    }
    std::cout<<std::endl;
    //Ausgabe #-Zeichen
    for (int j=0;j<AnzSpieler;j++) {
        std::cout<<this->SpielerAusgabeTextMuster[2];
    }
    std::cout<<std::endl;
    //Ausgabe Budget Spieler
    for (int j=0;j<AnzSpieler;j++) {
        std::string tempBudget = this->GetDigitsInt(Budget[j]);
        std::string tempText = this->SpielerAusgabeTextMuster[3];
        if (tempBudget.length()<8) {
            tempBudget.insert(tempBudget.length(),8-tempBudget.length(),' ');
        }
        for (int k=0;k<8; k++) {
            tempText.replace(tempText.find_last_of("X"),1,1,tempBudget[k]);
        }
        std::cout<<tempText;
    }
    std::cout<<std::endl;
    for (int j=0;j<AnzSpieler;j++) {
        std::string tempAnz = this->GetDigitsInt(AnzahlGekaufterObjekte[j]);
        std::string tempText = this->SpielerAusgabeTextMuster[4];
        if (tempAnz.length()<2) {
            tempAnz.insert(tempAnz.length(),2-tempAnz.length(),' ');
        }
        for (int k=0;k<2; k++) {
            tempText.replace(tempText.find_last_of("X"),1,1,tempAnz[k]);
        }
        std::cout<<tempText;
    }
    std::cout<<std::endl;
        for (int j=0;j<AnzSpieler;j++) {
        std::string tempAnz = this->GetDigitsInt(AnzahlGebauterObjekte[j]);
        std::string tempText = this->SpielerAusgabeTextMuster[5];
        if (tempAnz.length()<2) {
            tempAnz.insert(tempAnz.length(),2-tempAnz.length(),' ');
        }
        for (int k=0;k<2; k++) {
            tempText.replace(tempText.find_last_of("X"),1,1,tempAnz[k]);
        }
        std::cout<<tempText;
    }
    std::cout<<std::endl;
    //Ausgabe #-Zeichen
    for (int j=0;j<AnzSpieler;j++) {
        std::cout<<this->SpielerAusgabeTextMuster[2];
    }
    std::cout<<std::endl;

}
void TControl::AuswahlMenu(void){       
    
        int c = 0;//_getch();
        switch(c) {
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        default:
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
        int digit = Zahl % 10;
        digits.push_back(static_cast<char>(digit + '0')); 
        Zahl /= 10; 
    }

    //std::reverse(digits.begin(), digits.end());
    return digits;
}


