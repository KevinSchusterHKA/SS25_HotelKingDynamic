#include "TServerEngine.h"
#include <chrono>
#include <thread>
#define __AUSGABE_NACHRICHT_ZEIT 1000  
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
        Verkaufen,
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
   
    std::vector<std::string> Spielregeln = {
     "1. Ziel des Spiels: Das Ziel ist es, einen anderen Spieler in den Bankrott zu treiben.",
     "2. Spielvorbereitung: Jeder Spieler wird automatisch einer Spielfigur mit einer besonderen Farbe zugewiesen und erhaelt ein Startkapital.",
     "3. Spielablauf: Die Spieler wuerfeln und ziehen entsprechend der Augenzahl.",
     "4. Grundstuecke kaufen: Landen Sie auf einem unbesetzten Grundstueck, koennen Sie es kaufen.",
     "5. Miete zahlen: Wenn Sie auf einem Grundstueck eines anderen Spielers landen, muessen Sie Miete zahlen.",
     "6. Haeuser und Hotels: Sie koennen Haeuser und Hotels auf Ihren Grundstuecken bauen, um die Miete zu erhoehen.",
     "7. Gefaengnis: Sie koennen ins Gefaengnis kommen, wenn Sie auf das entsprechende Feld landen oder eine Karte ziehen.",
     "8. Ereignis- und Gemeinschaftskarten: Ziehen Sie Karten, die positive oder negative Effekte haben koennen.",
     "9. Bankrott: Wenn Sie nicht mehr genug Geld haben, um Ihre Schulden zu begleichen, sind Sie bankrott.",
     "10. Spielende: Das Spiel endet, wenn ein Spieler bankrott geht.",
     "11. Handelsoptionen: Spieler koennen untereinander handeln, um ihre Position zu verbessern.",
     "12. Wuerfel: Bei einem Pasch duerfen Sie erneut wuerfeln, aber bei dreimaligem Pasch muessen Sie ins Gefaengnis.",
     "13. Strassenbahn: Spieler koennen die Strassenbahn benutzen, um schneller voranzukommen.",
     "14. Haueser und Hotels: Bevor man eine Strasse von Strassenset verkaufen kann darf keine Gebaeude mehr auf einer dieser Strassen sein.",
     "15. Strassen Verkaufen: Um eine Strasse zu Verkaufen geben Sie als Gebaeudeanzahl die Zahl 0 ein.",
     "16. Fairplay: Spielen Sie fair und respektieren Sie die Regeln."
    };
    COORD CursorPos = { 0,0 };
	std::vector<std::string> SpielerNamen;
    std::vector<TPlayer*> playerRefs;
    vector<int> WurfelWert;
    vector<int> IndexReihenfolge(4, 0);
    string SpielerNachricht="";
    int option = 0, AnzahlSpieler = 0, AnzahlCpuGegner = 0, MomentanerSpieler = 0, Rundenzaehler = 1, x = 0, y = 0, AnzahlRunden = 0, StrasseBauen = -1, Angebot = -1, Strasse = -1, target = 0, ID = -1, targetPlayerOut = -1, ReferencePlayer = 0;
    bool Spiellaueft = TRUE, RundeVorhanden = FALSE, HatGewuerfelt = FALSE, GameFinished = FALSE, UpdateSpielfeld = FALSE, Handel_once_cpu = false, cpudone = false, gleicheWuerfe=true, cpu_train =FALSE;
    bool DurchKaufen = TRUE;
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
    system("chcp 850");
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
        system("cls");
    }
    Menues MenueAuswahl = Menues::Start;
    Menues MenueLetztes = MenueAuswahl;
    option = 0;
    while (Spiellaueft)
    {
        DWORD start_time = GetTickCount64();
        
        if (player[IndexReihenfolge[MomentanerSpieler]].imGefaengnis())
        {
            ConfigEngineLogging.playerMoney(player[IndexReihenfolge[MomentanerSpieler]].getName(), player[IndexReihenfolge[MomentanerSpieler]].getBudget());
            
            player[IndexReihenfolge[MomentanerSpieler]].decGefaengnisRunden();
            AnzahlRunden++;

            ConfigEngineLogging.newRound();
            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
            HatGewuerfelt = false;
            MomentanerSpieler++;
            if ((MomentanerSpieler >= AnzahlSpieler + AnzahlCpuGegner) && RundeVorhanden) {
                ConfigEngineLogging.newRound();
                MomentanerSpieler = 0;
            }
            switch (IndexReihenfolge[MomentanerSpieler])
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
        }  

        
        

        EingabeCh = MenueOptionen::Reset;
            if (_kbhit()) {
                EingabeCh = _getch();
            }
                if ((player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1) && (!HatGewuerfelt))
                { 
                    Sleep(1000);
                    EingabeCh = '\r';
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
                        for (size_t i = 0; i < AnzahlSpieler; i++)
                        {
                            player[i].setName(SpielerNamen[i]);
							player[i].setID(i);
                            player[i].setHuman(HUMAN);
                        }
                        for (size_t i = AnzahlSpieler; i < AnzahlSpieler + AnzahlCpuGegner; i++) {
                            player[i].setName(SpielerNamen[i]);
                            player[i].setID(i);
                            player[i].setHuman(CPU1);  
                        }
                        MapEngine.SetPlayerNumber(AnzahlSpieler + AnzahlCpuGegner);
                        for (int i = 0; i < AnzahlSpieler + AnzahlCpuGegner; ++i) {
                            playerRefs.push_back(&player[i]);
                        }

                        ConfigEngineLogging.newRound();
                        ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                        // Würfelreihenfolge festlegen:
                        gleicheWuerfe = true;
                        do {
                            WurfelWert.clear();
                            gleicheWuerfe = false;
                            for (int i = 0; i < AnzahlSpieler + AnzahlCpuGegner; i++) {
                                int temp1 = player[i].wurfeln();
                                int temp2 = player[i].wurfeln();
                                WurfelWert.push_back(temp1 + temp2);
                                
                            }
                            // Prüfen, ob alle Würfe unterschiedlich sind
                            for (int i = 0; i < (int)WurfelWert.size(); ++i) {
                                for (int j = i + 1; j < (int)WurfelWert.size(); ++j) {
                                    if (WurfelWert[i] == WurfelWert[j]) {
                                        gleicheWuerfe = true;
                                        break;
                                    }
                                }
                                if (gleicheWuerfe) 
                                {
                                    system("cls");
                                    break;
                                }
                            }
                        } while (gleicheWuerfe);
						// Ausgabe der Würfelergebnisse
						ControlEngine.SetConsoleFontSize(20);
                        for (int i = 0; i < AnzahlSpieler + AnzahlCpuGegner; i++) {
                            ControlEngine.AusgabeNachricht(player[i].getName() +  " Wuerfelergebnis:" + to_string(WurfelWert[i]), 10, 10 * i, static_cast<Farbe>(static_cast<int>(Farbe::Rot) + i));
                        }
                        Sleep(4000);
                        system("cls");
						ControlEngine.SetConsoleFontSize(8);
                        // Index-Vektor erstellen und richtig resizen!
                        IndexReihenfolge.resize(WurfelWert.size());
                        for (int i = 0; i < (int)WurfelWert.size(); ++i) {
                            IndexReihenfolge[i] = i;
                        }

                        // Sortieren der Indizes nach den Werten in WurfelWert (absteigend)
                        sort(IndexReihenfolge.begin(), IndexReihenfolge.end(),
                            [&WurfelWert](int a, int b) {
                                return WurfelWert[a] > WurfelWert[b];
                            });
                        switch (IndexReihenfolge[MomentanerSpieler])
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
                      
                    }
             		if (option == MenueOptionen::Highscore) { //HIGHSCORE ANZEIGEN
					    std::vector<HighscoreEntry> playerHS;
					    load_highscores("highscores.txt", playerHS);
                        std::vector<std::string> playerNames;
                        std::vector<int> playerScore;
                        for (size_t i = 0; i < playerHS.size(); i++)
                        {
                            playerNames.push_back(playerHS[i].playerName);
                            playerScore.push_back(playerHS[i].score);
                        }

                        ControlEngine.AusgabeHighscore(playerNames.data(), playerScore.data(), playerHS.size(), x / 2 - this->GetLongestStringVector(playerNames) / 2 - 6, y / 2 + ControlEngine.GetAnzMenuepunkteStartOptionen() + 2);
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
                            //PLAYERENGINE
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::left << player[IndexReihenfolge[MomentanerSpieler]].getName() + " : wirft den Wuerfel!";

                            player[IndexReihenfolge[MomentanerSpieler]].Wurfelmechn();

                            int wuerfel1 = player[IndexReihenfolge[MomentanerSpieler]].getWurfel(0);
                            int wuerfel2 = player[IndexReihenfolge[MomentanerSpieler]].getWurfel(1);
                            HatGewuerfelt = true;

                            ControlEngine.AusgabeWuerfel(wuerfel1, x / 2 - 160, y / 2 - 30, MomentanerSpielerFarbe);  
                            ControlEngine.AusgabeWuerfel(wuerfel2, x / 2 - 150, y / 2 - 30, MomentanerSpielerFarbe);  
                            ConfigEngineLogging.playerRollingDice(wuerfel1, wuerfel2);

                            if (player[IndexReihenfolge[MomentanerSpieler]].paschcheck()) {
                                HatGewuerfelt = FALSE;
                                player[IndexReihenfolge[MomentanerSpieler]].incPaschCounter();
                            }
                            else {
                                player[IndexReihenfolge[MomentanerSpieler]].setPaschCounter(0);
                            }
                            if (player[IndexReihenfolge[MomentanerSpieler]].getPaschCounter() == 3) {
                                MapEngine.setPlayer(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getPosition(), -1);//TODO:mit Map absprechen wegen dem Gefaegnis
                                player[IndexReihenfolge[MomentanerSpieler]].setPaschCounter(0);
                                break;
                            }

                            //MAPENGINE - Bug Bahnfahren erst nächste Runde nach Würfeln
                            //if (MRobj[IndexReihenfolge[MomentanerSpieler]].Type == 1 && (player[IndexReihenfolge[MomentanerSpieler]].getHuman()==HUMAN))
                            //{
                            //    //MenueAuswahl = Menues::BahnFahren;
                            //}
                            //else {
                            player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], wuerfel1 + wuerfel2, 0));
                            MRobj[IndexReihenfolge[MomentanerSpieler]] = MapEngine.getSpaceProps(IndexReihenfolge[MomentanerSpieler]);
                            if (MRobj[IndexReihenfolge[MomentanerSpieler]].Msg == "Du erhaeltst eine Freiheitskarte") {
								player[IndexReihenfolge[MomentanerSpieler]].setGefaengnisFreiKarte(player[IndexReihenfolge[MomentanerSpieler]].getGefaengnisFreiKarte() + 1);
                            }
                            if ((MRobj[IndexReihenfolge[MomentanerSpieler]].Rent != -1) && (MRobj[IndexReihenfolge[MomentanerSpieler]].Type != 1) && (MRobj[IndexReihenfolge[MomentanerSpieler]].Type != 7))
                            {
                                player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                            }
                            if (MRobj[IndexReihenfolge[MomentanerSpieler]].Type == 7)
                            {
                                player[IndexReihenfolge[MomentanerSpieler]].erhalte(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                            }
                            if (MRobj[IndexReihenfolge[MomentanerSpieler]].Owner != -1)
                            {
                                player[MRobj[IndexReihenfolge[MomentanerSpieler]].Owner].erhalte(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                            }

                            //Logger verschiedene Felder
                            switch (MRobj[IndexReihenfolge[MomentanerSpieler]].Type) {
                            case _type::TypeStreet: case _type::TypeStation: case _type::TypePark:
                                ConfigEngineLogging.playerOnStreet(MapEngine.getName(player[IndexReihenfolge[MomentanerSpieler]].getPosition()));
                                break;

                            case _type::TypeChance:
                                ConfigEngineLogging.onEventField(MRobj[IndexReihenfolge[MomentanerSpieler]].Msg);
                                break;

                            case _type::TypeChest:
                                ConfigEngineLogging.onChestField(MRobj[IndexReihenfolge[MomentanerSpieler]].Msg);
                                break;

                            case _type::TypePrison:
                                if (!player[IndexReihenfolge[MomentanerSpieler]].imGefaengnis())
                                {
                                    ConfigEngineLogging.playerOnStreet(MapEngine.getName(player[IndexReihenfolge[MomentanerSpieler]].getPosition()));
                                }
                                break;

                            case _type::TypeTax:
                                ConfigEngineLogging.payTax();
                                break;
                            }
                            //}
                            DurchKaufen = FALSE;

                        }
                        else {
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::left << "Du hast schon gewuerfelt!";
                        }
                    }
                    if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() ==CPU1 )//cpu buy street
                    {
                        bool istFrei = true;

                        for (int i = 0; i < AnzahlSpieler+AnzahlCpuGegner; i++) {
                            if (player[i].besitztStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition())) {
                                istFrei = false;
                                break;
                            }
                        }

                        if (istFrei) {
                            Sleep(500);
                                if (player[IndexReihenfolge[MomentanerSpieler]].tryBuyStreetcpu(MapEngine))
                                {
                                    int price = MapEngine.buyStreet(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(price);
                                    player[IndexReihenfolge[MomentanerSpieler]].addStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition(), SpielerNachricht);
                                    if (SpielerNachricht != "") {
                                        ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                                        Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                        SpielerNachricht = "";
                                    }
                                    if (price != -1) {
                                        ConfigEngineLogging.playerBuysObject(MapEngine.getName(player[IndexReihenfolge[MomentanerSpieler]].getPosition()), price);
                                    }
                                }

                        }
                    }
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::Kaufen )
                    {
						MRobj[IndexReihenfolge[MomentanerSpieler]] = MapEngine.getSpaceProps(IndexReihenfolge[MomentanerSpieler] );
                        //player[MomentanerSpieler].bezahle(MapEngine.buyStreet(MomentanerSpieler, player[MomentanerSpieler].getBudget()));
                        //player[MomentanerSpieler].addStrasse(player[MomentanerSpieler].getPosition());
                        //ConfigEngineLogging.playerBuysObject("Straße wurde gekauft"); //TODO: Mit MapEngine absprechen wegen String

                        // Prüfen ob die Straße schon jemand besitzt
                        DurchKaufen = TRUE;
                        bool istFrei = true;

                        for (int i = 0; i < AnzahlSpieler+AnzahlCpuGegner; i++) {
                            if (player[i].besitztStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition())) {
                                istFrei = false;
                                break;
                            }
                        }

                        // Wenn Straße frei ist und genug Geld hat: kaufen
                        if (istFrei && MRobj[IndexReihenfolge[MomentanerSpieler]].Type==TypeStreet) {
                            if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1) {
                                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                if (player[IndexReihenfolge[MomentanerSpieler]].tryBuyStreetcpu(MapEngine))
                                {

                                    int price = MapEngine.buyStreet(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                                    if(player[IndexReihenfolge[MomentanerSpieler]].getBudget() - price >= 0 && price != -1) {
                                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(price);
                                        player[IndexReihenfolge[MomentanerSpieler]].addStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition(), SpielerNachricht);
                                        if (SpielerNachricht != "") {
                                            ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                                            Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                            SpielerNachricht = "";
                                        }
                                    }
                                    if (price != -1) {
                                        ConfigEngineLogging.playerBuysObject(MapEngine.getName(player[IndexReihenfolge[MomentanerSpieler]].getPosition()), price);
                                    };
                                }
                            }
                            else {
                                int price = MapEngine.buyStreet(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                                if (player[IndexReihenfolge[MomentanerSpieler]].getBudget() - price >= 0 && price != -1) {
                                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(price);
                                    player[IndexReihenfolge[MomentanerSpieler]].addStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition(), SpielerNachricht);
                                    if (SpielerNachricht != "") {
                                        ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                                        Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                        SpielerNachricht = "";
                                    }
                                }
                                
                                if (price != -1) {
                                    ConfigEngineLogging.playerBuysObject(MapEngine.getName(player[IndexReihenfolge[MomentanerSpieler]].getPosition()), price);
                                }
                            }
                        }
                        if (MRobj[IndexReihenfolge[MomentanerSpieler]].Type==TypeStation)
                        {
							MenueAuswahl = Menues::BahnFahren;
                        }
                    }
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::Bauen)
                    {
                        ControlEngine.AusgabeGebaeudeBauen(option, StrasseBauen, x / 2 - 213, y / 2 - 20, MomentanerSpielerFarbe);
                        //TODO: Player und Map Bauen auf Straße implementieren
                        int space = MRobj[IndexReihenfolge[MomentanerSpieler]].SpaceNr;// Bug
                        space = StrasseBauen;
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.buyHouses(IndexReihenfolge[MomentanerSpieler], space, player[IndexReihenfolge[MomentanerSpieler]].getBudget()));
                        //player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.buyHouses(MomentanerSpieler, player[IndexReihenfolge[MomentanerSpieler]].getBudget()));
                        int houseBuilt = player[IndexReihenfolge[MomentanerSpieler]].baueHaus(StrasseBauen,playerRefs, SpielerNachricht);
                        if (SpielerNachricht != "") {
                            ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                            Sleep(__AUSGABE_NACHRICHT_ZEIT);
                            SpielerNachricht = "";
                        }
                        if (houseBuilt != -1) {
                            ConfigEngineLogging.playerBuildsBuilding(houseBuilt); 
                        }
                        StrasseBauen = -1;
                    }
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::Handeln) // Bug
                    {
                        std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::endl;
                        ControlEngine.AusgabeStrasseHandeln(option, Strasse, Angebot, x / 2 -211, y / 2-20, MomentanerSpielerFarbe);
                        for (size_t i = 0; i < AnzahlCpuGegner+AnzahlSpieler; i++)
                        {
                            if (player[i].besitztStrasse(Strasse)) {
                                target = player[i].getHuman();
                                ID = player[i].getID();
                            }
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        if (target == CPU1) {
                            if (player[ID].acceptTradecpu(Strasse, Angebot, IndexReihenfolge[MomentanerSpieler],playerRefs, MapEngine, SpielerNachricht))
                            {
                                
                            }
                            if (SpielerNachricht != "") {
                                ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                                Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                SpielerNachricht = "";
                            }
                        }
                        else {
                            MenueAuswahl = Menues::Handel;
                        }
					    
					    //TODO: ConfigEngineLogging.playerTradesObject("Objekt wurde gehandelt");
                    }
                    if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1)//cpu logic
                    {
                        Angebot = player[IndexReihenfolge[MomentanerSpieler]].handelcpu(IndexReihenfolge[MomentanerSpieler], AnzahlSpieler + AnzahlCpuGegner, playerRefs, targetPlayerOut, Strasse, MapEngine);//cpu trade 
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        if (targetPlayerOut != -1) {
                            if (!Handel_once_cpu)
                            {
                                for (size_t i = 0; i < AnzahlCpuGegner + AnzahlSpieler; i++)
                                {
                                    if (player[i].besitztStrasse(Strasse)) {
                                        target = player[i].getHuman();
                                        ID = player[i].getID();
                                    }
                                }
                                if (player[targetPlayerOut].getHuman() == CPU1)
                                {
                                    
                                    player[targetPlayerOut].acceptTradecpu(Strasse, Angebot, IndexReihenfolge[MomentanerSpieler], playerRefs, MapEngine, SpielerNachricht);
                                    if (SpielerNachricht != "") {
                                        ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                                        Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                        SpielerNachricht = "";
                                    }
                                }
                                else {
                                    ControlEngine.AusgabeJaNeinOptionCPU(option, x / 2 - 41, y / 2 - 9, static_cast<Farbe>(static_cast<int>(Farbe::BG_Rot) + player[targetPlayerOut].getID()), "Akzeptierst du den Handel Spieler wem die Strasse gehoert? (schreibe ja oder nein)", Strasse, Angebot);
                                    if (option == 0)
                                    {
                                        
                                        player[IndexReihenfolge[MomentanerSpieler]].Handeln(playerRefs, Strasse, Angebot, SpielerNachricht);
                                        if (SpielerNachricht != "") {
                                            ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                                            Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                            SpielerNachricht = "";
                                        }
                                    }
                                    else
                                    {
                                        ControlEngine.AusgabeNachricht("Handel abgelehnt!", x / 2 - 9, y / 2 - 1, MomentanerSpielerFarbe);
                                        Sleep(__AUSGABE_NACHRICHT_ZEIT);
                                    }
                                }
                            }


                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        bool answer = player[IndexReihenfolge[MomentanerSpieler]].tryBuildHousecpu(playerRefs, MapEngine, SpielerNachricht);//buildhouse
                        if (SpielerNachricht != "") {
                            ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                            Sleep(__AUSGABE_NACHRICHT_ZEIT);
                            SpielerNachricht = "";
                        }
                        
                        player[IndexReihenfolge[MomentanerSpieler]].cpuHausOderStrassenVerkauf(playerRefs, MapEngine, SpielerNachricht);//verkauf haus
                        if (SpielerNachricht != "") {
                            ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                            Sleep(__AUSGABE_NACHRICHT_ZEIT);
                            SpielerNachricht = "";
                        }
                        cpudone = true;
                    
                    if (player[IndexReihenfolge[MomentanerSpieler]].takebahn(playerRefs, MRobj[IndexReihenfolge[MomentanerSpieler]].Rent, player[IndexReihenfolge[MomentanerSpieler]].getPosition(),AnzahlCpuGegner+AnzahlSpieler,MapEngine))
                    {
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl(), 1));
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                        switch (player[IndexReihenfolge[MomentanerSpieler]].getPosition() - player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl()) {
                            //KIT Campus|-> Durlach BF
                        case 5:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(25 + player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl());
                            cpudone = true;
                            ConfigEngineLogging.usesTrain("KIT Campus", "Durlach BF");
                            break;
                            //Zuendhuetle|-> Entenfang
                        case 12:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(28 + player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl());
                            cpudone = true;
                            ConfigEngineLogging.usesTrain("Zuendhuetle", "Entenfang");
                            break;
                            //Europaplatz|-> Hauptbahnhof
                        case 15:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(35 + player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl());
                            cpudone = true;
                            ConfigEngineLogging.usesTrain("Europaplatz", "Hauptbahnhof");
                            break;
                            //Durlach BF|-> KIT Campus
                        case 25:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(5 + player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl());
                            cpudone = true;
                            ConfigEngineLogging.usesTrain("Durlach BF", "KIT Campus");
                            break;
                            //Entenfang|-> Zuendhuetle
                        case 28:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(12 + player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl());
                            cpudone = true;
                            ConfigEngineLogging.usesTrain("Entenfang", "Zuendhuetle");
                            break;
                            //Hauptbahnhof | ->Europaplatz
                        case 35:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(15 + player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl());
                            cpudone = true;
                            ConfigEngineLogging.usesTrain("Hauptbahnhof", "Europaplatz");
                            break;

                        }

                    }
                    else {
                        cpudone = true;
                    }
                    
                        if (HatGewuerfelt&& cpudone)
                        {

                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            ConfigEngineLogging.playerMoney(player[IndexReihenfolge[MomentanerSpieler]].getName(), player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            HatGewuerfelt = false;
                            system("cls");
                            ConfigEngineLogging.newRound();
                            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                            MomentanerSpieler++;
                            if ((MomentanerSpieler >= AnzahlSpieler + AnzahlCpuGegner) && RundeVorhanden) {
                                MomentanerSpieler=0;
                            }
                            ConfigEngineLogging.newRound();
                            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                            cpudone = false;
                        }
                    }
                    switch (IndexReihenfolge[MomentanerSpieler])
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
                       if (option + MenueOptionen::Wuerfeln == MenueOptionen::Verkaufen) {
                           int Strasse = -1,Gebaude = -1;
                           ControlEngine.AusgabeVerkaufen(option, Strasse,Gebaude, x / 2 - 215, y / 2 - 20, MomentanerSpielerFarbe);
                           player[IndexReihenfolge[MomentanerSpieler]].verkaufeHaus(Strasse, Gebaude, playerRefs, SpielerNachricht);
                           MapEngine.sellHouse(IndexReihenfolge[MomentanerSpieler], Strasse);
                           if (SpielerNachricht != "") {
                               ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                               Sleep(__AUSGABE_NACHRICHT_ZEIT);
                               SpielerNachricht = "";
                           }
                           //Logik wegen dem Verkaufen - Abfrage ob Gebaude und Strasse in Besitz zum Verkaufen 
                           system("cls");
                       }
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::RundeBeenden)
                    {
                        if (HatGewuerfelt)
                        {
                            AnzahlRunden++;
                            ConfigEngineLogging.playerMoney(player[IndexReihenfolge[MomentanerSpieler]].getName(), player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                            if (player[IndexReihenfolge[MomentanerSpieler]].imGefaengnis())
                            {
                                ConfigEngineLogging.playerInPrison();
                            }
                            HatGewuerfelt = false;
                            system("cls");
                            
                            ConfigEngineLogging.newRound();
                            MomentanerSpieler++;
                            if ((MomentanerSpieler >= AnzahlSpieler + AnzahlCpuGegner) && RundeVorhanden) {
                                ConfigEngineLogging.newRound();
                                MomentanerSpieler = 0;
                            }
                            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                        }
                        else
                        {
						    std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << player[IndexReihenfolge[MomentanerSpieler]].getName() + " hat noch nicht gewuerfelt!" << std::endl;
                        }
                        switch (IndexReihenfolge[MomentanerSpieler])
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
						Sleep(100);
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
                            GameState GsTemp;
                            PlayerState PlTemp;
                            GsTemp.diceOrder = IndexReihenfolge;
                            GsTemp.currentPlayerIndex = IndexReihenfolge[MomentanerSpieler];
                            for (size_t i = 0; i < AnzahlSpieler+AnzahlCpuGegner; i++)
                            {
                                PlTemp.budget = player[i].getBudget();
                                PlTemp.builtObjects = player[i].getHaueser();               // TODO: getGebObjVector Rückgabewert 40 std::vector  mit nuller aufgefüllt außer an den Positionen der Straßen Anzahl Gebaute Gebaude. kontrollieren
                                PlTemp.hasFreeJailCard = player[i].getGefaengnisFreiKarte();
                                PlTemp.inJail = player[i].imGefaengnis();
                                PlTemp.name = player[i].getName();
                                PlTemp.ownedObjects = player[i].getGekObjVector();
                                PlTemp.position = player[i].getPosition();
								PlTemp.isHuman = player[i].getHuman();
                                GsTemp.players.push_back(PlTemp);
                            }
                            GsTemp.roundCount=AnzahlRunden;
                            GsTemp.cpuCount = AnzahlCpuGegner;
                            GsTemp.playerCount = AnzahlSpieler;
                            GsTemp.roundCount = AnzahlRunden;
                            CursorPos = { short(x / 2 - ControlEngine.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 1) };
                            ControlEngine.UpdateCursorPosition(CursorPos);
						    save_game("Spielstand.txt", GsTemp);    //TODO: implementieren und auf Funktionalität testen
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird gespeichert!";
                        }
                        else
                        {
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Es gibt keine Runde zum speichern!";
                        }
                    }
                    if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielLaden) {
                        GameState GsTemp;
                        std::ifstream file("Spielstand.txt");
                        if (file.is_open())
                        {
                            CursorPos = { short(x / 2 - ControlEngine.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 1) };
                            ControlEngine.UpdateCursorPosition(CursorPos);
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Spiel wird geladen!";
                            //load_config("Config.txt", {}); //TODO: implementieren und auf Funktionalität testen
                            load_game("Spielstand.txt", GsTemp);//TODO: implementieren und auf Funktionalität testen
                            AnzahlSpieler = GsTemp.playerCount;
                            AnzahlCpuGegner = GsTemp.cpuCount;
							IndexReihenfolge = GsTemp.diceOrder;
                            MomentanerSpieler = GsTemp.currentPlayerIndex;
                            playerRefs.clear();
                            SpielerNamen.clear();
                            for (int i = 0; i < AnzahlSpieler+AnzahlCpuGegner; i++)
                            {
                                TPlayer temp(   i, 
                                                GsTemp.players[i].name, 
                                                GsTemp.players[i].budget, 
                                                GsTemp.players[i].position, 
                                                GsTemp.players[i].inJail, 
                                                GsTemp.players[i].inJail,
                                                GsTemp.players[i].ownedObjects, 
                                                GsTemp.players[i].builtObjects,
                                                SpeicherZuInternFormat(GsTemp.players[i].builtObjects));
								temp.setHuman(GsTemp.players[i].isHuman);
                                temp.setGefaengnisFreiKarte(GsTemp.players[i].hasFreeJailCard);
								SpielerNamen.push_back(GsTemp.players[i].name);
                                player[i] = temp;
								playerRefs.push_back(&player[i]);
                            }
                            MapEngine = Map();
                            MapEngine.loadGame(GsTemp.players);
							MomentanerSpielerFarbe = static_cast<Farbe>(static_cast<int>(Farbe::BG_Rot) + IndexReihenfolge[MomentanerSpieler]);
                            RundeVorhanden = TRUE; //Wenn das Spiel korrekt geladen wird
                        }
                        else
                        {
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Es gibt keinen Spielstand!";
                        }
                    }
                    if ((option + MenueOptionen::Fortfahren) == MenueOptionen::SpielRegeln) { 
                        ControlEngine.AusgabeSpielRegeln(Spielregeln, x / 2 - this->GetLongestStringVector(Spielregeln)/ 2 - 8, y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 2); 
                    }
                    if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Beenden + 11) { Spiellaueft = FALSE; }
                    if ((option + MenueOptionen::Fortfahren) == MenueOptionen::Highscore + 14) { 
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
                        ReferencePlayer = player[IndexReihenfolge[MomentanerSpieler]].Handeln(playerRefs, Strasse, Angebot, SpielerNachricht);
                        if (SpielerNachricht != "") {
                            ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                            Sleep(__AUSGABE_NACHRICHT_ZEIT);
                            SpielerNachricht = "";
                        }
                    }
                    else
                    {
						ControlEngine.AusgabeNachricht("Handel abgelehnt!", x / 2 - 9, y / 2 - 1, MomentanerSpielerFarbe);
                        Sleep(2000);
                    }
					break;
                case Menues::BahnFahren:
                    
                    MenueAuswahl = Menues::Spieler;
                    UpdateSpielfeld = TRUE;
                    //std::cout << player[IndexReihenfolge[MomentanerSpieler]].getPosition();

                    system("cls");

                    if (!option)
                    {
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], 0, 1));
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                        switch (player[IndexReihenfolge[MomentanerSpieler]].getPosition()) {
                            //KIT Campus|-> Durlach BF
                        case 5:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(25  );
                            ConfigEngineLogging.usesTrain("KIT Campus", "Durlach BF");
                            break;
                            //Zuendhuetle|-> Entenfang
                        case 12:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(28 );
                            ConfigEngineLogging.usesTrain("Zuendhuetle", "Entenfang");
                            break;
                            //Europaplatz|-> Hauptbahnhof
                        case 15:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(35  );
                            ConfigEngineLogging.usesTrain("Europaplatz", "Hauptbahnhof");
                            break;
                            //Durlach BF|-> KIT Campus
                        case 25:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(5  );
                            ConfigEngineLogging.usesTrain("Durlach BF", "KIT Campus");
                            break;
                            //Entenfang|-> Zuendhuetle
                        case 28:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(12 );
                            ConfigEngineLogging.usesTrain("Entenfang", "Zuendhuetle");
                            break;
                            //Hauptbahnhof | ->Europaplatz
                        case 35:
                            player[IndexReihenfolge[MomentanerSpieler]].setPosition(15 );
                            ConfigEngineLogging.usesTrain("Hauptbahnhof", "Europaplatz");
                            break;

                        }
                        
                    }
                    else {
                        //player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl(), 0));
                    }

                    MRobj[IndexReihenfolge[MomentanerSpieler]] = MapEngine.getSpaceProps(IndexReihenfolge[MomentanerSpieler]);
                    if ((MRobj[IndexReihenfolge[MomentanerSpieler]].Rent != -1) && (MRobj[IndexReihenfolge[MomentanerSpieler]].Type != 1) && (MRobj[IndexReihenfolge[MomentanerSpieler]].Type != 7))
                    {
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                    }
                    if (MRobj[IndexReihenfolge[MomentanerSpieler]].Type == 7)
                    {
                        player[IndexReihenfolge[MomentanerSpieler]].erhalte(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                    }
                    if (MRobj[IndexReihenfolge[MomentanerSpieler]].Owner != -1)
                    {
                        player[MRobj[IndexReihenfolge[MomentanerSpieler]].Owner].erhalte(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                    }
                    DurchKaufen = FALSE;

                    ConfigEngineLogging.playerOnStreet(MapEngine.getName(player[IndexReihenfolge[MomentanerSpieler]].getPosition()));
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
            ReferencePlayer = WemGehoertStrasse(Strasse, playerRefs);
            ControlEngine.AusgabeJaNeinOption(option, x / 2 - 198, y / 2 - 9, static_cast<Farbe>(static_cast<int>(Farbe::BG_Rot) + player[ReferencePlayer].getID()), "Akzeptierst du den Handel Spieler wem die Strasse gehoert?");
            break;
        case Menues::BahnFahren:
            if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == HUMAN)
            {
                ControlEngine.AusgabeJaNeinOption(option, x / 2 - 198, y / 2 - 9, MomentanerSpielerFarbe, "Bahn fahren?"); // Bug
            }
            break;
        default:
            break;
        }

        if (UpdateSpielfeld)
        {
            if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1&&cpu_train)
            {
                MomentanerSpieler++;
                cpu_train = FALSE;
                if ((MomentanerSpieler >= AnzahlSpieler + AnzahlCpuGegner) && RundeVorhanden) {
                    ConfigEngineLogging.newRound();
                    MomentanerSpieler = 0;
                }
                switch (IndexReihenfolge[MomentanerSpieler])
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
            }

            while (MRobj[IndexReihenfolge[MomentanerSpieler]].flag) 
            {
                MRobj[IndexReihenfolge[MomentanerSpieler]] = MapEngine.getSpaceProps(IndexReihenfolge[MomentanerSpieler]);
                if ((MRobj[IndexReihenfolge[MomentanerSpieler]].Rent != -1) && (MRobj[IndexReihenfolge[MomentanerSpieler]].Type != 7))
                {
                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                }
                if (MRobj[IndexReihenfolge[MomentanerSpieler]].Owner != -1)
                {
                    player[MRobj[IndexReihenfolge[MomentanerSpieler]].Owner].erhalte(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                }
            }
            if (!DurchKaufen)
            {
                if (!(MRobj[IndexReihenfolge[MomentanerSpieler]].Msg == ""))
                {
                    ControlEngine.AusgabeNachricht(MRobj[IndexReihenfolge[MomentanerSpieler]].Msg,
                        x / 2 - MRobj[IndexReihenfolge[MomentanerSpieler]].Msg.size() / 2,
                        y / 2,
                        MomentanerSpielerFarbe);
                    Sleep(4000);
                }
                DurchKaufen = TRUE;
            }
            ControlEngine.AusgabeFeld(MapEngine.toStr(), x / 2 - 110, y / 2 - 44);
            std::vector<std::vector<std::string>> gekObjNamen;
            std::vector<std::vector<std::string>> gebObjNamen;
            std::vector<int> tempBudgets;
            std::vector<int> gekObjAnz;
            std::vector<int> gebObjAnz;               
            
          
            for (size_t i = 0; i < AnzahlSpieler+AnzahlCpuGegner; i++)
            {
				SpielerNamen.push_back(player[IndexReihenfolge[i]].getName());        // Hier wird angenommen, dass getName() eine std::string zurückgibt
                gekObjNamen.push_back(player[IndexReihenfolge[i]].getGekObjNamen()); // Hier wird angenommen, dass getGekObjNamen() eine std::vector<std::string> zurückgibt
                gebObjNamen.push_back(player[IndexReihenfolge[i]].getGebObjNamen());    // Hier wird angenommen, dass getGebObjNamen() eine std::vector<std::string> zurückgibt
                tempBudgets.push_back(player[IndexReihenfolge[i]].getBudget());
                gekObjAnz.push_back(player[IndexReihenfolge[i]].getGekObjAnz());          // Hier wird angenommen, dass getGekObjAnz() eine int zurückgibt
                gebObjAnz.push_back(player[IndexReihenfolge[i]].getGebObjAnz());        // Hier wird angenommen, dass getGebObjAnz() eine int zurückgibt

            }
            ControlEngine.AusgabeSpielerInformationen(SpielerNamen.data(), tempBudgets.data(), gekObjAnz.data(), gebObjAnz.data(), AnzahlSpieler+AnzahlCpuGegner, x / 2 - 90, y / 2 - 36, gekObjNamen, gebObjNamen,IndexReihenfolge);

        }


        DWORD elapsed_time = GetTickCount64() - start_time;
        if (elapsed_time < FRAME_DURATION) {
            Sleep(FRAME_DURATION - elapsed_time);
        }

        if (player[IndexReihenfolge[MomentanerSpieler]].getBudget() < 0)
        {
            while (player[IndexReihenfolge[MomentanerSpieler]].getGekObjAnz() + player[IndexReihenfolge[MomentanerSpieler]].getGebObjAnz() > 0 && player[IndexReihenfolge[MomentanerSpieler]].getBudget() < 0) {
                int Strasse = -1, Gebaude = -1;
                ControlEngine.AusgabeVerkaufen(option, Strasse, Gebaude, x / 2 - 215, y / 2 - 20, MomentanerSpielerFarbe);
                player[IndexReihenfolge[MomentanerSpieler]].verkaufeHaus(Strasse, Gebaude, playerRefs, SpielerNachricht);
                if (SpielerNachricht != "") {
                    ControlEngine.AusgabeNachricht(SpielerNachricht, x / 2 - SpielerNachricht.size() / 2, y / 2 - 1, MomentanerSpielerFarbe);
                    Sleep(__AUSGABE_NACHRICHT_ZEIT);
                    SpielerNachricht = "";
                }
                MapEngine.sellHouse(IndexReihenfolge[MomentanerSpieler], Strasse);
                //Logik wegen dem Verkaufen - Abfrage ob Gebaude und Strasse in Besitz zum Verkaufen 
                system("cls");
            }
            GameFinished = TRUE;
            Spiellaueft = FALSE;
        }
        
    }
    if (GameFinished) {
        std::vector<HighscoreEntry> temp;
        for (size_t i = 0; i < AnzahlSpieler+AnzahlCpuGegner; i++)
        {
            temp.push_back({ player[i].getName(),player[i].Score(playerRefs) });
        }
		save_highscores("highscores.txt", temp); //TODO: Funktionalität testen
    }
}


int main() {
    TServer server;
    server.UnitTest();
    return 0;
}

