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
        Handel
    };


    std::string playerNames[4] = { "a","bbbb","ccccc","ddddddddddddddddddddddddddddddddddddddddddddddddddd" };
    std::vector<std::vector<std::string>> GekObjNamen = { { "Strasse1"},
                                                          { "Strasse2","Gebaeude xyz2"},
                                                          { "Strasse3","Gebaeude xyz3","Autobahn nach Karlsruhe3"},
                                                          { "Strasse4","Gebaeude xyz4","Autobahn nach Karlsruhe4","4TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"} };
    std::vector<std::vector<std::string>> GebObjNamen = { { "Haus 1"},
                                                          { "Haus 2","Gebaeude zyx2"},
                                                          { "Haus 3","Gebaeude zyx3","Hotel 3"},
                                                          { "Haus 4","Gebaeude zyx4","Hotel 4","4TEXTSTRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG"} };
    std::vector<std::string> Spielregeln = { "Regel 1", "Regel 2", "Regel 3", "Regel 4", "Regel 5555555555555555555555555555555555555555555555555555555555555" };
    int budget[4] = { 100,10000,100000,99999999 }; //Budget der Spieler
    int gekObjAnz[4] = { 5,15,2,3 };//Anzahl gekaufter Objekte der Spieler
    int gebObjAnz[4] = { 0,2,3,99 };//Anzahl gebaute Objekte der Spieler
    COORD CursorPos = { 0,0 };
    int option = 0;
    bool Spiellaueft = TRUE, RundeVorhanden = FALSE, HatGewuerfelt=FALSE;
    char EingabeCh = MenueOptionen::Reset;
    bool UpdateSpielfeld = FALSE;
    int AnzahlSpieler = 4;
    int MomentanerSpieler = 0;
    int x = 0, y = 0;
    MapReturnObj MRobj[4];

	Farbe MomentanerSpielerFarbe = Farbe::BG_Rot; // Standardfarbe für den ersten Spieler
    TestControl.GetMaximizedConsoleSize(x, y);
    board.SetPlayerNumber(AnzahlSpieler);
    //Ausgabe des Startbildschirms
    do
    {
        DWORD StartZeit = GetTickCount64();
        TestControl.AusgabeStartBildschirm(TRUE, x / 2 - 43, y / 2 - 11);
        DWORD ZeitDifferenz = GetTickCount64() - StartZeit;
        if (ZeitDifferenz < FRAME_DURATION) {
            Sleep(FRAME_DURATION - ZeitDifferenz);
        }
    } while (!_kbhit());
    std::cin.clear();
    system("chcp 850");
    system("cls");
    Menues MenueAuswahl = Menues::Start;
    Menues MenueLetztes = MenueAuswahl;
    while (Spiellaueft)
    {
        DWORD start_time = GetTickCount64();

        if (player[MomentanerSpieler].imGefaengnis())
        {
            player[MomentanerSpieler].decGefaengnisRunden();
            MomentanerSpieler++;
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
            if (option < TestControl.GetAnzMenuepunkteStartOptionen() - 1 && MenueAuswahl == Menues::Start) {
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

                    TestControl.AusgabeHighscore(playerNames.data(), playerScore.data(), player.size(), x / 2 - TestControl.GetLaengstenStringMenueStartOptionen() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteStartOptionen() + 2);
                }
                if (option == MenueOptionen::Optionen) { system("cls"); MenueLetztes = MenueAuswahl; MenueAuswahl = Menues::Optionen; }
                if (option == MenueOptionen::Beenden) { Spiellaueft = FALSE; }
                break;
            case Menues::Spieler:
                CursorPos = { short(x / 2 - 160), short(y / 2 - 40 + TestControl.GetAnzMenuepunkteSpielerOptionen()) };
                TestControl.UpdateCursorPosition(CursorPos);
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Wuerfeln )
                {

                    if (!HatGewuerfelt)
                    {
                        std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler "+to_string(MomentanerSpieler+1)+" : wirft den Wuerfel!";

                        int wuerfel1 = player[MomentanerSpieler].wurfeln();
                        int wuerfel2 = player[MomentanerSpieler].wurfeln();

                        TestControl.AusgabeWuerfel(wuerfel1, x / 2 - 160, y / 2 - 30, MomentanerSpielerFarbe); //die Farbe dem zugehörigen Spieler anpassen
                        TestControl.AusgabeWuerfel(wuerfel2, x / 2 - 150, y / 2 - 30, MomentanerSpielerFarbe); //die Farbe dem zugehörigen Spieler anpassen
                        if (MRobj[MomentanerSpieler].Type == 1)// Bug
                        {
                            player[MomentanerSpieler].bezahle(board.movePlayer(MomentanerSpieler, wuerfel1 + wuerfel2, 1));
                            player[MomentanerSpieler].bezahle(MRobj[MomentanerSpieler].Rent);
                        }
                        else {
                            player[MomentanerSpieler].bezahle(board.movePlayer(MomentanerSpieler, wuerfel1 + wuerfel2, 0));
                        }
                        MRobj[MomentanerSpieler] = board.getSpaceProps(MomentanerSpieler);
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
                        HatGewuerfelt = (wuerfel1!=wuerfel2); // Bug
                    }
                    else {
                        std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler " + to_string(MomentanerSpieler + 1) + " hat schon gewuerfelt!";
                    }
                    
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Kaufen )
                {
                    player[MomentanerSpieler].bezahle(board.buyStreet(MomentanerSpieler, player[MomentanerSpieler].getBudget())); // Bug
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Bauen)
                {
                    int space = 0;
                    player[MomentanerSpieler].bezahle(board.buyHouses(MomentanerSpieler, space, player[MomentanerSpieler].getBudget())); // Bug
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Handeln)
                {
                    std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Handeln von Objekten ist noch nicht implementiert!" << std::endl;
                    //Code zum Handeln von Objekten
                    //player[MomentanerSpieler].handel(board.(MomentanerSpieler, player[MomentanerSpieler].getBudget()));

                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::RundeBeenden)
                {
                    ++MomentanerSpieler %= AnzahlSpieler;
                    HatGewuerfelt = false;
                    system("cls");
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
                        CursorPos = { short(x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 1) };
                        TestControl.UpdateCursorPosition(CursorPos);
                        std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird gespeichert!";
                    }
                    else
                    {
                        std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Es gibt keine Runde zum speichern!";
                    }
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielLaden) {
                    CursorPos = { short(x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 1) };
                    TestControl.UpdateCursorPosition(CursorPos);
                    std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird geladen!";
                    RundeVorhanden = TRUE; //Wenn das Spiel korrekt geladen wird
                }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielRegeln) { TestControl.AusgabeSpielRegeln(Spielregeln, x / 2 - playerNames[3].size() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 2); }
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

                    TestControl.AusgabeHighscore(playerNames.data(), playerScore.data(), player.size(), x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 2);
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
            default:
                break;
            }

            option = Reset + 1;
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
            TestControl.AusgabeSpielerOptionen(option, x / 2 - 160, y / 2 - 44, MomentanerSpielerFarbe); //die Farbe dem zugehörigen Spieler anpassen
            break;
        case Menues::Optionen:
            TestControl.AusgabeSpielOptionen(option, x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2, y / 2 - TestControl.GetAnzMenuepunkteSpielOptionen() / 2);
            break;
        case Menues::Handel:
            TestControl.AusgabeHandelsMenu(option, x / 2 - TestControl.GetLaengstenStringMenueSpielerOptionen() / 2, y / 2 - TestControl.GetAnzMenuepunkteSpielerOptionen() / 2, Farbe::BG_Gelb); //die Farbe dem zugehörigen Spieler anpassen
        default:
            break;
        }

        if (UpdateSpielfeld)
        {
            //TestControl.AusgabeFeld(board.toStr(), x / 2 - 110, y / 2 - 44);
            while (MRobj[MomentanerSpieler].flag)
            {
                MRobj[MomentanerSpieler] = board.getSpaceProps(MomentanerSpieler);
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
            TestControl.AusgabeFeld(board.toStr(), x / 2 - 110, y / 2 - 44);
            /*std::vector<std::string> Namen;
            std::vector<std::vector<std::string>> gekObjNamen;
            std::vector<std::vector<std::string>> gebObjNamen;
            std::vector<int> tempBudgets;
            std::vector<int> gekObjAnz;
            std::vector<int> gebObjAnz;*/
    //        for (size_t i = 0; i < 4; i++)
    //        {
    //            Namen.push_back(player[i].getName());
				//gekObjNamen[i].push_back(player[i].getGekObjNamen()); // Hier wird angenommen, dass getGekObjNamen() eine std::vector<std::string> zurückgibt
				//gebObjNamen.push_back(player[i].getGebObjNamen());    // Hier wird angenommen, dass getGebObjNamen() eine std::vector<std::string> zurückgibt
    //            tempBudgets.push_back(player[i].getBudget());
				//gekObjAnz.push_back(player[i].getGekObjAnz);          // Hier wird angenommen, dass getGekObjAnz() eine int zurückgibt
				//gebObjAnz.push_back(player[i].getGebObjAnz());        // Hier wird angenommen, dass getGebObjAnz() eine int zurückgibt
    //        }
            
            //TestControl.AusgabeSpielerInformationen(Namen.data(), tempBudgets.data(), gekObjAnz.data(), gebObjAnz.data(), AnzahlSpieler, x / 2 - 90, y / 2 - 36, gekObjNamen, gebObjNamen);
            std::cout << MRobj[MomentanerSpieler].Msg << "\n";
            for (int i = 0; i < AnzahlSpieler; i++)
            {
                std::cout << player[i].getBudget() << "     ";
            }
            TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObjAnz, gebObjAnz , AnzahlSpieler, x / 2 - 90, y / 2 - 36, GekObjNamen, GebObjNamen);
        }


        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
    }
}
int main() {
    TServer server;
    server.UnitTest();
    return 0;
}

