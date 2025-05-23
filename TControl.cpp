
#include "TControl.h"
#include <iterator>

TControl::TControl(){
    this->MenueStartText =      "###################################################\n"
                                "#             Hotel King Dynamic                  #\n"
                                "###################################################\n"
                                "#               1. Spiel Starten                  #\n"
                                "#               2. Highscore                      #\n"
                                "#               3. Beenden                        #\n"
                                "###################################################\n";

    this->MenueSpielText =      "###################################################\n"
                                "#             Hotel King Dynamic                  #\n"
                                "###################################################\n"
                                "#               1. Kaufen                         #\n"
                                "#               2. Bauen                          #\n"
                                "#               3. Handeln                        #\n"
                                "###################################################\n";

    this->SpielerAusgabeTextMuster=         
                                "######################################" //Anzahl Zeichen pro Zeile  = 39 mit \n
                                "#Spielername                         #"
                                "######################################"
                                "#Budget:                   XXXXXXXX  #"
                                "#Anzahl gekaufter Objekte: XX        #"
                                "#Anzahl gebauter Objekte:  XX        #"
                                "######################################";

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
void TControl::PrintSpielerInformationen(std::string Namen[4],int Budget[4],int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4]){
    int PosSpielername =this->SpielerAusgabeTextMuster.find("Spielername");
    int PosBudget =this->SpielerAusgabeTextMuster.find("Budget:                   X")+sizeof("Budget:                   X");
    int PosAnzGekauft =this->SpielerAusgabeTextMuster.find("Anzahl gekaufter Objekte: X")+sizeof("Anzahl gekaufter Objekte: X");
    int PosAnzGebaut =this->SpielerAusgabeTextMuster.find("Anzahl gebauter Objekte: X")+sizeof("Anzahl gebauter Objekte: X");

    std::string TempString="";
    std::string AusgabeTextSpielerN[4];
    int tempLengthSpielerBox=std::size("######################################")-1;
    for (int i = 0;i<4; i++) {
        AusgabeTextSpielerN[i]=this->SpielerAusgabeTextMuster;
        for (int j=0; j<11; j++) {
            if (j<Namen[i].length()) {
                AusgabeTextSpielerN[i][PosSpielername+j]=Namen[i][j];
            }
            else {
                AusgabeTextSpielerN[i][PosSpielername+j]=' ';
            }
        }
        TempString = this->GetDigitsInt(Budget[i]);

        for (int j=7; j>=0; j--) {
            if (this->GetDigitsInt(Budget[i]).length()<j) {
                //ändere die Leerzeichen nicht
            }
            else {
                AusgabeTextSpielerN[i][PosBudget+j]=TempString[j];
            }
        }
        TempString = this->GetDigitsInt(AnzahlGekaufterObjekte[i]);

        for (int j=1; j>=0; j--) {
            if (Namen[i].length()<j) {
                //ändere die Leerzeichen nicht
            }
            else {
                AusgabeTextSpielerN[i][PosAnzGekauft+j]=TempString.c_str()[j];
            }
        }

        TempString = this->GetDigitsInt(AnzahlGebauterObjekte[i]);

        for (int j=1; j>=0; j--) {
            if (Namen[i].length()<j) {
                //ändere die Leerzeichen nicht
            }
            else {
                AusgabeTextSpielerN[i][PosAnzGebaut+j]=TempString.c_str()[j];
            }
        }
    }   
        for (int j=0; j<7; j++) {
            for (int k=0;k<4;k++) {
                            TempString=AusgabeTextSpielerN[0].substr(j*tempLengthSpielerBox,tempLengthSpielerBox);
                            std::cout<<TempString;
            }
            std::cout<<std::endl;
        }
}
void TControl::AuswahlMenu(void){       
    
        int c = getch();
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
        int digit = Zahl % 10; // Get the last digit
        digits.push_back(static_cast<char>(digit + '0')); // Convert to char
        Zahl /= 10; // Remove the last digit
    }
    // The digits are in reverse order, so reverse them
    std::reverse(digits.begin(), digits.end());
    return digits;
}


