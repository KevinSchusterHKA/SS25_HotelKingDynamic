#include "TServerEngine.h"


TServer::TServer(){

}

TServer::~TServer(){
}

int TServer::main() {

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
    bool Spiellaueft = TRUE, RundeVorhanden = FALSE;
    char EingabeCh = MenueOptionen::Reset;
    bool UpdateSpielfeld = FALSE;
    int AnzahlSpieler = 4;
    int x = 0, y = 0;
    TestControl.GetMaximizedConsoleSize(x, y);
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
            else if (option < TestControl.GetAnzMenuepunkteHandelsOptionen() - 1 && MenueAuswahl == Menues::Spieler) {
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
                if (option == MenueOptionen::Highscore) { TestControl.AusgabeHighscore(playerNames, budget, 4, x / 2 - playerNames[3].size() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteStartOptionen() + 2); }
                if (option == MenueOptionen::Optionen) { system("cls"); MenueLetztes = MenueAuswahl; MenueAuswahl = Menues::Optionen; }
                if (option == MenueOptionen::Beenden) { Spiellaueft = FALSE; }
                break;
            case Menues::Spieler:
                CursorPos = { short(x / 2 - 160), short(y / 2 - 36) };
                TestControl.UpdateCursorPosition(CursorPos);
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Wuerfeln)
                {

                    std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler X: wirft den Wuerfel!";

                    TestControl.AusgabeWuerfel(3, x / 2 - 160, y / 2 - 30, Farbe::BG_Gruen); //die Farbe dem zugehörigen Spieler anpassen
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Kaufen)
                {
                    //Code zum Kaufen von Objekten
                    std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Kaufen von Objekten ist noch nicht implementiert!" << std::endl;
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Bauen)
                {
                    std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Bauen von Objekten ist noch nicht implementiert!" << std::endl;
                    //Code zum Bauen von Objekten
                }
                if (option + MenueOptionen::Wuerfeln == MenueOptionen::Handeln)
                {
                    std::cout << setw(TestControl.GetLaengstenStringMenueSpielOptionen()) << "Handeln von Objekten ist noch nicht implementiert!" << std::endl;
                    //Code zum Handeln von Objekten
                }

                TestControl.AusgabeTestFeld(x / 2 - 110, y / 2 - 44);
                TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObjAnz, gebObjAnz, AnzahlSpieler, x / 2 - 90, y / 2 - 36, GekObjNamen, GebObjNamen);
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
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Beenden + 9) { Spiellaueft = FALSE; }
                if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Highscore + 12) { TestControl.AusgabeHighscore(playerNames, budget, 4, x / 2 - playerNames[3].size() / 2 - 8, y / 2 + TestControl.GetAnzMenuepunkteSpielOptionen() + 2); }

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
            TestControl.AusgabeSpielerOptionen(option, x / 2 - 160, y / 2 - 44, Farbe::BG_Gruen); //die Farbe dem zugehörigen Spieler anpassen
            break;
        case Menues::Optionen:
            TestControl.AusgabeSpielOptionen(option, x / 2 - TestControl.GetLaengstenStringMenueSpielOptionen() / 2, y / 2 - TestControl.GetAnzMenuepunkteSpielOptionen() / 2);
            break;
        case Menues::Handel:
            TestControl.AusgabeHandelsMenu(option, x / 2 - TestControl.GetLaengstenStringMenueHandelsOptionen() / 2, y / 2 - TestControl.GetAnzMenuepunkteHandelsOptionen() / 2, Farbe::BG_Gelb); //die Farbe dem zugehörigen Spieler anpassen
        default:
            break;
        }

        if (UpdateSpielfeld)
        {
            TestControl.AusgabeTestFeld(x / 2 - 110, y / 2 - 44);
            TestControl.AusgabeSpielerInformationen(playerNames, budget, gekObjAnz, gebObjAnz, AnzahlSpieler, x / 2 - 90, y / 2 - 36, GekObjNamen, GebObjNamen);
        }


        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }
    }
	return 0;
}

