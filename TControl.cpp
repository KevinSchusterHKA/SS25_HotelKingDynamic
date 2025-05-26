
#include "TControl.h"

TControl::TControl(){
    // Initialize ncurses;
    //initscr(); // Start ncurses mode
    //cbreak(); // Disable line buffering
    //noecho(); // Don't echo pressed keys
    //keypad(stdscr, TRUE); // Enable arrow keys
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->HideCursor(hConsole);
    
}
TControl::~TControl(){
    
}
void TControl::AusgabeSpielerBox(   std::string Namen ,
                                    int Budget ,
                                    int AnzahlGekaufterObjekte ,
                                    int AnzahlGebauterObjekte ,
                                    int x,
                                    int y,
                                    Farbe f) {
    this->SetFarbe(f);
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << "###################################################";
    coord.Y += 1;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << "#" << setw(49) << std::left<<Namen.substr(0,49) << "#";
    coord.Y += 1;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << "###################################################";
    coord.Y += 1;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << "#" << setw(25) << std::left << "Budget:" << setw(22) << std::right << Budget << "$ " << "#";
    coord.Y += 1;
    SetConsoleCursorPosition(this->hConsole, this->coord); 
    std::cout << "#" << setw(25) << std::left << "Anzahl gekaufter Objekte:" << setw(23) << std::right << AnzahlGekaufterObjekte << " #";
    coord.Y += 1;
    SetConsoleCursorPosition(this->hConsole, this->coord); 
    std::cout << "#" << setw(25) << std::left << "Anzahl gebauter Objekte:" << setw(23) << std::right << AnzahlGebauterObjekte << " #";
    coord.Y += 1;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << "###################################################";
    this->SetFarbe(Farbe::Zuruecksetzen);
    
}
void TControl::AusgabeFeld(std::string FeldBlock[]){
    //std::string out = _fgcolortable[4];
    //for (int i = 0; i < _dimY; i++)
    //{
    //    for (int j = 20; j < 31; j++)
    //    {
    //        out += FeldBlock[j].toStr(i);
    //    }
    //    out += "\n";
    //}
    //for (int i = 19; i > 10; i--)
    //{
    //    for (int j = 0; j < _dimY; j++)
    //    {
    //        out += FeldBlock[i].toStr(j) + Buffer + FeldBlock[50 - i].toStr(j);
    //        out += "\n";
    //    }

    //}
    //for (int i = 0; i < _dimY; i++)
    //{
    //    for (int j = 10; j >= 0; j--)
    //    {
    //        out += FeldBlock[j].toStr(i);

    //    }
    //    out += "\n";
    //}
    //out += "\033[0m";
    std::cout<< FeldBlock;
}
void TControl::AusgabeSpielerInformationen(std::string Namen[4],int Budget[4],int AnzahlGekaufterObjekte[4],int AnzahlGebauterObjekte[4],int AnzSpieler){    
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
void TControl::AusgabeSpielerInformationenMitPosition(std::string Namen[4], int Budget[4], int AnzahlGekaufterObjekte[4], int AnzahlGebauterObjekte[4], int AnzSpieler,int x,int y) {

    Farbe start = Farbe::Rot;
    for (int i = 0; i < AnzSpieler; i++) {
        this->AusgabeSpielerBox(Namen[i], Budget[i], AnzahlGekaufterObjekte[i], AnzahlGebauterObjekte[i], i * 52+x, y, static_cast<Farbe>(static_cast<int>(start) + i));
    }
}
int TControl::AusgabeStartMenu(int &option,int x,int y){
    enum OptionenMenu{Start=3,Highscore=4,Beenden=5};
    this->SetFarbe(Farbe::Weiss);
    std::string temp[7];
    int inputCh = 0;
        std::ostringstream oss;

    
    inputCh = 0;

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
    case KEY_ENTER:     if (option == Beenden) return Beenden;
                        else return 0;
        break;
    default:
        break;
    }
    for (int i = 0; i < 7; ++i) {
        temp[i] = MenueStartText[i];
        if (i == option) {
            temp[option].replace(temp[option].find(GetDigitsInt(option - 2)) - 1, 1, 1, '>');
        }
        temp[i] += "\n";
        oss << temp[i];
    }
    std::cout << oss.str();

    return true;
}
void TControl::AusgabeHighscore(std::string Namen[], int HighscoreWert[],int size,int x,int y) {
    int maxSizeNames = 0;
    this->SetFarbe(Farbe::BG_Weiss);
    this->SetFarbe(Farbe::Schwarz);
    for (size_t i = 0; i < size; i++)
    {
        if (maxSizeNames < Namen[i].size()){
            maxSizeNames = Namen[i].size();
        }
    }


    coord.X = x;
    coord.Y = y;
    //HEADER HIGHSCORE
    for (size_t i = 0; i < maxSizeNames+1+8+2+3; i++)
    {
        coord.X = x + i;
        coord.Y = y;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
        coord.X = x;
        coord.Y = y + 1;
        SetConsoleCursorPosition(this->hConsole, this->coord);
                                      //NAMEN SIZE  + # + xx- + Wert - Korrektur
        std::cout << "#" << std::setw((maxSizeNames + 1 + 3   + 8 - 6) / 2) << "" << std::setw((maxSizeNames +3+ 1 + 8 + 7) / 2)<<std::left<<"HIGHSCORE"<<"#";
        coord.X = x+i;
        coord.Y = y + 2;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }
    std::cout << std::endl;
    //AUSGABE HIGHSCORES
    for (size_t i = 0; i < size; i++)
    {
        coord.X = x;
        coord.Y = y +3+ i;

        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout << "#" << std::setw(3) << std::left << (to_string(i + 1) + "]") << std::setw(maxSizeNames) << std::left << Namen[i] <<"|" << std::setw(8) << std::right << HighscoreWert[i] << "#" << std::endl;

        if (i == size - 1) {
            coord.Y = y + 4 + i;
        }
    }
    //ABSCHLUSS AUSGABE FENSTER
    for (size_t i = 0; i < maxSizeNames + 1 +3+ 8 + 2; i++)
    {
        coord.X = x + i;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }
    this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeSpielOptionen(int& option, int x, int y) {
    int maxSizeOption = 0;
    this->SetFarbe(Farbe::BG_Rot);
    this->SetFarbe(Farbe::Schwarz);
    for (size_t i = 0; i < this->MenueSpielOptionen.size(); i++)
    {
        if (maxSizeOption < this->MenueSpielOptionen[i].size()) {
            maxSizeOption = this->MenueSpielOptionen[i].size();
        }
    }
    for (size_t i = 0; i < maxSizeOption; i++)
    {
        coord.X = x + i;
        coord.Y = y;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }
    for (size_t i = 0; i < maxSizeOption; i++)
    {
        coord.X = x + i;
        coord.Y = y+1;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }
    for (size_t i = 0; i < maxSizeOption; i++)
    {
        coord.X = x + i;
        coord.Y = y+2;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }
    for (size_t i = 0; i < this->MenueSpielOptionen.size()-3; i++)
    {
        coord.X = x;
        coord.Y = y + 3 + i;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#" << setw(10) << std::right << ("["+to_string(i + 1) + "]") << setw(39) << std::left << this->MenueSpielOptionen[i]<<"#";
    }
    coord.Y = coord.Y + 1;
    for (size_t i = 0; i < maxSizeOption; i++)
    {
        coord.X = x + i;

        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }
    this->SetFarbe(Farbe::Zuruecksetzen);
}



void TControl::ClearConsole() {
    std::cout << "\033[1;1H"; // Clear screen and move cursor to top-left
    //system("cls"); 
    std::cout.flush(); // Ensure the output is sent to the console immediately
}
void TControl::HideCursor(HANDLE hConsole) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
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