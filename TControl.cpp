
#include "TControl.h"

TControl::TControl(){
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    this->HideCursor(hConsole);
	//this->SetConsoleFontSize(1); // funktioniert nicht
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
void TControl::AusgabeStartBildschirm(bool flip,int x,int y) {
    static bool flipper = false;
    static int counter = 0;
	int FlipZeit = 3; // Zeit in Sekunden, nach der der Text wechselt
	flipper = !flipper; // Toggle the flipper state
    this->coord.X = x;
    this->coord.Y = y;
    counter++;



    if (counter >= 12 * FlipZeit)
    {
        for (int i = 0; i < 22; i++) {
            this->coord.Y = y + i;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << setw(86) << std::left << this->Hotelking[1][i];
        }
        if (counter >= 12 * FlipZeit*2) 
        {
            counter = 0; 
		}
        
    }
    else
    {
        for (int i = 0; i < 22; i++) {
            this->coord.Y = y + i;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout<<setw(86)<<std::left << this->Hotelking[0][i];
        }
    }
    

        
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
void TControl::AusgabeSpielerInformationen(std::string Namen[4], int Budget[4], int AnzahlGekaufterObjekte[4], int AnzahlGebauterObjekte[4], int AnzSpieler,int x,int y) {

    Farbe start = Farbe::Rot;
    for (int i = 0; i < AnzSpieler; i++) {
        this->AusgabeSpielerBox(Namen[i], Budget[i], AnzahlGekaufterObjekte[i], AnzahlGebauterObjekte[i], i * 51+x, y, static_cast<Farbe>(static_cast<int>(start) + i));
    }
}
void TControl::AusgabeStartMenu(int &option,int x,int y){
    this->SetFarbe(Farbe::Weiss);
    std::string temp[7];

    this->coord.X = x;
    this->coord.Y = y;

    for (int i = 0; i < 7; ++i) {
		this->coord.Y = y + i;
		SetConsoleCursorPosition(this->hConsole, this->coord);
        temp[i] = MenueStartText[i];
        if (i == option) {
            temp[option].replace(temp[option].find("["+GetDigitsInt(option - 2)) - 1, 1, 1, '>');
        }
		std::cout << temp[i];
    }
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

        std::cout << "#" << std::setw(4) << std::left << ("["+to_string(i + 1) + "]") << std::setw(maxSizeNames-1) << std::left << Namen[i].substr(0,maxSizeNames-1) << "|" << std::setw(8) << std::right << HighscoreWert[i] << "#" << std::endl;

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
    enum Optionen
    {
        SpielStarten=3,
        SpielSpeichern,
        SpielLaden
    };
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
    coord.X = x;
    coord.Y = y + 1;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout           << "#" 
                        << setw(maxSizeOption / 2 - this->MenueSpielOptionen[this->MenueSpielOptionen.size() - 1].size() / 2) <<"" 
                        << std::left << this->MenueSpielOptionen[this->MenueSpielOptionen.size() - 1] 
                        << setw(maxSizeOption / 2 - this->MenueSpielOptionen[this->MenueSpielOptionen.size() - 1].size() / 2-2) << ""
                        <<"#";
    
    for (size_t i = 0; i < maxSizeOption; i++) 
    {
        coord.X = x + i;
        coord.Y = y+2;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }


    for (size_t i = 0; i < this->MenueSpielOptionen.size() - 3; i++)
    {
        coord.X = x;
        coord.Y = y + 3 + i;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        //std::cout << "#" << setw(10) << std::right << ("[" + to_string(i + 1) + "]") << setw(39) << std::left << this->MenueSpielOptionen[i] << "#";
        std::cout   << "#"
                    << setw(15) << ""
                    << setw(4) << "["+to_string(i+1)+"]"
                    << setw(30) << this->MenueSpielOptionen[i]
                    << "#";
    }


    coord.X = x+15;
    coord.Y = y + option;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << setw(1) << ">";

    coord.Y = y+ this->MenueSpielOptionen.size();
    for (size_t i = 0; i < maxSizeOption; i++)
    {
        coord.X = x + i;

        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }


    this->SetFarbe(Farbe::Zuruecksetzen);
}



void TControl::ResetConsole() {
    std::cout << "\033[1;1H"; //  move cursor to top-left
    std::cout.flush();
}
void TControl::HideCursor(HANDLE hConsole) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
#include <windows.h>

void TControl::SetConsoleFontSize(int size) {
    CONSOLE_FONT_INFOEX cfi = { 0 };
    cfi.cbSize = sizeof(cfi);
    cfi.dwFontSize.Y = size;
    wcscpy_s(cfi.FaceName, L"Lucida Console");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
        std::cerr << "Error changing font size!\n";
    }
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
void TControl::UnitTest() {
    enum OptionenMenu { Reset = 0, Start = 3, Highscore = 4, Beenden = 5 };

    TControl TestControl;
    std::string playerNames[4] = { "a","bbbb","ccccc","ddddddddddddddddddddddddddddddddddddddddddddddddddd" };
    int budget[4] = { 100,10000,100000,99999999 };
    int gekObj[4] = { 5,15,2,3 };
    int gebObj[4] = { 0,2,3,99 };
    int option = 3;
    int Spiellaueft = 1;
    int ClearScreenCounter = 0;
    char inputCh = 0;

    while (Spiellaueft != 5) //5 ist Beenden Code
    {
        DWORD start_time = GetTickCount64();

        inputCh = Reset;
        if (_kbhit()) { // Check if a key is pressed
            inputCh = _getch();
        }

        switch (inputCh) {
        case KEY_UP:
            if (option > 3) {
                option--;
            }
            break;
        case KEY_DOWN:
            if (option < 5) {
                option++;
            }
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        case KEY_ENTER:     if (option == Beenden) Spiellaueft = Beenden;
            if (option == Highscore) {
                this->AusgabeHighscore(playerNames, budget, 4, 0, 50);
            }
                if (option == Start) { /*Spielstart*/ }
                break;
        default:
            break;
            }
            TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObj, gebObj, 4, 0, 0);
            //TestControl.AusgabeHighscore(playerNames, budget, 4, 30, 30);
			TestControl.AusgabeSpielOptionen(option, 90, 30);
            TestControl.AusgabeStartBildschirm(TRUE, 0, 10);
            TestControl.AusgabeStartMenu(option, 90, 20);

            DWORD elapsed_time = GetTickCount64() - start_time;
            if (elapsed_time < FRAME_DURATION) {
                Sleep(FRAME_DURATION - elapsed_time);
            }
            ClearScreenCounter++;
            if (ClearScreenCounter == 12 * 6)//*t in Sekunden
            {
                ClearScreenCounter = 0;
                system("cls");
            }
            TestControl.ResetConsole();
        }
    }
