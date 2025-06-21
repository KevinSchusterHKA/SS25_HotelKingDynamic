#include "TServerEngine.h"
TServer::TServer(){

}

TServer::~TServer(){
}

void TServer::UnitTest() {

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
        RundeBeenden,
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
        Handel,
        BahnFahren
    };

    std::vector<std::string> Spielregeln = { "Regel 1", "Regel 2", "Regel 3", "Regel 4", "Regel 5555555555555555555555555555555555555555555555555555555555555" };

    COORD CursorPos = { 0,0 };
	std::vector<std::string> SpielerNamen;
    int option = 0, AnzahlSpieler = 4, AnzahlCpuGegner=2, MomentanerSpieler = 0, Rundenzaehler = 1, x = 0, y = 0;
    bool Spiellaueft = TRUE, RundeVorhanden = FALSE, HatGewuerfelt=FALSE, GameFinished=FALSE, UpdateSpielfeld = FALSE;
    char EingabeCh = MenueOptionen::Reset;
    MapReturnObj MRobj[4];
	Farbe MomentanerSpielerFarbe = Farbe::BG_Rot; // Standardfarbe für den ersten Spieler
    ControlEngine.SetConsoleFontSize(8);
  
    ControlEngine.GetMaximizedConsoleSize(x, y);
    if (ControlEngine.isRunningInWindowsTerminal())
    {
		Spiellaueft = FALSE; 
        return;
    }

    ControlEngine.SetConsoleFontSize(22);
    ControlEngine.UpdateCursorPosition({short(10),short(20) });
    std::cout << "Folgendes Einstellungen umstellen:" << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(21) });
    std::cout << "1) Windows-Taste->Terminaleinstellungen oeffnen." << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(22) });
    std::cout << "2) im Reiter Terminal \"Windows-Terminal\" auf \"Windows-Konsolenhost\" umstellen!" << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(23) });
    std::cout << "3) Programm starten und zum Zoomen STRG + Mausrad benutzen!" << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(25) });
    std::cout << "Danach ueberpruefen ob der Buffer der Konsole gross genug ist:" << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(26) });
    std::cout << "1) Windows-Taste->Konsole/Eingabeaufforderung oeffnen." << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(27) });
    std::cout << "2) Rechtsklick auf die Titelleiste->Eigenschaften->Layout folgendes einstellen Breite: 500, Hoehe: 100" << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(28) });
    std::cout << "3) Programm starten und zum Zoomen STRG + Mausrad benutzen!" << std::endl;
    ControlEngine.UpdateCursorPosition({ short(10),short(31) });
    std::cout << "Irgendeine Taste druecken um fortzufahren!" << std::endl;
    option = _getch();
    
	system("cls");
    ControlEngine.SetConsoleFontSize(8);
	Sleep(100); 

    //Ausgabe des Startbildschirms
    if (Spiellaueft)
    {
        do
        {
             DWORD StartZeit = GetTickCount64();
            ControlEngine.AusgabeStartBildschirm(TRUE, x / 2 - 43, y / 2 - 11);
             DWORD ZeitDifferenz = GetTickCount64() - StartZeit;
            if (ZeitDifferenz < FRAME_DURATION) {
                Sleep(FRAME_DURATION - ZeitDifferenz);
            } 
            if (_kbhit()) 
            {
                option = _getch(); 
                if (option!=KEY_ENTER && option != KEY_SPACE)
                {
                    break;
                }
            }
        } while (TRUE);
        std::cin.clear();
        system("chcp 850");
        system("cls");
    }
    Menues MenueAuswahl = Menues::Start;
    Menues MenueLetztes = MenueAuswahl;
    option = 0;
    while (Spiellaueft)
    {
        DWORD start_time = GetTickCount64();
        
        if (player[MomentanerSpieler].imGefaengnis())
        {
            ConfigEngineLogging.playerMoney(player[MomentanerSpieler].getName(), player[MomentanerSpieler].getBudget());
            ConfigEngineLogging.playerInPrison();
            player[MomentanerSpieler].decGefaengnisRunden();
            MomentanerSpieler++;
            ConfigEngineLogging.newRound();
            ConfigEngineLogging.newPlayer(player[MomentanerSpieler].getName());
            HatGewuerfelt = false;
        }
        if (MomentanerSpieler >= AnzahlSpieler) {
            MomentanerSpieler = 0;
        }

        switch (MomentanerSpieler)
        {
        case 0:
            MomentanerSpielerFarbe = Farbe::BG_Rot;
            break;
        case 1:
            MomentanerSpielerFarbe = Farbe::BG_Gruen;
            break;
        case 2:
            MomentanerSpielerFarbe = Farbe::BG_Gelb;
            break;
        case 3:
            MomentanerSpielerFarbe = Farbe::BG_Cyan;
            break;
        default:
            break;
        }

        EingabeCh = MenueOptionen::Reset;
        if (_kbhit()) {
            EingabeCh = _getch();
        }
        UpdateSpielfeld = FALSE;

        //Verarbeitung der Eingaben
        switch (EingabeCh) {
        case KEY_UP:
        case KEY_W:
            if (option > 0) {
                option--;
            }
            break;
        case KEY_DOWN:
        case KEY_S:
            if (option < ControlEngine.GetAnzMenuepunkteStartOptionen() - 1 && MenueAuswahl == Menues::Start) {
                option++;
            }
            else if (option < ControlEngine.GetAnzMenuepunkteSpielOptionen() - 1 && MenueAuswahl == Menues::Optionen) {
                option++;
            }
            else if (option < ControlEngine.GetAnzMenuepunkteSpielerOptionen() - 1 && MenueAuswahl == Menues::Spieler) {
                option++;
            }
            else if (option < 1 && MenueAuswahl == Menues::Handel) {
                option++;
            }
            else if (option < 1 && MenueAuswahl == Menues::BahnFahren) {
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

                    ConfigEngineLogging.newGame();
                    ControlEngine.AusgabeAuswahlSpieler(option, x/7, y / 7, Farbe::Gelb, AnzahlSpieler,AnzahlCpuGegner, SpielerNamen);
                    for (size_t i = 0; i < 4; i++)
                    {
                        player[i].setName(SpielerNamen[i]);
                    }
                    MapEngine.SetPlayerNumber(AnzahlSpieler);
                }
				if (option == MenueOptionen::Highscore) { //HIGHSCORE ANZEIGEN
					std::vector<HighscoreEntry> player;
					load_highscores("highscores.txt", player);
                    std::vector<std::string> playerNames;
                    std::vector<int> playerScore;
                    for (size_t i = 0; i < player.size(); i++)
                    {
                        playerNames.push_back(player[i].playerName);
                        playerScore.push_back(player[i].score);
                    }

                    ControlEngine.AusgabeHighscore(playerNames.data(), playerScore.data(), player.size(), x / 2 - this->GetLongestStringVector(playerNames) / 2 - 6, y / 2 + ControlEngine.GetAnzMenuepunkteStartOptionen() + 2);
                }
                if (option == MenueOptionen::Optionen) { system("cls"); MenueLetztes = MenueAuswahl; MenueAuswahl = Menues::Optionen; }
                if (option == MenueOptionen::Beenden) { Spiellaueft = FALSE; }
                break;
            case Menues::Spieler:
                CursorPos = { short(x / 2 - 160), short(y / 2 - 40 + ControlEngine.GetAnzMenuepunkteSpielerOptionen()) };
                ControlEngine.UpdateCursorPosition(CursorPos);
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Wuerfeln )
                {
                    if (!HatGewuerfelt)
                    {
                        std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler "+to_string(MomentanerSpieler+1)+" : wirft den Wuerfel!";

                        player[MomentanerSpieler].Wurfelmechn();
                        int wuerfel1 = player[MomentanerSpieler].getWurfel(0);
                        int wuerfel2 = player[MomentanerSpieler].getWurfel(1);
                        HatGewuerfelt = true;

                        ControlEngine.AusgabeWuerfel(wuerfel1, x / 2 - 160, y / 2 - 30, MomentanerSpielerFarbe);  
                        ControlEngine.AusgabeWuerfel(wuerfel2, x / 2 - 150, y / 2 - 30, MomentanerSpielerFarbe);  
                        ConfigEngineLogging.playerRollingDice(wuerfel1, wuerfel2);

                        if (player[MomentanerSpieler].paschcheck()) {
                            HatGewuerfelt = FALSE;
                            player[MomentanerSpieler].incPaschCounter();
                        }
                        else {
                            player[MomentanerSpieler].setPaschCounter(0);
                        }
                        if (player[MomentanerSpieler].getPaschCounter() == 3) {
                            MapEngine.setPlayer(MomentanerSpieler, 10, -1);//TODO:mit Map absprechen wegen dem Gefaegnis
                            player[MomentanerSpieler].setPaschCounter(0);
                            break;
                        }
                        if (MRobj[MomentanerSpieler].Type == 1)
                        {
                            MenueAuswahl = Menues::BahnFahren;
                        }
                        else {
                            player[MomentanerSpieler].bezahle(MapEngine.movePlayer(MomentanerSpieler, wuerfel1 + wuerfel2, 0));

                            MRobj[MomentanerSpieler] = MapEngine.getSpaceProps(MomentanerSpieler);
                            if ((MRobj[MomentanerSpieler].Rent != -1) && (MRobj[MomentanerSpieler].Type != 1) && (MRobj[MomentanerSpieler].Type != 7))
                            {
                                player[MomentanerSpieler].bezahle(MRobj[MomentanerSpieler].Rent);
                            }
                            if (MRobj[MomentanerSpieler].Type == 7)
                            {
                                player[MomentanerSpieler].erhalte(MRobj[MomentanerSpieler].Rent);
                            }
                            if (MRobj[MomentanerSpieler].Owner != -1)
                            {
                                player[MRobj[MomentanerSpieler].Owner].erhalte(MRobj[MomentanerSpieler].Rent);
                            }

                            ConfigEngineLogging.playerOnStreet("Spieler kommt auf Straße"); //TODO: Mit MapEngine absprechen wegen String
                            ConfigEngineLogging.onEventField("Event xyz wurde ausgelöst");  //TODO: Mit MapEngine absprechen wegen String
                            ConfigEngineLogging.playerInPrison();                           //TODO: Mit MapEngine absprechen wegen String
                        }
                    }
                    else {
                        std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler " + to_string(MomentanerSpieler + 1) + " hat schon gewuerfelt!";
                    }
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Kaufen )
                {
                    //player[MomentanerSpieler].bezahle(MapEngine.buyStreet(MomentanerSpieler, player[MomentanerSpieler].getBudget()));
                    //player[MomentanerSpieler].addStrasse(player[MomentanerSpieler].getPosition());
                    //ConfigEngineLogging.playerBuysObject("Straße wurde gekauft"); //TODO: Mit MapEngine absprechen wegen String

                    // Prüfen ob die Straße schon jemand besitzt
                    bool istFrei = true;

                    for (int i = 0; i < AnzahlSpieler; i++) {
                        if (player[i].besitztStrasse(player[MomentanerSpieler].getPosition())) {
                            istFrei = false;
                            break;
                        }
                    }

                    // Wenn Straße frei ist: kaufen
                    if (istFrei) {
                        player[MomentanerSpieler].bezahle(MapEngine.buyStreet(MomentanerSpieler, player[MomentanerSpieler].getBudget()));
                        player[MomentanerSpieler].addStrasse(player[MomentanerSpieler].getPosition());
                        ConfigEngineLogging.playerBuysObject("Straße wurde gekauft"); // TODO: String von MapEngine holen
                    }
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Bauen)
                {
                    int space = MRobj[MomentanerSpieler].SpaceNr;// Bug
                    player[MomentanerSpieler].bezahle(MapEngine.buyHouses(MomentanerSpieler, space, player[MomentanerSpieler].getBudget()));
                    //player[MomentanerSpieler].bezahle(MapEngine.buyHouses(MomentanerSpieler, player[MomentanerSpieler].getBudget()));
                    player[MomentanerSpieler].baueHaus(player[MomentanerSpieler].getPosition());
					          ConfigEngineLogging.playerBuildsBuilding("Haus wurde gebaut"); //TODO: Mit MapEngine absprechen wegen String
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Handeln) // Bug
                {
                    std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Handeln von Objekten ist noch nicht implementiert!" << std::endl;
					int Angebot = -1;
					int Strasse = -1;
                    ControlEngine.AusgabeStrasseHandeln(option, Strasse, Angebot, x / 2 -211, y / 2-20, Farbe::BG_Rot);
					MenueAuswahl = Menues::Handel;
                    //Code zum Handeln von Objekten
                    //player[MomentanerSpieler].handel(board.(MomentanerSpieler, player[MomentanerSpieler].getBudget()));
					//TODO: ConfigEngineLogging.playerTradesObject("Objekt wurde gehandelt");
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::RundeBeenden)
                {
                    if (HatGewuerfelt)
                    {
                        ConfigEngineLogging.playerMoney(player[MomentanerSpieler].getName(), player[MomentanerSpieler].getBudget());
                        MomentanerSpieler++;
                        HatGewuerfelt = false;
                        system("cls");
                        ConfigEngineLogging.newRound();
                        ConfigEngineLogging.newPlayer(player[MomentanerSpieler].getName());
                    }
                    else
                    {
						std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Spieler " + to_string(MomentanerSpieler + 1) + " hat noch nicht gewuerfelt!" << std::endl;
                    }
                }
                UpdateSpielfeld = TRUE;
                
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
                        CursorPos = { short(x / 2 - ControlEngine.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 1) };
                        ControlEngine.UpdateCursorPosition(CursorPos);
                        save_config("Config.txt",{});       //TODO: implementieren und auf Funktionalität testen
						save_game("Spielstand.txt", {});    //TODO: implementieren und auf Funktionalität testen
                        std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird gespeichert!";
                    }
                    else
                    {
                        std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Es gibt keine Runde zum speichern!";
                    }
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielLaden) {
                    CursorPos = { short(x / 2 - ControlEngine.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 1) };
                    ControlEngine.UpdateCursorPosition(CursorPos);
                    std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird geladen!";
                    //load_config("Config.txt", {}); //TODO: implementieren und auf Funktionalität testen
                    //load_game("Spielstand.txt", {});//TODO: implementieren und auf Funktionalität testen
                    RundeVorhanden = TRUE; //Wenn das Spiel korrekt geladen wird
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielRegeln) { 
                    ControlEngine.AusgabeSpielRegeln(Spielregeln, x / 2 - this->GetLongestStringVector(Spielregeln)/ 2 - 8, y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 2); 
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Beenden + 10) { Spiellaueft = FALSE; }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Highscore + 13) { 
                    std::vector<HighscoreEntry> player;
                    load_highscores("highscores.txt", player);
                    std::vector<std::string> playerNames;
                    std::vector<int> playerScore;
                    for (size_t i = 0; i < player.size(); i++)
                    {
                        playerNames.push_back(player[i].playerName);
                        playerScore.push_back(player[i].score);
                    }

                    ControlEngine.AusgabeHighscore(playerNames.data(), playerScore.data(), player.size(), x / 2 - this->GetLongestStringVector(playerNames) / 2 - 6, y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 2);
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Zurueck + 2) {
                    MenueAuswahl = MenueLetztes;
                    if (MenueAuswahl == Menues::Start)
                    {

                    }
                    else if (MenueAuswahl == Menues::Spieler)
                    {
                        UpdateSpielfeld = TRUE;
                    }

                }
                break;
            case Menues::Handel:
				
                MenueAuswahl = Menues::Spieler;
                UpdateSpielfeld = TRUE;
				system("cls");
                if (option == 0) //Akzeptieren
                {
					//Code zum Akzeptieren des Handels
                }
                else
                {
                    //Code zum Ablehnen des Handels
                }
            case Menues::BahnFahren:
                MenueAuswahl = Menues::Spieler;
                UpdateSpielfeld = TRUE;
                system("cls");

                if (!option)
                {
                    player[MomentanerSpieler].bezahle(MapEngine.movePlayer(MomentanerSpieler, player[MomentanerSpieler].getAugenzahl(), 1));
                    player[MomentanerSpieler].bezahle(MRobj[MomentanerSpieler].Rent);
                }
                else {
                    player[MomentanerSpieler].bezahle(MapEngine.movePlayer(MomentanerSpieler, player[MomentanerSpieler].getAugenzahl(), 0));
                }

                MRobj[MomentanerSpieler] = MapEngine.getSpaceProps(MomentanerSpieler);
                if ((MRobj[MomentanerSpieler].Rent != -1) && (MRobj[MomentanerSpieler].Type != 1) && (MRobj[MomentanerSpieler].Type != 7))
                {
                    player[MomentanerSpieler].bezahle(MRobj[MomentanerSpieler].Rent);
                }
                if (MRobj[MomentanerSpieler].Type == 7)
                {
                    player[MomentanerSpieler].erhalte(MRobj[MomentanerSpieler].Rent);
                }
                if (MRobj[MomentanerSpieler].Owner != -1)
                {
                    player[MRobj[MomentanerSpieler].Owner].erhalte(MRobj[MomentanerSpieler].Rent);
                }

                ConfigEngineLogging.playerOnStreet("Spieler kommt auf Straße"); //TODO: Mit MapEngine absprechen wegen String
                ConfigEngineLogging.onEventField("Event xyz wurde ausgelöst");  //TODO: Mit MapEngine absprechen wegen String
                ConfigEngineLogging.playerInPrison();                           //TODO: Mit MapEngine absprechen wegen String
                break;
            default:
                break;
            }

            option = Reset + 1;
            break;
        default:
            break;
        }


        //Ausgabe des ausgewaehlten Menüs

        switch (MenueAuswahl)
        {
        case Menues::Start:
            ControlEngine.AusgabeStartMenu(option, x / 2 - ControlEngine.GetLaengstenStringMenueStartOptionen() / 2, y / 2 - ControlEngine.GetAnzMenuepunkteStartOptionen() / 2);
            break;
        case Menues::Spieler:
            ControlEngine.AusgabeSpielerOptionen(option, x / 2 - 160, y / 2 - 44, MomentanerSpielerFarbe); //die Farbe dem zugehoerigen Spieler anpassen

            break;
        case Menues::Optionen:
            ControlEngine.AusgabeSpielOptionen(option, x / 2 - ControlEngine.GetLaengstenStringMenueSpielOptionen() / 2, y / 2 - ControlEngine.GetAnzMenuepunkteSpielOptionen() / 2);
            break;
        case Menues::Handel:
            ControlEngine.AusgabeJaNeinOption(option, x / 2 - 198, y / 2 - 9, Farbe::BG_Schwarz,"Akzeptierst du den Handel Spieler wem die Strasse gehoert?");

        case Menues::BahnFahren:
            ControlEngine.AusgabeJaNeinOption(option, x / 2 - 198, y / 2 - 9, MomentanerSpielerFarbe, "Bahn fahren?"); // Bug
            break;
        default:
            break;
        }

        if (UpdateSpielfeld)
        {
            //TestControl.AusgabeFeld(board.toStr(), x / 2 - 110, y / 2 - 44);
            while (MRobj[MomentanerSpieler].flag)
            {
                MRobj[MomentanerSpieler] = MapEngine.getSpaceProps(MomentanerSpieler);
                if ((MRobj[MomentanerSpieler].Rent != -1) && (MRobj[MomentanerSpieler].Type != 7))
                {
                    player[MomentanerSpieler].bezahle(MRobj[MomentanerSpieler].Rent);
                }
                if (MRobj[MomentanerSpieler].Owner != -1)
                {
                    player[MRobj[MomentanerSpieler].Owner].erhalte(MRobj[MomentanerSpieler].Rent);
                }
                //TestControl.AusgabeFeld(board.toStr(), x / 2 - 110, y / 2 - 44);
            }
            ControlEngine.AusgabeFeld(MapEngine.toStr(), x / 2 - 110, y / 2 - 44);
            std::vector<std::vector<std::string>> gekObjNamen;
            std::vector<std::vector<std::string>> gebObjNamen;
            std::vector<int> tempBudgets;
            std::vector<int> gekObjAnz;
            std::vector<int> gebObjAnz;               
            std::cout << MRobj[MomentanerSpieler].Msg << "\n";
            for (size_t i = 0; i < 4; i++)
            {
                gekObjNamen.push_back(player[i].getGekObjNamen()); // Hier wird angenommen, dass getGekObjNamen() eine std::vector<std::string> zurückgibt
                gebObjNamen.push_back(player[i].getGebObjNamen());    // Hier wird angenommen, dass getGebObjNamen() eine std::vector<std::string> zurückgibt
                tempBudgets.push_back(player[i].getBudget());
                gekObjAnz.push_back(player[i].getGekObjAnz());          // Hier wird angenommen, dass getGekObjAnz() eine int zurückgibt
                gebObjAnz.push_back(player[i].getGebObjAnz());        // Hier wird angenommen, dass getGebObjAnz() eine int zurückgibt
            }
            ControlEngine.AusgabeSpielerInformationen(SpielerNamen.data(), tempBudgets.data(), gekObjAnz.data(), gebObjAnz.data(), AnzahlSpieler, x / 2 - 90, y / 2 - 36, gekObjNamen, gebObjNamen);
        }


        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
        if (player[MomentanerSpieler].getBudget() < 0)
        {
			GameFinished = TRUE;
			Spiellaueft = FALSE;
        }
    }
    if (GameFinished) {
		save_highscores("highscores.txt",{}); //TODO: implementieren und auf Funktionalität testen
    }
}
int TServer::GetLongestStringVector(std::vector<std::string> s) {
    int temp = 0;
    for (std::string var : s) {
        if (var.size()>temp)
        {
            temp = var.size();
        }
    }
    return temp;
}








int main() {
    TServer server;
    server.UnitTest();
    return 0;
}

