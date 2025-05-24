
#include "TControl.h"

TControl::TControl(){
    // Initialize ncurses;
    //initscr(); // Start ncurses mode
    //cbreak(); // Disable line buffering
    //noecho(); // Don't echo pressed keys
    //keypad(stdscr, TRUE); // Enable arrow keys

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
TControl::~TControl(){
    
}

void TControl::PrintFeld(std::string Feld[]){

}
void TControl::PrintSpielerInformationen(std::string Namen[4],int Budget[4],int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4],int AnzSpieler){    
    //Ausgabe #-Zeichen
    for (int j=0;j<AnzSpieler;j++) {
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));
        std::cout<<this->SpielerAusgabeTextMuster[0];
    }
    std::cout<<std::endl;
    //Ausgabe Spielernamen
    for (int j=0;j<AnzSpieler; j++) {
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));

        if (Namen[j].length()<36) {
            Namen[j].insert(Namen[j].length(),36-Namen[j].length(),' ');
        }
        std::cout<<"#"+Namen[j].substr(0,36)+"#";
    }
    std::cout<<std::endl;
    //Ausgabe #-Zeichen
    for (int j=0;j<AnzSpieler;j++) {
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));

        std::cout<<this->SpielerAusgabeTextMuster[2];
    }
    std::cout<<std::endl;
    //Ausgabe Budget Spieler
    for (int j=0;j<AnzSpieler;j++) {
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));

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
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));

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
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));

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
        this->SetFarbe(static_cast<Farbe>(j+static_cast<int>(Farbe::Rot)));

        std::cout<<this->SpielerAusgabeTextMuster[2];
    }
    std::cout<<std::endl;

}
int TControl::PrintMenu(void){
    enum OptionenMenu{Start=3,Highscore=4,Beenden=5};
    std::string temp[7];
    int option = 3;
    int inputCh = 0;
    system("cls");
    do {
        std::ostringstream oss;

        DWORD start_time = GetTickCount64();

        for (int i = 0; i < 7; ++i) {
            temp[i] = MenueStartText[i]; 
            if (i==option) {
                temp[option].replace(temp[option].find(GetDigitsInt(option-2))-1,1,1,'>');
            }
            temp[i] += "\n";
			oss << temp[i]; 
        }
        inputCh = 0;

		std::cout << oss.str(); 
        if (_kbhit()) { // Check if a key is pressed
            inputCh = _getch(); 
        }

        switch(inputCh) {
        case KEY_UP:
                if ( option > 3) {
                    option--;            
                }
            break;
        case KEY_DOWN:
                if (option <5) {
                    option++;            
                }
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        default:
            break;
        }
        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time); 
        }
		this->ClearConsole();//muss in die Hauptschleife, zu Testzwecken hier


    }while (inputCh!= KEY_ENTER);
    return option;
}

void TControl::SetCursorPosition(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
    std::cout.flush(); // Ensure the output is sent to the console immediately

}

void TControl::ClearConsole() {
    std::cout << "\033[1;1H"; // Clear screen and move cursor to top-left
    //system("cls"); 
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

std::string TControl::GetFarbe(Farbe farbe) {
        switch (farbe) {
            case Farbe::Schwarz:   return "\033[30m";
            case Farbe::Rot:       return "\033[31m";
            case Farbe::Gruen:     return "\033[32m";
            case Farbe::Gelb:      return "\033[33m";
            case Farbe::Blau:      return "\033[34m";
            case Farbe::Magenta:   return "\033[35m";
            case Farbe::Cyan:      return "\033[36m";
            case Farbe::Weiss:     return "\033[37m";
            case Farbe::BG_Schwarz:   return "\033[40m";   // Schwarzer Hintergrund
            case Farbe::BG_Rot:       return "\033[41m";   // Roter Hintergrund
            case Farbe::BG_Gruen:     return "\033[42m";   // Grüner Hintergrund
            case Farbe::BG_Gelb:      return "\033[43m";   // Gelber Hintergrund
            case Farbe::BG_Blau:      return "\033[44m";   // Blauer Hintergrund
            case Farbe::BG_Magenta:   return "\033[45m";   // Magenta Hintergrund
            case Farbe::BG_Cyan:      return "\033[46m";   // Cyan Hintergrund
            case Farbe::BG_Weiss:     return "\033[47m";   // Weißer Hintergrund
            case Farbe::Zuruecksetzen: return "\033[0m"; // Zurücksetzen auf Standardfarbe
            default:               return "\033[0m";     // Standardfarbe
        }
    }

void TControl::SetFarbe(Farbe farbe) {
    switch (farbe) {
    case Farbe::Schwarz:   std::cout << "\033[30m"; break;
    case Farbe::Rot:       std::cout << "\033[31m"; break;
    case Farbe::Gruen:     std::cout << "\033[32m"; break;
    case Farbe::Gelb:      std::cout << "\033[33m"; break;
    case Farbe::Blau:      std::cout << "\033[34m"; break;
    case Farbe::Magenta:   std::cout << "\033[35m"; break;
    case Farbe::Cyan:      std::cout << "\033[36m"; break;
    case Farbe::Weiss:     std::cout << "\033[37m"; break;
    case Farbe::BG_Schwarz: std::cout << "\033[40m"; break; // Schwarzer Hintergrund
    case Farbe::BG_Rot:    std::cout << "\033[41m"; break; // Roter Hintergrund
    case Farbe::BG_Gruen:  std::cout << "\033[42m"; break; // Grüner Hintergrund
    case Farbe::BG_Gelb:   std::cout << "\033[43m"; break; // Gelber Hintergrund
    case Farbe::BG_Blau:   std::cout << "\033[44m"; break; // Blauer Hintergrund
    case Farbe::BG_Magenta: std::cout << "\033[45m"; break; // Magenta Hintergrund
    case Farbe::BG_Cyan:   std::cout << "\033[46m"; break; // Cyan Hintergrund
    case Farbe::BG_Weiss:  std::cout << "\033[47m"; break; // Weißer Hintergrund
    case Farbe::Zuruecksetzen: std::cout << "\033[0m"; break; // Zurücksetzen auf Standardfarbe
    default:               std::cout << "\033[0m"; break; // Standardfarbe
    }
}