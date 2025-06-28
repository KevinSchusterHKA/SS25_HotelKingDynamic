#include "TControl.h"

TControl::TControl(){
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND consoleWindow = GetConsoleWindow(); 
    ShowWindow(consoleWindow, SW_MAXIMIZE);  //Vollbildschirm Konsole
    this->HideCursor();
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
            std::cout << std::setw(86) << std::left << this->Hotelking[1][i];
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
            std::cout<<std::setw(86)<<std::left << this->Hotelking[0][i];
            this->SetFarbe(Farbe::Zuruecksetzen);
        }
    }
    

        
}
void TControl::AusgabeFeld(std::string FeldBlock,int x,int y){
	this->coord.X = x;               
	this->coord.Y = y;      
    SetConsoleCursorPosition(this->hConsole, this->coord);

    for (char var : FeldBlock)
    {
        if (var !='\n')
        {
            std::cout << var;
        }
        else
        {
            this->coord.Y++;
            this->coord.X = x;
            SetConsoleCursorPosition(this->hConsole, this->coord);
        }
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
                                            std::vector<std::vector<std::string>> GebauteObjekte,
                                            std::vector<int> SpielerReihenfolge) {

    Farbe start[] = { Farbe::Rot, Farbe::Gruen, Farbe::Gelb, Farbe::Cyan };
    int BreiteMenueSpielerBox = this->SpielerInformationen[this->SpielerInformationen.size() - 2].size();

    for (int i = 0; i < AnzSpieler; i++) { //todo give list of amount of cpu players
        this->AusgabeSpielerBox(Namen[SpielerReihenfolge[i]], Budget[i], AnzahlGekaufterObjekte[i], AnzahlGebauterObjekte[i], i * BreiteMenueSpielerBox+x, y, start[SpielerReihenfolge[i]]);
		this->AusgabeSpielerInventarAnzeige(Namen[i], GekaufteObjekte[i], GebauteObjekte[i], i * BreiteMenueSpielerBox + x, y + 7, start[SpielerReihenfolge[i]]);
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
    this->coord.X = x;
    this->coord.Y = y;
    int BreiteMenue = this->SpielerInformationen[this->SpielerInformationen.size() - 2].size();
    int linkerRandText = (BreiteMenue - 2) / 2 - this->SpielerInformationen.back().size() / 2;

    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue-1; i++)
    {
        std::cout << _symbolcharsControl[HL];

    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;

    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue-2) << std::left << Namen.substr(0, BreiteMenue-2) << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LT];

    for (size_t i = 1; i < BreiteMenue-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
	}
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL] << std::setw(26) << std::left << "Budget:" << std::setw(BreiteMenue-30) << std::right << Budget << "$" <<std::setw(2)<<std::right<< _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL] << std::setw(26) << std::left << "Anzahl gekaufter Objekte:" << std::setw(BreiteMenue - 29) << std::right << AnzahlGekaufterObjekte << std::setw(2) <<std::right<< _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL] << std::setw(26) << std::left << "Anzahl gebauter Objekte:" << std::setw(BreiteMenue - 29) << std::right << AnzahlGebauterObjekte << std::setw(2) << std::right << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];

    this->SetFarbe(Farbe::Zuruecksetzen);
}

void TControl::AusgabeSpielerInventarAnzeige(   std::string Namen,
                                                std::vector<std::string> GekaufteObjekte,
                                                std::vector<std::string> GebauteObjekte,
                                                int x,
                                                int y,
                                                Farbe f){
    int maxSizeOption = this->SpielerInformationen[this->SpielerInformationen.size() - 2].size();
    this->coord.X = x;
    this->coord.Y = y;

    
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 0; i < maxSizeOption - 2; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];
    
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
	std::cout   << _symbolcharsControl[VL] << this->GetFarbe(f)
                << std::setw(maxSizeOption / 2 - static_cast<std::string>("Gekaufte Objekte").size()/2) << ""
                << std::left << "Gekaufte Objekte"
                << std::setw(maxSizeOption / 2 - static_cast<std::string>("Gekaufte Objekte").size()/2-1) << ""
                << this->GetFarbe(Farbe::Zuruecksetzen) << _symbolcharsControl[VL];
	this->coord.Y++;
	SetConsoleCursorPosition(this->hConsole, this->coord);
	std::cout << _symbolcharsControl[LT];
    for (size_t i = 0; i < maxSizeOption-2; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];
    
    SetConsoleCursorPosition(this->hConsole, this->coord);
    for (size_t i = 0,temp=0; i < GekaufteObjekte.size(); i++,temp=0)
    {
        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout   <<  _symbolcharsControl[VL]
                    << this->GetFarbe(f)
                    << std::setw(maxSizeOption - 2) << std::left
                    << GekaufteObjekte[i].substr(0, maxSizeOption - 2) 
                    << this->GetFarbe(Farbe::Zuruecksetzen)
                    <<  _symbolcharsControl[VL];
    }

    this->coord.Y++;

    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 0; i < maxSizeOption -2; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[VL];

	this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    
    std::cout << _symbolcharsControl[VL] << this->GetFarbe(f)
        << std::setw(maxSizeOption / 2 - static_cast<std::string>("Gebaute Objekte").size() / 2) << " "
        << std::left << "Gebaute Objekte"
        << std::setw(maxSizeOption / 2 - static_cast<std::string>("Gebaute Objekte").size() / 2 - 2) << ""
        << this->GetFarbe(Farbe::Zuruecksetzen) << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 0; i < maxSizeOption-2; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[VL];

    for (size_t i = 0; i < GebauteObjekte.size(); i++)
    {
        if (GebauteObjekte[i]!="LOS")
        {
            this->coord.Y ++;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << _symbolcharsControl[VL] << this->GetFarbe(f) << std::setw(maxSizeOption-2) << std::left << GebauteObjekte[i].substr(0, maxSizeOption-2)<< this->GetFarbe(Farbe::Zuruecksetzen) << _symbolcharsControl[VL];
        }
    }

    this->coord.Y++;

    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 0; i < maxSizeOption - 2; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
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

    this->coord.X = x;
    this->coord.Y = y;
    //HEADER HIGHSCORE
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < maxSizeNames + 8 + 2 + 3; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
                                    //NAMEN SIZE  + # + xx- + Wert - Korrektur
    std::cout << _symbolcharsControl[VL] << std::setw((maxSizeNames + 1 + 3   + 8 - 6) / 2) << "" << std::setw((maxSizeNames +3+ 1 + 8 + 7) / 2)<<std::left<<"HIGHSCORE"<< _symbolcharsControl[VL];
    this->coord.X = x;
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < maxSizeNames + 8 + 2 + 3; i++)
    {
        if (i== maxSizeNames+4)
        {
            std::cout << _symbolcharsControl[IT];
        }
        else
        {
            std::cout << _symbolcharsControl[HL];
        }
    }
    std::cout << _symbolcharsControl[RT];

    //AUSGABE HIGHSCORES
    for (size_t i = 0; i < size; i++)
    {
        this->coord.Y++;

        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout << _symbolcharsControl[VL] << std::setw(4) << std::left << ("["+std::to_string(i + 1) + "]") << std::setw(maxSizeNames-1) << std::left << Namen[i].substr(0,maxSizeNames-1) << _symbolcharsControl[VL] << std::setw(8) << std::right << HighscoreWert[i] << _symbolcharsControl[VL] ;
    }

    //ABSCHLUSS AUSGABE FENSTER
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < maxSizeNames +3+ 8 + 2; i++)
    {
        if (i == maxSizeNames + 4)
        {
            std::cout << _symbolcharsControl[T];
        }
        else
        {
            std::cout << _symbolcharsControl[HL];
        }
    }
    std::cout << _symbolcharsControl[LRC];

    this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeStartMenu(int& option, int x, int y) {
    this->SetFarbe(Farbe::Weiss);
    int BreiteMenue = this->MenueStartOptionen[this->MenueStartOptionen.size() - 2].size();
    int linkerRandText = (BreiteMenue - 2) / 2 - this->MenueStartOptionen.back().size() / 2;
    this->coord.X = x;
	this->coord.Y = y;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.X = x;
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

	std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) <<" " <<std::left << this->MenueStartOptionen[this->MenueStartOptionen.size()-1] << std::setw(linkerRandText+1) <<std::right<< _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];
	this->coord.X = x;
    for (size_t i = 0; i < this->MenueStartOptionen.size()-2; i++)
    {
		this->coord.Y++;
		linkerRandText = (BreiteMenue - 2) / 2 - 13 / 2;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        if (option==i)
        {
            std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText-3) << ">" <<"["+ std::to_string(i+1) +"]" << std::setw(13) << std::left << this->MenueStartOptionen[i] << std::setw(linkerRandText) << std::right << _symbolcharsControl[VL];

        }
        else
        {
            std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText - 3) << " " << "[" + std::to_string(i+1) + "]" << std::setw(13) << std::left << this->MenueStartOptionen[i] << std::setw(linkerRandText) << std::right << _symbolcharsControl[VL];
        }

    }
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];

}
void TControl::AusgabeSpielOptionen(int& option, int x, int y) {
    int maxSizeOption = 0;
    this->coord.Y = y;
    this->coord.X = x;
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
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < maxSizeOption-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];
    this->coord.X = x;
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout           << _symbolcharsControl[VL]
                        << std::setw(maxSizeOption / 2 - this->MenueSpielOptionen[this->MenueSpielOptionen.size() - 1].size() / 2) <<"" 
                        << std::left << this->MenueSpielOptionen[this->MenueSpielOptionen.size() - 1] 
                        << std::setw(maxSizeOption / 2 - this->MenueSpielOptionen[this->MenueSpielOptionen.size() - 1].size() / 2-2) << ""
                        << _symbolcharsControl[VL];
    this->coord.Y++;

    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < maxSizeOption - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

	int MaxLaenge = 16;
    int AbstandTextMitte = maxSizeOption / 2 - MaxLaenge / 2;
    coord.X = x;

    for (size_t i = 0; i < this->MenueSpielOptionen.size() - 2; i++)
    {
        coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        if (i == option)
        {
            
            std::cout << _symbolcharsControl[VL]
                << std::setw(AbstandTextMitte - 3) << std::right << ">"
                << std::setw(3) << "[" + std::to_string(i + 1) + "]"
                << std::setw(16) << std::left 
                << std::left << this->MenueSpielOptionen[i]
                << std::setw(AbstandTextMitte - 2) << ""
                << _symbolcharsControl[VL];
        }
        else
        {
            std::cout << _symbolcharsControl[VL]
                << std::setw(AbstandTextMitte-3) << ""
                << std::setw(3) << "[" + std::to_string(i + 1) + "]"
                << std::setw(16) << std::left
                << std::left << this->MenueSpielOptionen[i]
                << std::setw(AbstandTextMitte - 2) << ""
                << _symbolcharsControl[VL];
        }


    }

    coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);


    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < maxSizeOption-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];


    this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeSpielerOptionen(int& option, int x, int y,Farbe f) {
    int maxSizeOption = 0;
    this->SetFarbe(f);
    this->SetFarbe(Farbe::Schwarz);
    this->coord.Y = y;
	this->coord.X = x;
    for (size_t i = 0; i < this->MenueSpielerOptionen.size(); i++)
    {
        if (maxSizeOption < this->MenueSpielerOptionen[i].size()) {
            maxSizeOption = this->MenueSpielerOptionen[i].size();
        }
    }
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < maxSizeOption-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];
    this->coord.X = x;
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL]
        << std::setw(maxSizeOption / 2 - this->MenueSpielerOptionen[this->MenueSpielerOptionen.size() - 1].size() / 2) << ""
        << std::left << this->MenueSpielerOptionen[this->MenueSpielerOptionen.size() - 1]
        << std::setw(maxSizeOption / 2 - this->MenueSpielerOptionen[this->MenueSpielerOptionen.size() - 1].size() / 2 - 2) << ""
        << _symbolcharsControl[VL];
    this->coord.Y++;
    this->coord.X = x;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < maxSizeOption-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    coord.X = x;
    int MaxLaenge = 16;
    int AbstandTextMitte = maxSizeOption / 2 - MaxLaenge / 2;

	//Ausgabe der Handelsoptionen
    for (size_t i = 0; i < this->MenueSpielerOptionen.size() - 2; i++)
    {
        coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        if (i == option)
        {

			std::cout << _symbolcharsControl[VL] 
                << std::setw(AbstandTextMitte - 3) << std::right << ">"
                << std::setw(3) << "[" + std::to_string(i + 1) + "]"
                << std::setw(16) << std::left
                << std::left << this->MenueSpielerOptionen[i]
                << std::setw(AbstandTextMitte - 2) << ""
                << _symbolcharsControl[VL];
        }
        else
        {
            std::cout << _symbolcharsControl[VL]
                << std::setw(AbstandTextMitte - 3) << ""
                << std::setw(3) << "[" + std::to_string(i + 1) + "]"
                << std::setw(16) << std::left
                << std::left << this->MenueSpielerOptionen[i]
                << std::setw(AbstandTextMitte - 2) << ""
                << _symbolcharsControl[VL];
        }
        
    }
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < maxSizeOption-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];


    this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeSpielRegeln(std::vector<std::string> s, int x, int y) {

	this->SetFarbe(Farbe::BG_Weiss);
	this->SetFarbe(Farbe::Schwarz);
    this->coord.X = x;
    this->coord.Y = y;
    int BreiteMenue = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (BreiteMenue < s[i].size()) {
            BreiteMenue = s[i].size();
        }
    }
    if (BreiteMenue < 21)
    {
        BreiteMenue = 21;
    }
    
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue + 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
	}
    std::cout << _symbolcharsControl[URC];

    this->coord.X = x;
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL] << std::setw((BreiteMenue - 2) / 2-4) << "" << std::left << "Spielregeln" << std::setw((BreiteMenue - 2) / 2 - 4) << "" << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue + 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
	}
    std::cout << _symbolcharsControl[RT];
    this->coord.X = x;
    for (size_t i = 0; i < s.size(); i++)
    {
        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << _symbolcharsControl[VL] << std::setw(1) << std::left << s[i].substr(0, BreiteMenue) << std::setw(BreiteMenue - s[i].size()) << "" << _symbolcharsControl[VL];
    }
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue + 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
}
void TControl::AusgabeJaNeinOption(int& option, int x, int y, Farbe f,std::string Ueberschrift) {
    this->SetFarbe(f);
    this->SetFarbe(Farbe::Schwarz);
    int BreiteMenue = Ueberschrift.size()+20;
    int linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
    this->coord.X = x;
    this->coord.Y = y;

    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue-1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
    
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    linkerRandText = (BreiteMenue - 2) / 2 - 13 / 2;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    if (option == 0)
    {
        std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText - 3) << ">" << "[" + std::to_string(1) + "]" << std::setw(13) << std::left << "ja" << std::setw(linkerRandText) << std::right << _symbolcharsControl[VL];
        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText - 3) << " " << "[" + std::to_string(2) + "]" << std::setw(13) << std::left << "nein" << std::setw(linkerRandText) << std::right << _symbolcharsControl[VL];

    }
    else
    {
        std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText - 3) << " " << "[" + std::to_string(1) + "]" << std::setw(13) << std::left << "ja" << std::setw(linkerRandText) << std::right << _symbolcharsControl[VL];
        this->coord.X = x;
        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText - 3) << ">" << "[" + std::to_string(2) + "]" << std::setw(13) << std::left << "nein" << std::setw(linkerRandText) << std::right << _symbolcharsControl[VL];
    }

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
    this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeJaNeinOptionCPU(int& option, int x, int y, Farbe f, std::string Ueberschrift, int Strasse, int Angebot) {
    this->SetFarbe(f);
    this->SetFarbe(Farbe::Schwarz);
    int BreiteMenue = Ueberschrift.size() + 10,tempy=0;
    int linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
    this->coord.X = x;
    this->coord.Y = y;
    std::string temp = "Strasse: xx fuer xxxx$ (Bestaetige mit Enter)";
    
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - temp.size() / 2) << " " <<setw(66)<< std::left << "Strasse:" + std::to_string(Strasse) + " fuer " + std::to_string(Angebot) + "$ (Bestaetige mit Enter)"<<std::right<< _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    tempy = this->coord.Y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[SP];
    }
    std::cout << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
    this->coord.X++;
    this->coord.Y = tempy;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    this->ShowCursor();
    std::cin >> temp;
    if (temp =="ja")
    {
        option = 0;
    }
    else {
        option = 1;
    }
    this->HideCursor();
    std::cin.clear();
    std::cin.ignore(1000, '\n');
	this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeStrasseHandeln(int& option, int& WelcheStrasse,int& Angebot, int x, int y, Farbe f) {
    this->SetFarbe(f);
    this->SetFarbe(Farbe::Schwarz);

    std::string Ueberschrift = "Welche Strasse moechten Sie handeln? (Geben sie die Nummer unter der Strasse ein)";
    int BreiteMenue = Ueberschrift.size() + 20;
    int linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
    this->coord.X = x;
    this->coord.Y = y;
    int tempy = 0;

	//EINGABE DER STRASSE
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue/2-11) << " " << std::left << "Bestaetige mit Enter" << std::setw(BreiteMenue / 2 - 10+1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
	tempy = this->coord.Y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[SP];
    }
    std::cout << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
	this->coord.X++;
	this->coord.Y = tempy;
    SetConsoleCursorPosition(this->hConsole, this->coord);
	this->ShowCursor();
    std::cin >> WelcheStrasse;
	this->HideCursor();
    std::cin.clear();
    std::cin.ignore(1000, '\n');

	//EINGABE DES ANGEBOTS
    Ueberschrift = "Gebe einen Betrag ein.";
	this->coord.X = x;
    this->coord.Y += 2;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue/2- Ueberschrift.size()/2) << _symbolcharsControl[SP] << std::left << Ueberschrift << std::setw(BreiteMenue / 2 - Ueberschrift.size() / 2-1) <<_symbolcharsControl[SP] << std::right << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    tempy = this->coord.Y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[SP];
    }
    std::cout << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
    this->coord.X++;
    this->coord.Y = tempy;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    this->ShowCursor();
    std::cin >> Angebot;
    this->HideCursor();
    this->SetFarbe(Farbe::Zuruecksetzen);
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}
void TControl::AusgabeVerkaufen(int& option, int& WelcheStrasse, int& Gebaude, int x, int y, Farbe f) {
    this->SetFarbe(f);
    this->SetFarbe(Farbe::Schwarz);

    std::string Ueberschrift = "Welche Strasse moechten Sie an die Bank Verkaufen? (Geben sie die Nummer unter der Strasse ein)";
    int BreiteMenue = Ueberschrift.size() + 10;
    int linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
    this->coord.X = x;
    this->coord.Y = y;
    int tempy = 0;

    //EINGABE DER STRASSE
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - 11) << " " << std::left << "Bestaetige mit Enter" << std::setw(BreiteMenue / 2 - 10 + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    tempy = this->coord.Y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[SP];
    }
    std::cout << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
    this->coord.X++;
    this->coord.Y = tempy;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    this->ShowCursor();
    std::cin >> WelcheStrasse;
    this->HideCursor();
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    //EINGABE DER ANZAHL GEBAUDE
    Ueberschrift = "Gebe die Anzahl an Gebaeude ein welche du verkaufen willst.";
    this->coord.X = x;
    this->coord.Y += 2;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - Ueberschrift.size() / 2) << _symbolcharsControl[SP] << std::left << Ueberschrift << std::setw(BreiteMenue / 2 - Ueberschrift.size() / 2 - 2) << _symbolcharsControl[SP] << std::right << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    tempy = this->coord.Y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[SP];
    }
    std::cout << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
    this->coord.X++;
    this->coord.Y = tempy;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    this->ShowCursor();
    std::cin >> Gebaude;
    this->HideCursor();
    this->SetFarbe(Farbe::Zuruecksetzen);
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}
void TControl::AusgabeGebaeudeBauen(int& option, int& WelcheStrasse, int x, int y, Farbe f) {
    this->SetFarbe(f);
    this->SetFarbe(Farbe::Schwarz);

    std::string Ueberschrift = "Auf welche Strasse moechten Sie bauen? (Geben sie die Nummer unter der Strasse ein)";
    int BreiteMenue = Ueberschrift.size() + 20;
    int linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
    this->coord.X = x;
    this->coord.Y = y;
    int tempy = 0;

    //EINGABE DER STRASSE
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - 11) << " " << std::left << "Bestaetige mit Enter" << std::setw(BreiteMenue / 2 - 10 + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LT];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[RT];

    this->coord.Y++;
    tempy = this->coord.Y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[SP];
    }
    std::cout << _symbolcharsControl[VL];

    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);

    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];
    this->coord.X++;
    this->coord.Y = tempy;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    this->ShowCursor();
    std::cin >> WelcheStrasse;
    this->HideCursor();
    std::cin.clear();
    std::cin.ignore(1000, '\n');

    this->HideCursor();
    this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::AusgabeAuswahlSpieler(int& option, int x, int y, Farbe f, int& AnzahlSpieler,int& AnzahlCpuGegner,std::vector<std::string>& SpielerNamen) {
    this->SetFarbe(f);
    this->SetConsoleFontSize(20);
	std::string tempNamen = "";
    std::string Ueberschrift = "Gebe die Anzahl an Spieler ein (zwischen 2 und 4)";

    int BreiteMenue = Ueberschrift.size() + 20;
    int linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
    int tempy = 0;
	int TempAnzahlSpieler = 0;
    do
    {
        Ueberschrift = "Gebe die Anzahl an Spieler ein (zwischen 2 und 4)";
        linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
        tempy = 0;
        TempAnzahlSpieler = 0;
        do
        {
            this->coord.X = x;
            this->coord.Y = y;
	        //Ausgabe der Auswahl Spieler
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << _symbolcharsControl[ULC];
            for (size_t i = 1; i < BreiteMenue - 1; i++)
            {
                std::cout << _symbolcharsControl[HL];
            }
            std::cout << _symbolcharsControl[URC];

            this->coord.Y++;
            SetConsoleCursorPosition(this->hConsole, this->coord);

            std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
            this->coord.Y++;
            SetConsoleCursorPosition(this->hConsole, this->coord);

            std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - 11) << " " << std::left << "Bestaetige mit Enter" << std::setw(BreiteMenue / 2 - 11 + 2) << std::right << _symbolcharsControl[VL];
            this->coord.Y++;
            SetConsoleCursorPosition(this->hConsole, this->coord);

            std::cout << _symbolcharsControl[LT];
            for (size_t i = 1; i < BreiteMenue - 1; i++)
            {
                std::cout << _symbolcharsControl[HL];
            }
            std::cout << _symbolcharsControl[RT];

            this->coord.Y++;
            tempy = this->coord.Y;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            std::cout << _symbolcharsControl[VL];
            for (size_t i = 1; i < BreiteMenue - 1; i++)
            {
                std::cout << _symbolcharsControl[SP];
            }
            std::cout << _symbolcharsControl[VL];

            this->coord.Y++;
            SetConsoleCursorPosition(this->hConsole, this->coord);

            std::cout << _symbolcharsControl[LLC];
            for (size_t i = 1; i < BreiteMenue - 1; i++)
            {
                std::cout << _symbolcharsControl[HL];
            }
            std::cout << _symbolcharsControl[LRC];
            this->coord.X++;
            this->coord.Y = tempy;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            this->ShowCursor();
            std::cin >> AnzahlSpieler;
            if (!std::cin)
	        {
		        std::cin.clear(); 
                std::cin.ignore();
            }
            if (2 > AnzahlSpieler || AnzahlSpieler > 4)
            {
                this->coord.Y +=2;
                SetConsoleCursorPosition(this->hConsole, this->coord);
		        std::cout << std::setw(BreiteMenue - 2) << std::left << "Bitte geben Sie eine Zahl zwischen 2 und 4 ein!"  ; 
            }
        } while (2 > AnzahlSpieler || AnzahlSpieler > 4);
	    //Ausgabe der Anzahl der CPU Gegner
		TempAnzahlSpieler += AnzahlSpieler;
        if (TempAnzahlSpieler < 4){
            Ueberschrift = "Gebe die Anzahl an CPU-Gegner ein (zwischen 0 und 2)";
            linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;
            do
            {
                this->coord.Y = y+8;
                this->coord.X = x;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                std::cout << _symbolcharsControl[ULC];
                for (size_t i = 1; i < BreiteMenue - 1; i++)
                {
                    std::cout << _symbolcharsControl[HL];
                }
                std::cout << _symbolcharsControl[URC];

                this->coord.Y++;
                SetConsoleCursorPosition(this->hConsole, this->coord);

                std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText+2) << std::right << _symbolcharsControl[VL];
                this->coord.Y++;
                SetConsoleCursorPosition(this->hConsole, this->coord);

                std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - 11) << " " << std::left << "Bestaetige mit Enter" << std::setw(BreiteMenue / 2 - 11 + 2) << std::right << _symbolcharsControl[VL];
                this->coord.Y++;
                SetConsoleCursorPosition(this->hConsole, this->coord);

                std::cout << _symbolcharsControl[LT];
                for (size_t i = 1; i < BreiteMenue - 1; i++)
                {
                    std::cout << _symbolcharsControl[HL];
                }
                std::cout << _symbolcharsControl[RT];

                this->coord.Y++;
                tempy = this->coord.Y;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                std::cout << _symbolcharsControl[VL];
                for (size_t i = 1; i < BreiteMenue - 1; i++)
                {
                    std::cout << _symbolcharsControl[SP];
                }
                std::cout << _symbolcharsControl[VL];

                this->coord.Y++;
                SetConsoleCursorPosition(this->hConsole, this->coord);

                std::cout << _symbolcharsControl[LLC];
                for (size_t i = 1; i < BreiteMenue - 1; i++)
                {
                    std::cout << _symbolcharsControl[HL];
                }
                std::cout << _symbolcharsControl[LRC];
                this->coord.X++;
                this->coord.Y = tempy;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                this->ShowCursor();
                std::cin >> AnzahlCpuGegner;
                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore();
                    AnzahlCpuGegner = -1;
                }
                if (0 > AnzahlCpuGegner || AnzahlCpuGegner > 3)
                {
                    this->coord.Y += 2;
                    SetConsoleCursorPosition(this->hConsole, this->coord);
                    std::cout << std::setw(BreiteMenue - 2) << std::left << "Bitte geben Sie eine Zahl zwischen 0 und 2 ein!";
                }
            } while ( AnzahlCpuGegner < 0 || AnzahlCpuGegner > 2);
			TempAnzahlSpieler += AnzahlCpuGegner;
            if (TempAnzahlSpieler > 4 || TempAnzahlSpieler < 2)
            {
                this->coord.Y += 2;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                std::cout << std::setw(BreiteMenue - 2) << std::left << "Die Summe der Spieler und CPU Gegner muss zwischen 2 und 4 liegen!";
            }
        }
    } while (2>TempAnzahlSpieler|| TempAnzahlSpieler >4);
    
	system("cls");

    for (size_t i = 0; i < AnzahlSpieler; i++)
    {
        Ueberschrift = "Spieler "+std::to_string(i+1)+" gebe deinen Namen ein";
        linkerRandText = (BreiteMenue - 2) / 2 - Ueberschrift.size() / 2;

		this->SetFarbe(static_cast<Farbe>(static_cast<int>(Farbe::Rot) + i));
        this->coord.X = x;
        this->coord.Y = y;
        //Ausgabe der Auswahl Spieler
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << _symbolcharsControl[ULC];
        for (size_t i = 1; i < BreiteMenue - 1; i++)
        {
            std::cout << _symbolcharsControl[HL];
        }
        std::cout << _symbolcharsControl[URC];

        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Ueberschrift << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout << _symbolcharsControl[VL] << std::setw(BreiteMenue / 2 - 11) << " " << std::left << "Bestaetige mit Enter" << std::setw(BreiteMenue / 2 - 11 + 2) << std::right << _symbolcharsControl[VL];
        this->coord.Y++;

        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout << _symbolcharsControl[LT];
        for (size_t i = 1; i < BreiteMenue - 1; i++)
        {
            std::cout << _symbolcharsControl[HL];
        }
        std::cout << _symbolcharsControl[RT];

        this->coord.Y++;
        tempy = this->coord.Y;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        std::cout << _symbolcharsControl[VL];
        for (size_t i = 1; i < BreiteMenue - 1; i++)
        {
            std::cout << _symbolcharsControl[SP];
        }
        std::cout << _symbolcharsControl[VL];

        this->coord.Y++;
        SetConsoleCursorPosition(this->hConsole, this->coord);

        std::cout << _symbolcharsControl[LLC];
        for (size_t i = 1; i < BreiteMenue - 1; i++)
        {
            std::cout << _symbolcharsControl[HL];
        }
        std::cout << _symbolcharsControl[LRC];
        this->coord.X++;
        this->coord.Y = tempy;
        SetConsoleCursorPosition(this->hConsole, this->coord);
        this->ShowCursor();
        std::cin >> tempNamen;
		SpielerNamen.push_back(tempNamen);
        system("cls");
    }
    for (size_t i = 0; i < AnzahlCpuGegner; i++)
    {
        SpielerNamen.push_back("CPU-Gegner" + std::to_string(i+1));
    }
    this->SetFarbe(Farbe::Zuruecksetzen);
    this->HideCursor();
    this->SetConsoleFontSize(8);

}
void TControl::AusgabeTestFeld(int x, int y) {
    //Außen MAP :   Hoehe = 8*11 , Breite = 20*11 

	int MapHoeheA = 88; // 8*11
	int MapBreiteA = 220; // 20*11
	int MapHoeheI = 74; // 8*9 +2 Korrektur
	int MapBreiteI = 182; // 20*9 +2 Korrektur

    for (size_t i = 0; i < MapHoeheA; i++)
    {
		this->coord.Y = y + i;
        for (size_t j = 0; j < MapBreiteA; j++)
        {
			this->coord.X = x + j;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            if (i == 0 || i == MapHoeheA-1)
            {
                std::cout << "#";
            }
            else if (j == 0 || j == MapBreiteA-1)
            {
                std::cout << "#";
            }

        }
        std::cout << std::endl;
    }

    //Innen MAP :   Hoehe = 8*9  , Breite = 20*9
    for (size_t i = 0; i < MapHoeheI; i++)
    {
        this->coord.Y = y + 7 + i;
        for (size_t j = 0; j < MapBreiteI; j++)
        {
            this->coord.X = x + 19 + j;
            SetConsoleCursorPosition(this->hConsole, this->coord);
            if (i == 0 || i == MapHoeheI-1)
            {
                std::cout << "#";
            }
            else if (j == 0 || j == MapBreiteI-1)
            {
                std::cout << "#";
            }

        }
        std::cout << std::endl;
    }

}
void TControl::HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(this->hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(this->hConsole, &cursorInfo);
}
void TControl::ShowCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(this->hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(this->hConsole, &cursorInfo);
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
            case Farbe::Rot:       return "\033[91m";
            case Farbe::Gruen:     return "\033[92m";
            case Farbe::Gelb:      return "\033[93m";
            case Farbe::Blau:      return "\033[94m";
            case Farbe::Magenta:   return "\033[95m";
            case Farbe::Cyan:      return "\033[96m";
            case Farbe::Weiss:     return "\033[97m";
            case Farbe::BG_Schwarz:   return "\033[40m";   // Schwarzer Hintergrund
            case Farbe::BG_Rot:       return "\033[101m";   // Roter Hintergrund
            case Farbe::BG_Gruen:     return "\033[102m";   // Grüner Hintergrund
            case Farbe::BG_Gelb:      return "\033[103m";   // Gelber Hintergrund
            case Farbe::BG_Blau:      return "\033[104m";   // Blauer Hintergrund
            case Farbe::BG_Magenta:   return "\033[105m";   // Magenta Hintergrund
            case Farbe::BG_Cyan:      return "\033[106m";   // Cyan Hintergrund
            case Farbe::BG_Weiss:     return "\033[107m";   // Weißer Hintergrund
            case Farbe::Zuruecksetzen: return "\033[0m"; // Zurücksetzen auf Standardfarbe
            default:               return "\033[0m";     // Standardfarbe
        }
    }
void TControl::SetFarbe(Farbe farbe) {
    switch (farbe) {
    case Farbe::Schwarz:   std::cout << "\033[30m"; break;
    case Farbe::Rot:       std::cout << "\033[91m"; break;
    case Farbe::Gruen:     std::cout << "\033[92m"; break;
    case Farbe::Gelb:      std::cout << "\033[93m"; break;
    case Farbe::Blau:      std::cout << "\033[94m"; break;
    case Farbe::Magenta:   std::cout << "\033[95m"; break;
    case Farbe::Cyan:      std::cout << "\033[96m"; break;
    case Farbe::Weiss:     std::cout << "\033[97m"; break;
    case Farbe::BG_Schwarz: std::cout << "\033[40m"; break; // Schwarzer Hintergrund
    case Farbe::BG_Rot:    std::cout << "\033[101m"; break; // Roter Hintergrund
    case Farbe::BG_Gruen:  std::cout << "\033[102m"; break; // Grüner Hintergrund
    case Farbe::BG_Gelb:   std::cout << "\033[103m"; break; // Gelber Hintergrund
    case Farbe::BG_Blau:   std::cout << "\033[104m"; break; // Blauer Hintergrund
    case Farbe::BG_Magenta: std::cout << "\033[105m"; break; // Magenta Hintergrund
    case Farbe::BG_Cyan:   std::cout << "\033[106m"; break; // Cyan Hintergrund
    case Farbe::BG_Weiss:  std::cout << "\033[107m"; break; // Weißer Hintergrund
    case Farbe::Zuruecksetzen: std::cout << "\033[0m"; break; // Zurücksetzen auf Standardfarbe
    default:               std::cout << "\033[0m"; break; // Standardfarbe
    }
}
void TControl::AusgabeWuerfel(int wuerfel, int x, int y, Farbe f) {
    this->SetFarbe(Farbe::BG_Schwarz);
    this->SetFarbe(Farbe::Weiss);
    static bool AusgabeWurf = false;

    int WuerfelFlaeche[6][5][9] = {
        {
            {ULC,HL,HL,HL,HL,HL,HL,HL,URC},
            {VL,SP,SP,SP,SP,SP,SP,SP,VL},
            {VL,SP,SP,SP,CR,SP,SP,SP,VL},
            {VL,SP,SP,SP,SP,SP,SP,SP,VL},
            {LLC,HL,HL,HL,HL,HL,HL,HL,LRC}
        },
        {
            {ULC,HL,HL,HL,HL,HL,HL,HL,URC},
            {VL,SP,CR,SP,SP,SP,SP,SP,VL},
            {VL,SP,SP,SP,SP,SP,SP,SP,VL},
            {VL,SP,SP,SP,SP,SP,CR,SP,VL},
            {LLC,HL,HL,HL,HL,HL,HL,HL,LRC}
        },
        {
            {ULC,HL,HL,HL,HL,HL,HL,HL,URC},
            {VL,SP,CR,SP,SP,SP,SP,SP,VL},
            {VL,SP,SP,SP,CR,SP,SP,SP,VL},
            {VL,SP,SP,SP,SP,SP,CR,SP,VL},
            {LLC,HL,HL,HL,HL,HL,HL,HL,LRC}
        },
        {
            {ULC,HL,HL,HL,HL,HL,HL,HL,URC},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {VL,SP,SP,SP,SP,SP,SP,SP,VL},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {LLC,HL,HL,HL,HL,HL,HL,HL,LRC}
        },
        {
            {ULC,HL,HL,HL,HL,HL,HL,HL,URC},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {VL,SP,SP,SP,CR,SP,SP,SP,VL},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {LLC,HL,HL,HL,HL,HL,HL,HL,LRC}
        },
        {
            {ULC,HL,HL,HL,HL,HL,HL,HL,URC},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {VL,SP,CR,SP,SP,SP,CR,SP,VL},
            {LLC,HL,HL,HL,HL,HL,HL,HL,LRC}
        },
    };
    this->coord.X = x;
    this->coord.Y = y;
	int counter = 0;
    int RandZeitSimulation1 = 5; // Zeit in Sekunden, nach der der Text wechselt
    int RandZeitSimulation2 = RandZeitSimulation1+3; // Zeit in Sekunden, nach der der Text wechselt
	std::mt19937 rng(time(nullptr)); // Zufallszahlengenerator initialisieren
    std::uniform_int_distribution<int> dist(0,5);
	int rand = dist(rng); 
    while (true)
    {
		rand = dist(rng); 
        if (counter >= 6)
        {
            this->SetFarbe(f);
            this->SetFarbe(Farbe::Schwarz);
            for (int i = 0; i < 5; i++) {
                this->coord.Y = y + i;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                for (size_t j = 0; j < 9; j++)
                {
                    std::cout << _symbolcharsControl[WuerfelFlaeche[wuerfel - 1][i][j]];
                }
            }
            break;
        }
        else
        {
            for (int i = 0; i < 5; i++) {
                this->coord.Y = y + i;
                SetConsoleCursorPosition(this->hConsole, this->coord);
                for (size_t j = 0; j < 9; j++)
                {
                    std::cout << _symbolcharsControl[WuerfelFlaeche[rand][i][j]];
                }
            }
			Sleep(200); // Kurze Pause für die Animation
        }
        counter++;
    }
	counter = 0;
	this->SetFarbe(Farbe::Zuruecksetzen);
}
void TControl::GetMaximizedConsoleSize(int& width, int& height) {
    HWND consoleWindow = GetConsoleWindow();
    if (!consoleWindow) {
        std::cerr << "Error: Could not get console window handle\n";
        return;
    }

    // Maximize the console window
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    // Small delay to allow window to maximize
    Sleep(100);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Could not get console handle\n";
        return;
    }
    COORD largest = GetLargestConsoleWindowSize(this->hConsole);
    if (largest.X > 0 && largest.Y > 0) {
        width = largest.X;
        height = largest.Y;
        std::cout << "Console size (GetLargestConsoleWindowSize): " << width << "x" << height << std::endl;
        return; 
    }
}
int TControl::GetLaengstenStringMenueStartOptionen(void){
    int tempMax = 0;
    for (std::string option : this->MenueStartOptionen) {
        if (option.size() > tempMax) {
            tempMax = option.size();
        }
    }
	return tempMax;
}
int TControl::GetLaengstenStringMenueSpielOptionen(void) {
    int tempMax = 0;
    for (std::string option : this->MenueSpielOptionen) {
        if (option.size() > tempMax) {
            tempMax = option.size();
        }
    }
    return tempMax;
}
int TControl::GetLaengstenStringMenueSpielerOptionen(void) {
    int tempMax = 0;
    for (std::string option : this->MenueSpielerOptionen) {
        if (option.size() > tempMax) {
            tempMax = option.size();
        }
    }
    return tempMax;
}
int TControl::GetAnzMenuepunkteStartOptionen(void) {
    return MenueStartOptionen.size() - 2;
}
int TControl::GetAnzMenuepunkteSpielOptionen(void){
    return MenueSpielOptionen.size() - 2;
}
int TControl::GetAnzMenuepunkteSpielerOptionen(void) {
	return MenueSpielerOptionen.size() - 2;  
}
void TControl::UpdateCursorPosition(COORD Pos) {
    SetConsoleCursorPosition(this->hConsole, Pos);
}
void TControl::SetConsoleFontSize(int fontSize) {
    CONSOLE_FONT_INFOEX cfi;

    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(this->hConsole, FALSE, &cfi);

    cfi.dwFontSize.Y = fontSize;  
    cfi.dwFontSize.X = fontSize;  
    SetCurrentConsoleFontEx(this->hConsole, FALSE, &cfi);
}
bool TControl::isRunningInWindowsTerminal() {
    char className[256];

    HWND hwnd = GetConsoleWindow();
    GetClassNameA(hwnd, className, sizeof(className));
    if (strcmp(className, "PseudoConsoleWindow") == 0) {
        // Windows-Terminal
        std::cout << "Folgendes Einstellungen umstellen:" << std::endl;
        std::cout << "1) Windows-Taste->Terminaleinstellungen oeffnen." << std::endl;
        std::cout << "2) im Reiter Terminal \"Windows-Terminal\" auf \"Windows-Konsolenhost\" umstellen!" << std::endl;
        std::cout << "3) Programm starten und zum Zoomen STRG + Mausrad benutzen!" << std::endl;
        std::cout << "Danach ueberpruefen ob der Buffer der Konsole groß genug ist:" << std::endl;
        std::cout << "1) Windows-Taste->Konsole/Eingabeaufforderung oeffnen." << std::endl;
        std::cout << "2) Rechtsklick auf die Titelleiste->Eigenschaften->Layout folgendes einstellen Breite: 500, Hoehe: 100" << std::endl;
        std::cout << "3) Programm starten und zum Zoomen STRG + Mausrad benutzen!" << std::endl;
        return true;
    }
    else if (strcmp(className, "ConsoleWindowClass") == 0) {
        // Windows-Konsolenhost
    }
    return false;
}
void TControl::AusgabeNachricht(std::string Nachricht,int x,int y,Farbe f) {
    this->SetFarbe(Farbe::Schwarz);
    this->SetFarbe(f);
    int BreiteMenue = Nachricht.size() + 10;
    int linkerRandText = (BreiteMenue - 2) / 2 - Nachricht.size() / 2;

    this->coord.X = x;
    this->coord.Y = y;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[ULC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[URC];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[VL] << std::setw(linkerRandText) << " " << std::left << Nachricht << std::setw(linkerRandText + 1) << std::right << _symbolcharsControl[VL];
    this->coord.Y++;
    SetConsoleCursorPosition(this->hConsole, this->coord);
    std::cout << _symbolcharsControl[LLC];
    for (size_t i = 1; i < BreiteMenue - 1; i++)
    {
        std::cout << _symbolcharsControl[HL];
    }
    std::cout << _symbolcharsControl[LRC];

    this->SetFarbe(Farbe::Zuruecksetzen);


}
void TControl::UnitTest() {

    enum MenueOptionen {
        Reset = -1,
        Start = 0,
        Highscore,
        Optionen,
        Beenden,
        Wuerfeln,
        Kaufen,
        Bauen,
        Handeln,
        Fortfahren,
        SpielSpeichern,
        SpielLaden,
        SpielRegeln,
        Zurueck
    };

    enum class Menues {
        Start = 100,
        Spieler,
        Optionen,
        Handel
    };


    TControl TestControl;
    std::string playerNames[4] = { "a","bbbb","ccccc","ddddddddddddddddddddddddddddddddddddddddddddddddddd" };
    std::vector<std::vector<std::string>> GekObjNamen = { { "Strasse1"},
                                                          { "Strasse2","Gebaeude xyz2"},
                                                          { "Strasse3","Gebaeude xyz3","Autobahn nach Karlsruhe3"},
                                                          { "Strasse4","Gebaeude xyz4","Autobahn nach Karlsruhe4","4TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"}};
    std::vector<std::vector<std::string>> GebObjNamen = { { "Haus 1"},
                                                          { "Haus 2","Gebaeude zyx2"},
                                                          { "Haus 3","Gebaeude zyx3","Hotel 3"},
                                                          { "Haus 4","Gebaeude zyx4","Hotel 4","4TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"}};
	std::vector<std::string> Spielregeln = { "Regel 1", "Regel 2", "Regel 3", "Regel 4", "Regel 5555555555555555555555555555555555555555555555555555555555555" };
	int budget[4] = { 100,10000,100000,99999999 }; //Budget der Spieler
	int gekObjAnz[4] = { 5,15,2,3 };//Anzahl gekaufter Objekte der Spieler
	int gebObjAnz[4] = { 0,2,3,99 };//Anzahl gebaute Objekte der Spieler
	COORD CursorPos = { 0,0 };
    int option = 1;
    bool Spiellaueft = TRUE, RundeVorhanden=FALSE;
    char EingabeCh = MenueOptionen::Reset;
	bool UpdateSpielfeld = FALSE;
	int AnzahlSpieler = 4;
    int x=0,y=0;
    int AuswahlStraße = -1,Angebot=-1;
    TestControl.GetMaximizedConsoleSize(x, y);
	//Ausgabe des Startbildschirms
    do
    {
		TestControl.AusgabeJaNeinOption(option, 10, 10, Farbe::Weiss, "Akzeptierst du das Angebot?");
        DWORD StartZeit = GetTickCount64();
        TestControl.AusgabeStartBildschirm(TRUE, x/2-43 , y/2-11);
        DWORD ZeitDifferenz = GetTickCount64() - StartZeit;
        if (ZeitDifferenz < FRAME_DURATION) {
            Sleep(FRAME_DURATION - ZeitDifferenz);
        }
    } while (!_kbhit());
	std::cin.clear();
    system("cls");
    Menues MenueAuswahl = Menues::Start;
    Menues MenueLetztes = MenueAuswahl;
    while (Spiellaueft)  
    {
        DWORD start_time = GetTickCount64();


        EingabeCh = MenueOptionen::Reset;
        if (_kbhit()) {
            EingabeCh = _getch();
        }
        UpdateSpielfeld = FALSE;

		//Verarbeitung der Eingaben
        switch (EingabeCh) {
        case KEY_UP :
		case KEY_W:
            if (option > 0) {
                option--;
            }
            break;
        case KEY_DOWN:
		case KEY_S:
            if (option < TestControl.GetAnzMenuepunkteStartOptionen() - 1 && MenueAuswahl==Menues::Start) {
                option++;
            }
            else if (option < TestControl.GetAnzMenuepunkteSpielOptionen() - 1 && MenueAuswahl == Menues::Optionen) {
                option++;
            }
            else if (option < TestControl.GetAnzMenuepunkteSpielerOptionen() - 1 && MenueAuswahl == Menues::Spieler) {
                option++;
            }
            break;
        case KEY_ESCAPE:
            system("cls");
            if (MenueAuswahl != Menues::Optionen)
            {
                MenueLetztes = MenueAuswahl;
            }
            MenueAuswahl = Menues::Optionen;

            break;
        case KEY_ENTER:
        case KEY_SPACE:
            switch (MenueAuswahl)
            {
            case Menues::Start:
                system("cls");
                if (option == MenueOptionen::Start) { 
					MenueAuswahl = Menues::Spieler;
                    RundeVorhanden = TRUE;
                    UpdateSpielfeld = TRUE;
                }
                if (option == MenueOptionen::Highscore) { TestControl.AusgabeHighscore(playerNames, budget, 4, x / 2 - playerNames[3].size()/2-8, y / 2 + TestControl.GetAnzMenuepunkteStartOptionen() + 2); }
                if (option == MenueOptionen::Optionen) { system("cls"); MenueLetztes = MenueAuswahl; MenueAuswahl = Menues::Optionen; }
                if (option == MenueOptionen::Beenden) { Spiellaueft = FALSE; }
                break;
            case Menues::Spieler:
                CursorPos = { short(x / 2 - 160), short(y / 2 - 36) };
                TestControl.UpdateCursorPosition(CursorPos);
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Wuerfeln)
                {
                    
					std::cout<< std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) <<std::left<< "Spieler X: wirft den Wuerfel!";

					TestControl.AusgabeWuerfel(3, x / 2 - 160, y / 2 - 30, Farbe::BG_Gruen); //die Farbe dem zugehörigen Spieler anpassen
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Kaufen)
                {
					//Code zum Kaufen von Objekten
					std::cout << std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Kaufen von Objekten ist noch nicht implementiert!" << std::endl;
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Bauen)
                {
                    std::cout << std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Bauen von Objekten ist noch nicht implementiert!" << std::endl;
                    //Code zum Bauen von Objekten
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Handeln)
                {
                    std::cout << std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Handeln von Objekten ist noch nicht implementiert!" << std::endl;
                    //Code zum Handeln von Objekten
                }

                TestControl.AusgabeTestFeld(x / 2 - 110, y / 2 - 44);
                TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObjAnz, gebObjAnz, AnzahlSpieler, x / 2 - 90, y / 2 - 36, GekObjNamen, GebObjNamen,{0,1,2,3});
                break;
            case Menues::Optionen:
                system("cls");

                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Fortfahren) {
                    if (RundeVorhanden) {
                        UpdateSpielfeld = TRUE;
						MenueAuswahl = Menues::Spieler;
                    }
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielSpeichern) {
                    
                    if (RundeVorhanden) {
                        CursorPos = { short(x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 1) };
                        TestControl.UpdateCursorPosition(CursorPos);
                        std::cout <<std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird gespeichert!";
                    }
                    else
                    {
                        std::cout << std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Es gibt keine Runde zum speichern!";
                    }
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielLaden) {
                    CursorPos = { short(x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 1) };
                    TestControl.UpdateCursorPosition(CursorPos);
                    std::cout << std::setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird geladen!";
					RundeVorhanden = TRUE; //Wenn das Spiel korrekt geladen wird
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielRegeln) { TestControl.AusgabeSpielRegeln(Spielregeln, x / 2 - playerNames[3].size() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 2);}
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Beenden + 9) { Spiellaueft = FALSE; }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Highscore + 12) { TestControl.AusgabeHighscore(playerNames, budget, 4, x / 2 - playerNames[3].size() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen()+2); }
                
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Zurueck + 2) { 
                    MenueAuswahl = MenueLetztes;
                    if (MenueAuswahl==Menues::Start)
                    {

                    }
                    else if (MenueAuswahl==Menues::Spieler)
                    {
                        UpdateSpielfeld = TRUE;
                    }

                }
                break;
            default:
                break;
            }

            option = Reset+1;
            break;
        default:
            break;
        }

        //Ausgabe des ausgewählten Menüs
        switch (MenueAuswahl)
        {
        case Menues::Start:
            TestControl.AusgabeStartMenu(option, x / 2 - TestControl.GetLaengstenStringMenueStartOptionen() / 2, y / 2 - TestControl.GetAnzMenuepunkteStartOptionen() / 2);
            break;
        case Menues::Spieler:
            TestControl.AusgabeSpielerOptionen(option, x / 2 - 160, y / 2 - 44, Farbe::BG_Gruen); //die Farbe dem zugehörigen Spieler anpassen
            break;
        case Menues::Optionen:
            TestControl.AusgabeSpielOptionen(option, x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() /2, y / 2 - TestControl.GetAnzMenuepunkteSpielOptionen() / 2);
            break;
		case Menues::Handel:
			//TestControl.AusgabeHandelsMenu(option, x / 2 - TestControl.GetLaengstenStringMenueSpielerOptionen() / 2, y / 2 - TestControl.GetAnzMenuepunkteSpielerOptionen() / 2, Farbe::BG_Gelb); //die Farbe dem zugehörigen Spieler anpassen
        default:
            break;
        }
        
        if (UpdateSpielfeld)
        {
            TestControl.AusgabeTestFeld(x / 2 - 110, y / 2 - 44);
            TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObjAnz, gebObjAnz, AnzahlSpieler, x / 2 - 90, y / 2 - 36, GekObjNamen, GebObjNamen,{0,1,2,3});
        }


        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
    }
}