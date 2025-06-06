
#include "TControl.h"

TControl::TControl(){
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND consoleWindow = GetConsoleWindow(); 
    ShowWindow(consoleWindow, SW_MAXIMIZE);  //Vollbildschirm Konsole
    this->HideCursor(hConsole);
	//this->SetConsoleFontSize(1); // funktioniert nicht
    //HWND hConsole = GetConsoleWindow();

}
TControl::~TControl(){
    
}

void TControl::AusgabeStartBildschirm(bool flip,int x,int y) {
    
    int SizeString = sizeof(this->Hotelking[0]) / sizeof(this->Hotelking[0][0]);
    static int counter = 0;
	int FlipZeit = 1; // Zeit in Sekunden, nach der der Text wechselt
    this->coord.X = x;
    this->coord.Y = y;
    counter++;


    if (counter >= this->ZeitKorrekturKonstante * FlipZeit)
    {
        for (int i = 0,j=0; i < SizeString; i++,j++) {
            if (j==7)
            {
                j = 0;
            }
            this->SetFarbe(static_cast<Farbe>(static_cast<int>(Farbe::Rot) + j));
            this->coord.Y = y + i;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << setw(86) << std::left << this->Hotelking[1][i];
        }
        this->SetFarbe(Farbe::Zuruecksetzen);

        if (counter >= this->ZeitKorrekturKonstante * FlipZeit*2)
        {
            counter = 0; 
		}
        
    }
    else
    {
        for (int i = 0,j=0; i < SizeString; i++,j++) {
            if (j == 7)
            {
                j = 0;
            }
            this->SetFarbe(static_cast<Farbe>(static_cast<int>(Farbe::Rot) + j));
            this->coord.Y = y + i;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout<<setw(86)<<std::left << this->Hotelking[0][i];
            this->SetFarbe(Farbe::Zuruecksetzen);
        }
    }
    

        
}
void TControl::AusgabeFeld(std::string FeldBlock[], int sizeFeld){
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
    for (size_t i = 0; i < sizeFeld; i++)
    {
        std::cout << FeldBlock[i];
    }
}
void TControl::AusgabeSpielerInformationen( std::string Namen[4], 
                                            int Budget[4], 
                                            int AnzahlGekaufterObjekte[4], 
                                            int AnzahlGebauterObjekte[4], 
                                            int AnzSpieler,
                                            int x,
                                            int y,
                                            std::vector<std::vector<std::string>> GekaufteObjekte,
                                            std::vector<std::vector<std::string>> GebauteObjekte) {

    Farbe start = Farbe::Rot;
    for (int i = 0; i < AnzSpieler; i++) {
        this->AusgabeSpielerBox(Namen[i], Budget[i], AnzahlGekaufterObjekte[i], AnzahlGebauterObjekte[i], i * 51+x, y, static_cast<Farbe>(static_cast<int>(start) + i));
		this->AusgabeSpielerInventarAnzeige(Namen[i], GekaufteObjekte[i], GebauteObjekte[i], i * 51 + x, y + 7, static_cast<Farbe>(static_cast<int>(start) + i));
    }
}
void TControl::AusgabeSpielerBox(   std::string Namen,
                                    int Budget,
                                    int AnzahlGekaufterObjekte,
                                    int AnzahlGebauterObjekte,
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
    std::cout << "#" << setw(49) << std::left << Namen.substr(0, 49) << "#";
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
void TControl::AusgabeSpielerInventarAnzeige(   std::string Namen,
                                                std::vector<std::string> GekaufteObjekte,
                                                std::vector<std::string> GebauteObjekte,
                                                int x,
                                                int y,
                                                Farbe f){
    int maxSizeOption = 49;
    this->coord.X = x;
    this->coord.Y = y;

    SetConsoleCursorPosition(this->hConsole, this->coord);
	std::cout   << "|" << this->GetFarbe(f)
                << setw(maxSizeOption / 2 - static_cast<std::string>("Gekaufte Objekte").size()/2) << ""
                << std::left << "Gekaufte Objekte"
                << setw(maxSizeOption / 2 - static_cast<std::string>("Gekaufte Objekte").size()/2) << ""
                << this->GetFarbe(Farbe::Zuruecksetzen) << "|";
	this->coord.Y++;
    for (size_t i = 0; i < maxSizeOption+1; i++)
    {
		SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "-";
        this->coord.X++;
    }
	this->coord.X = x;

    for (size_t i = 0; i < GekaufteObjekte.size(); i++)
    {
        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);

		std::cout << setw(1) <<"|" << this->GetFarbe(f) << std::setw(maxSizeOption) << std::left << GekaufteObjekte[i].substr(0,maxSizeOption) << this->GetFarbe(Farbe::Zuruecksetzen) <<setw(1)<<std::right<< " |";
    }

    this->coord.Y++;
    for (size_t i = 0; i < maxSizeOption + 1; i++)
    {
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "-";
        this->coord.X++;
    }
    this->coord.X = x;
	this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << "|" << this->GetFarbe(f)
        << setw(maxSizeOption / 2 - static_cast<std::string>("Gebaute Objekte").size() / 2) << " "
        << std::left << "Gebaute Objekte"
        << setw(maxSizeOption / 2 - static_cast<std::string>("Gebaute Objekte").size() / 2 - 2) << ""
        << this->GetFarbe(Farbe::Zuruecksetzen) << "|";
    this->coord.Y++;
    for (size_t i = 0; i < maxSizeOption + 1; i++)
    {
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "-";
        this->coord.X++;
    }
    this->coord.X = x;
    for (size_t i = 0; i < GekaufteObjekte.size(); i++)
    {
        this->coord.Y ++;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "|" << this->GetFarbe(f) << std::setw(maxSizeOption) << std::left << GebauteObjekte[i].substr(0, maxSizeOption)<< this->GetFarbe(Farbe::Zuruecksetzen) << "|";
    }
    this->SetFarbe(Farbe::Zuruecksetzen);
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
void TControl::AusgabeStartMenu(int& option, int x, int y) {
    this->SetFarbe(Farbe::Weiss);
    std::string temp[7];

    this->coord.X = x;
    this->coord.Y = y;

    for (int i = 0; i < 7; ++i) {
        this->coord.Y = y + i;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        temp[i] = MenueStartText[i];
        if (i == option) {
            temp[option].replace(temp[option].find("[" + GetDigitsInt(option - 2)) - 1, 1, 1, '>');
        }
        std::cout << temp[i];
    }
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
void TControl::AusgabeHandelsOptionen(int& option, int x, int y) {
    int maxSizeOption = 0;
    enum HandelsOptionen
    {
        kaufen = 3,
        bauen,
        handeln
    };
    this->SetFarbe(Farbe::BG_Rot);
    this->SetFarbe(Farbe::Schwarz);
    for (size_t i = 0; i < this->MenueHandelsOptionen.size(); i++)
    {
        if (maxSizeOption < this->MenueHandelsOptionen[i].size()) {
            maxSizeOption = this->MenueHandelsOptionen[i].size();
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
    std::cout << "#"
        << setw(maxSizeOption / 2 - this->MenueHandelsOptionen[this->MenueHandelsOptionen.size() - 1].size() / 2) << ""
        << std::left << this->MenueHandelsOptionen[this->MenueHandelsOptionen.size() - 1]
        << setw(maxSizeOption / 2 - this->MenueHandelsOptionen[this->MenueHandelsOptionen.size() - 1].size() / 2 - 2) << ""
        << "#";

    for (size_t i = 0; i < maxSizeOption; i++)
    {
        coord.X = x + i;
        coord.Y = y + 2;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << "#";
    }


    for (size_t i = 0; i < this->MenueHandelsOptionen.size() - 3; i++)
    {
        coord.X = x;
        coord.Y = y + 3 + i;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        //std::cout << "#" << setw(10) << std::right << ("[" + to_string(i + 1) + "]") << setw(39) << std::left << this->MenueSpielOptionen[i] << "#";
        std::cout << "#"
            << setw(15) << ""
            << setw(4) << "[" + to_string(i + 1) + "]"
            << setw(30) << this->MenueHandelsOptionen[i]
            << "#";
    }


    coord.X = x + 15;
    coord.Y = y + option;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << setw(1) << ">";

    coord.Y = y + this->MenueHandelsOptionen.size();
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
    std::vector<std::vector<std::string>> GekObjNamen = { { "Straße1","Gebäude xyz1","Autobahn nach Karlsruhe1","1TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"},
                                                          { "Straße2","Gebäude xyz2","Autobahn nach Karlsruhe2","2TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"},
                                                          { "Straße3","Gebäude xyz3","Autobahn nach Karlsruhe3","3TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"},
                                                          { "Straße4","Gebäude xyz4","Autobahn nach Karlsruhe4","4TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"}};
    std::vector<std::vector<std::string>> GebObjNamen = { { "Haus 1","Gebäude zyx1","Hotel 1","1TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"},
                                                          { "Haus 2","Gebäude zyx2","Hotel 2","2TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"},
                                                          { "Haus 3","Gebäude zyx3","Hotel 3","3TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"},
                                                          { "Haus 4","Gebäude zyx4","Hotel 4","4TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"}};
    int budget[4] = { 100,10000,100000,99999999 };
    int gekObjAnz[4] = { 5,15,2,3 };
    int gebObjAnz[4] = { 0,2,3,99 };

    int option = 3;
    int Spiellaueft = 1;

    int ClearScreenCounter = 0;

    char EingabeCh = 0;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int x=0,y=0;
    GetMaximizedConsoleSize(x, y);
    do
    {
        
        DWORD start_time = GetTickCount64();

        TestControl.AusgabeStartBildschirm(TRUE, x/2-43 , y/2-11);

        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
        ClearScreenCounter++;
        if (ClearScreenCounter == this->ZeitKorrekturKonstante * 6)//*t in Sekunden
        {
            ClearScreenCounter = 0;
            //system("cls");
        }
        TestControl.ResetConsole();
    } while (!_kbhit());
    system("cls");
    Menues MenueAuswahl = Menues::Start;
    while (Spiellaueft != 5) //5 ist Beenden Code
    {
        EingabeCh = Reset;
        if (_kbhit()) { // Check if a key is pressed
            EingabeCh = _getch();
        }

        DWORD start_time = GetTickCount64();
        switch (MenueAuswahl)
        {
        case TControl::Menues::Start:
            this->AusgabeStartMenu(option,0,0);
            break;
        case TControl::Menues::Handel:
            break;
        case TControl::Menues::Optionen:
            break;
        default:
            break;
        }
        

        switch (EingabeCh) {
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
                            if (option == Start) { 
                                //TestControl.AusgabeStartMenu(option, 90, 20);
                            }
                break;
        default:
            break;
        }

        //TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObjAnz, gebObjAnz, 4, 0, 0, GekObjNamen, GebObjNamen);
        //TestControl.AusgabeHighscore(playerNames, budget, 4, 30, 30);
        //TestControl.AusgabeSpielOptionen(option, 90, 30);
        //TestControl.AusgabeHandelsOptionen(option, 90, 40);
		//TestControl.AusgabeWuerfel(3, 50, 60, Farbe::Gruen);




        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }


        ClearScreenCounter++;
        if (ClearScreenCounter == this->ZeitKorrekturKonstante * 6)//*t in Sekunden
        {
            ClearScreenCounter = 0;
            //system("cls");
        }
        TestControl.ResetConsole();
        }
    }
void TControl::AusgabeWuerfel(int wuerfel, int x, int y, Farbe f) {
	this->SetFarbe(f);
    std::string WuerfelFlaeche[6][5] = {
    {
        "---------",
        "|       |",
        "|   *   |",
        "|       |",
        "---------"
    },
    {
        "---------",
        "| *     |",
        "|       |",
        "|     * |",
        "---------"
    },
    {
        "---------",
        "| *     |",
        "|   *   |",
        "|     * |",
        "---------"
    },
    {
        "---------",
        "| *   * |",
        "|       |",
        "| *   * |",
        "---------"
    },
    {
        "---------",
        "| *   * |",
        "|   *   |",
        "| *   * |",
        "---------"
    },
    {
        "---------",
        "| *   * |",
        "| *   * |",
        "| *   * |",
        "---------"
    }
    };
    this->coord.X = x;
    this->coord.Y = y;
	static int counter = 0;
	static bool AusgabeWurf= false;
    int RandZeitSimulation1 = 5; // Zeit in Sekunden, nach der der Text wechselt
    int RandZeitSimulation2 = RandZeitSimulation1+3; // Zeit in Sekunden, nach der der Text wechselt
    counter++;
	std::mt19937 rng(time(nullptr)); // Zufallszahlengenerator initialisieren
    std::uniform_int_distribution<int> dist(0,5);
	int rand = dist(rng); 

    if (counter >= this->ZeitKorrekturKonstante * RandZeitSimulation1)
    {
        this->SetFarbe(Farbe::BG_Rot);
        this->SetFarbe(Farbe::Weiss);
        for (int i = 0; i < 5; i++) {
            this->coord.Y = y + i;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << setw(10) << WuerfelFlaeche[wuerfel-1][i];
        }
        if (counter >= this->ZeitKorrekturKonstante * RandZeitSimulation2)
        {
            counter = 0;
            for (int i = 0; i < 5; i++) {
                this->coord.Y = y + i;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                std::cout << setw(10) << " " ;
            }
            this->SetFarbe(Farbe::Zuruecksetzen);

        }
		this->SetFarbe(f);

    }
    else
    {
        for (int i = 0; i < 5; i++) {
            this->coord.Y = y + i;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << setw(10) << WuerfelFlaeche[rand][i];
        }
    }

	this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::GetMaximizedConsoleSize(int& width, int& height) {
    HWND consoleWindow = GetConsoleWindow();
    if (!consoleWindow) {
        std::cerr << "Error: Could not get console window handle\n";
        return;
    }

    // Maximize the console window
    if (!ShowWindow(consoleWindow, SW_MAXIMIZE)) {
        std::cerr << "Warning: ShowWindow failed\n";
        // Continue anyway
    }

    // Small delay to allow window to maximize

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Could not get console handle\n";
        return;
    }

    // Method 1: Using GetLargestConsoleWindowSize
    COORD largest = GetLargestConsoleWindowSize(hConsole);
    if (largest.X == 0 && largest.Y == 0) {
        std::cerr << "Error: GetLargestConsoleWindowSize failed\n";
    }
    else {
        width = largest.X;
        height = largest.Y;
    }

    // Method 2: Using GetClientRect and current font size
    RECT rect;
    if (!GetClientRect(consoleWindow, &rect)) {
        std::cerr << "Error: GetClientRect failed\n";
        return;
    }

    CONSOLE_FONT_INFO fontInfo;
    if (!GetCurrentConsoleFont(hConsole, FALSE, &fontInfo)) {
        std::cerr << "Error: GetCurrentConsoleFont failed\n";
        return;
    }

    width = rect.right / fontInfo.dwFontSize.X;
    height = rect.bottom / fontInfo.dwFontSize.Y;
}