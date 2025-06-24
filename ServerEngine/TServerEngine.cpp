#include "TServerEngine.h"
#include <chrono>
#include <thread>
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

    std::vector<std::string> Spielregeln = { "Regel 1", "Regel 2", "Regel 3", "Regel 4", "Regel 5555555555555555555555555555555555555555555555555555555555555" };

    COORD CursorPos = { 0,0 };
	std::vector<std::string> SpielerNamen;
    std::vector<TPlayer*> playerRefs;
    vector<int> WurfelWert;
    vector<int> IndexReihenfolge(4, 0);
    int option = 0, AnzahlSpieler = 0, AnzahlCpuGegner = 0, MomentanerSpieler = 0, Rundenzaehler = 1, x = 0, y = 0, AnzahlRunden = 0, StrasseBauen = -1, Angebot = -1, Strasse = -1, target = 0, ID = -1;
    bool Spiellaueft = TRUE, RundeVorhanden = FALSE, HatGewuerfelt = FALSE, GameFinished = FALSE, UpdateSpielfeld = FALSE, Handel_once_cpu = false, cpudone = false, gleicheWuerfe=true;
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
            ConfigEngineLogging.playerInPrison();
            player[IndexReihenfolge[MomentanerSpieler]].decGefaengnisRunden();
            MomentanerSpieler++;
            ConfigEngineLogging.newRound();
            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
            HatGewuerfelt = false;
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

        EingabeCh = MenueOptionen::Reset;
        if (_kbhit()) {
            EingabeCh = _getch();
        }
        else { //logic for cpu auto wurfel
            if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1 && !HatGewuerfelt) {
                std::this_thread::sleep_for(std::chrono::milliseconds(800));
                EingabeCh = '\r';   
            }
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
                    }
                    for (size_t i = AnzahlSpieler; i < AnzahlSpieler + AnzahlCpuGegner; i++) {
                        player[i].setName(SpielerNamen[i]);
                        player[i].setID(i);
                        player[i].setHuman(CPU1);  

                    }
                    MapEngine.SetPlayerNumber(AnzahlSpieler + AnzahlCpuGegner);

                    // Würfelreihenfolge festlegen:
                    gleicheWuerfe = true;
                    do {
                        WurfelWert.clear();
                        gleicheWuerfe = false;
                        for (int i = 0; i < AnzahlSpieler + AnzahlCpuGegner; i++) {
                            int temp1 = player[i].wurfeln();
                            int temp2 = player[i].wurfeln();
                            WurfelWert.push_back(temp1 + temp2);
                            ControlEngine.AusgabeNachricht("Spieler " + to_string(i+1) + " Wuerfelergebnis:" + to_string(WurfelWert[i]), 10, 10*i, static_cast<Farbe>(static_cast<int>(Farbe::Rot) + i));
                        }
				
                        // Prüfen, ob alle Würfe unterschiedlich sind
                        for (int i = 0; i < (int)WurfelWert.size(); ++i) {
                            for (int j = i + 1; j < (int)WurfelWert.size(); ++j) {
                                if (WurfelWert[i] == WurfelWert[j]) {
                                    gleicheWuerfe = true;
                                    break;
                                }
                            }
                            if (gleicheWuerfe) break;
                        }
                    } while (gleicheWuerfe);
                    Sleep(2000);
                    system("cls");
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

                    for (int i = 0; i < AnzahlSpieler+AnzahlCpuGegner; ++i) {
                        playerRefs.push_back(&player[IndexReihenfolge[i]]);
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

                    ConfigEngineLogging.newRound();
                    ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                    break;
                 

                case Menues::Spieler:
                    CursorPos = { short(x / 2 - 160), short(y / 2 - 40 + ControlEngine.GetAnzMenuepunkteSpielerOptionen()) };
                    ControlEngine.UpdateCursorPosition(CursorPos);
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::Wuerfeln )
                    {
                        if (!HatGewuerfelt)
                        {
                            //PLAYERENGINE
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler "+to_string(IndexReihenfolge[MomentanerSpieler]+1)+" : wirft den Wuerfel!";

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
                                MapEngine.setPlayer(IndexReihenfolge[MomentanerSpieler], 10, -1);//TODO:mit Map absprechen wegen dem Gefaegnis
                                player[IndexReihenfolge[MomentanerSpieler]].setPaschCounter(0);
                                break;
                            }

                            //MAPENGINE - Bug Bahnfahren erst nächste Runde nach Würfeln
                            if (MRobj[IndexReihenfolge[MomentanerSpieler]].Type == 1)
                            {
                                MenueAuswahl = Menues::BahnFahren;
                            }
                            else {
                                player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], wuerfel1 + wuerfel2, 0));
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

                                //TODO Logger prüfen ob das so geht
                                switch (MRobj[IndexReihenfolge[MomentanerSpieler]].Type) {
                                case 0:
                                    ConfigEngineLogging.playerOnStreet(MapEngine.getName(player[MomentanerSpieler].getPosition()));
                                    break;
                                    
                                case 1:
                                    ConfigEngineLogging.onEventField(MRobj[IndexReihenfolge[MomentanerSpieler]].Msg);  //TODO: Mit MapEngine absprechen wegen String
                                    break;

                                }
                                

                                
                                
                                ConfigEngineLogging.playerInPrison();                           //TODO: Mit MapEngine absprechen wegen String
                            }
                        }
                        else {
                            std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << std::left << "Spieler " + to_string(IndexReihenfolge[MomentanerSpieler] + 1) + " hat schon gewuerfelt!";
                        }
                    }
                    if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() ==CPU1 )//cpu buy street
                    {
                        bool istFrei = true;

                        for (int i = 0; i < AnzahlSpieler; i++) {
                            if (player[i].besitztStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition())) {
                                istFrei = false;
                                break;
                            }
                        }

                        if (istFrei) {

                                if (player[IndexReihenfolge[MomentanerSpieler]].tryBuyStreetcpu(MapEngine))
                                {
                                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.buyStreet(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getBudget()));
                                    player[IndexReihenfolge[MomentanerSpieler]].addStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition());
                                    ConfigEngineLogging.playerBuysObject(MapEngine.getName(player[MomentanerSpieler].getPosition())); 
                                }

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
                            if (player[i].besitztStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition())) {
                                istFrei = false;
                                break;
                            }
                        }

                        // Wenn Straße frei ist: kaufen
                        if (istFrei) {
                            if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1) {
                                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                                if (player[IndexReihenfolge[MomentanerSpieler]].tryBuyStreetcpu(MapEngine))
                                {
                                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.buyStreet(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getBudget()));
                                    player[IndexReihenfolge[MomentanerSpieler]].addStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition());
                                    ConfigEngineLogging.playerBuysObject(MapEngine.getName(player[MomentanerSpieler].getPosition())); 
                                }
                            }
                            else {
                                player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.buyStreet(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getBudget()));
                                player[IndexReihenfolge[MomentanerSpieler]].addStrasse(player[IndexReihenfolge[MomentanerSpieler]].getPosition());
                                ConfigEngineLogging.playerBuysObject(MapEngine.getName(player[MomentanerSpieler].getPosition()));
                            }
                            
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
                        player[IndexReihenfolge[MomentanerSpieler]].baueHausTEMP(StrasseBauen,MapEngine);
                        ConfigEngineLogging.playerBuildsBuilding("Haus wurde gebaut"); //TODO: Mit MapEngine absprechen wegen String
                        StrasseBauen = -1;
                    }
                 

                    if (player[IndexReihenfolge[MomentanerSpieler]].getHuman() == CPU1)
                    {
                        int street = -1;
                        int targetPlayerOut = -1;
                        int angebotspreis = player[IndexReihenfolge[MomentanerSpieler]].handelcpu(IndexReihenfolge[MomentanerSpieler],AnzahlSpieler+ AnzahlCpuGegner,player, targetPlayerOut, street, MapEngine);//cpu trade 
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        if (angebotspreis != -1) {
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
                                    player[targetPlayerOut].acceptTradecpu(street, angebotspreis, IndexReihenfolge[MomentanerSpieler], playerRefs, MapEngine);

                                }
                                else {

                                    MenueAuswahl = Menues::Handel;

                                }
                            }
                            
                            
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                       bool answer = player[IndexReihenfolge[MomentanerSpieler]].tryBuildHousecpu(player,MapEngine);//buildhouse


                        cpudone = true;
                    }

                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::Handeln) // Bug
                    {
                        std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Handeln von Objekten ist noch nicht implementiert!" << std::endl;
                        ControlEngine.AusgabeStrasseHandeln(option, Strasse, Angebot, x / 2 -211, y / 2-20, Farbe::BG_Rot);
                        for (size_t i = 0; i < AnzahlCpuGegner+AnzahlSpieler; i++)
                        {
                            if (player[i].besitztStrasse(Strasse)) {
                                target = player[i].getHuman();
                                ID = player[i].getID();
                            }
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                        if (target == CPU1) {
                            if (player[ID].acceptTradecpu(Strasse, Angebot, IndexReihenfolge[MomentanerSpieler],playerRefs, MapEngine))
                            {

                            }
                        }
                        else {
                            MenueAuswahl = Menues::Handel;
                        }
					    
					    //TODO: ConfigEngineLogging.playerTradesObject("Objekt wurde gehandelt");
                    }
                    if (player[IndexReihenfolge[MomentanerSpieler]].getHuman()==CPU1)
                    {
                        MRobj[IndexReihenfolge[MomentanerSpieler]] = MapEngine.getSpaceProps(IndexReihenfolge[MomentanerSpieler]);//space
                        if (cpudone && MRobj[IndexReihenfolge[MomentanerSpieler]].Type != 1)
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            ConfigEngineLogging.playerMoney(player[IndexReihenfolge[MomentanerSpieler]].getName(), player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                            std::this_thread::sleep_for(std::chrono::milliseconds(500));
                            HatGewuerfelt = false;
                            system("cls");
                            ConfigEngineLogging.newRound();
                            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                            MomentanerSpieler++;
                            cpudone = false;
                        }

                    }
                   
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::Verkaufen) {
                        int Strasse = -1,Gebaude = -1;
                        ControlEngine.AusgabeVerkaufen(option, Strasse,Gebaude, x / 2 - 215, y / 2 - 20, Farbe::BG_Rot);

                        //Logik wegen dem Verkaufen - Abfrage ob Gebaude und Strasse in Besitz zum Verkaufen 
                        system("cls");
                    }
                    if (option + MenueOptionen::Wuerfeln == MenueOptionen::RundeBeenden)
                    {
                        if (HatGewuerfelt)
                        {
                            ConfigEngineLogging.playerMoney(player[IndexReihenfolge[MomentanerSpieler]].getName(), player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                            HatGewuerfelt = false;
                            system("cls");
                            ConfigEngineLogging.newRound();
                            ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());
                            MomentanerSpieler++;
                            
                        }
                        else
                        {
						    std::cout << setw(ControlEngine.GetLaengstenStringMenueSpielOptionen()) << "Spieler " + to_string(IndexReihenfolge[MomentanerSpieler] + 1) + " hat noch nicht gewuerfelt!" << std::endl;
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
                            GameState GsTemp;
                            PlayerState PlTemp;
                            GsTemp.currentPlayerIndex = IndexReihenfolge[MomentanerSpieler];
                            for (size_t i = 0; i < AnzahlSpieler; i++)
                            {
                                PlTemp.budget = player[i].getBudget();
                                //PlTemp.builtObjects = player[i].GetGebObjVector();
                                //PlTemp.hasFreeJailCard = MapEngine.GetPrison(i);
                                PlTemp.inJail = player[i].imGefaengnis();
                                PlTemp.name = player[i].getName();
                                //PlTemp.ownedObjects = player[i].GetGekObjVector(); 
                                PlTemp.position = player[i].getPosition();
                                GsTemp.players.push_back(PlTemp);
                            }
                            for (size_t i = 0; i < AnzahlCpuGegner; i++)
                            {
                                PlTemp.budget = player[i].getBudget();                //TODO:CPU GEGNER
                                //PlTemp.builtObjects = player[i].GetGebObjVector;      //TODO:CPU GEGNER
                                //PlTemp.hasFreeJailCard = MapEngine.GetPrison(i);      //TODO:CPU GEGNER
                                PlTemp.inJail = player[i].imGefaengnis();             //TODO:CPU GEGNER
                                PlTemp.name = player[i].getName();                    //TODO:CPU GEGNER
                                //PlTemp.ownedObjects = player[i].GetGekObjVector();    //TODO:CPU GEGNER
                                PlTemp.position = player[i].getPosition();            //TODO:CPU GEGNER
                                GsTemp.players.push_back(PlTemp);                     //TODO:CPU GEGNER
                            }
                            GsTemp.roundCount=AnzahlRunden;
                            CursorPos = { short(x / 2 - ControlEngine.GetLaengstenStringMenueSpielOptionen() / 2), short(y / 2 + ControlEngine.GetAnzMenuepunkteSpielOptionen() + 1) };
                            ControlEngine.UpdateCursorPosition(CursorPos);
                            save_config("Config.txt",{});       //TODO: implementieren und auf Funktionalität testen
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
                            //AnzahlSpieler = GsTemp.AnzSpieler;   //int
                                //AnzahlCpuGegner = GsTemp.AnzCpuGegner; //int
                            for (int i = 0; i < 2; i++)
                            {
                                TPlayer temp(i, GsTemp.players[i].name, GsTemp.players[i].budget, GsTemp.players[i].position, GsTemp.players[i].inJail, GsTemp.players[i].inJail, GsTemp.players[i].ownedObjects, GsTemp.players[i].builtObjects);
                                player[i] = temp;
                            }
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
                        player[IndexReihenfolge[MomentanerSpieler]].Handeln(playerRefs, Strasse, Angebot, MapEngine);
                    }
                    else
                    {
                        //Code zum Ablehnen des Handels
                    }
                case Menues::BahnFahren:
                    //TODO:Position spieler wird beim Bahnhof nicht richtig aktualisiert
                    MenueAuswahl = Menues::Spieler;
                    UpdateSpielfeld = TRUE;
                    std::cout << player[IndexReihenfolge[MomentanerSpieler]].getPosition();

                    system("cls");

                    if (!option)
                    {
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(MomentanerSpieler, player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl(), 1));
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                    }
                    else {
                        player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl(), 0));
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

                    ConfigEngineLogging.playerOnStreet(MapEngine.getName(player[MomentanerSpieler].getPosition()));
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
        if (MomentanerSpieler >= AnzahlSpieler + AnzahlCpuGegner) {
            MomentanerSpieler = 0;
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
            ControlEngine.AusgabeJaNeinOption(option, x / 2 - 198, y / 2 - 9, Farbe::BG_Weiss,"Akzeptierst du den Handel Spieler wem die Strasse gehoert?");
            break;
        case Menues::BahnFahren:
            if (player[IndexReihenfolge[MomentanerSpieler]].getHuman()==CPU1)
            {

                if (player[IndexReihenfolge[MomentanerSpieler]].takebahn(player, MRobj[IndexReihenfolge[MomentanerSpieler]].Rent, player[IndexReihenfolge[MomentanerSpieler]].getPosition(), AnzahlSpieler + AnzahlCpuGegner, MapEngine))
                {
                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(MapEngine.movePlayer(IndexReihenfolge[MomentanerSpieler], player[IndexReihenfolge[MomentanerSpieler]].getAugenzahl(), 1));
                    player[IndexReihenfolge[MomentanerSpieler]].bezahle(MRobj[IndexReihenfolge[MomentanerSpieler]].Rent);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                ConfigEngineLogging.playerMoney(player[IndexReihenfolge[MomentanerSpieler]].getName(), player[IndexReihenfolge[MomentanerSpieler]].getBudget());
                MomentanerSpieler++;
                HatGewuerfelt = false;
                system("cls");
                ConfigEngineLogging.newRound();
                ConfigEngineLogging.newPlayer(player[IndexReihenfolge[MomentanerSpieler]].getName());

            }
            else {
                ControlEngine.AusgabeJaNeinOption(option, x / 2 - 198, y / 2 - 9, MomentanerSpielerFarbe, "Bahn fahren?"); // Bug
            }
            break;
        default:
            break;
        }

        if (UpdateSpielfeld)
        {
            //TestControl.AusgabeFeld(board.toStr(), x / 2 - 110, y / 2 - 44);
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
                //TestControl.AusgabeFeld(board.toStr(), x / 2 - 110, y / 2 - 44);
            }
            ControlEngine.AusgabeFeld(MapEngine.toStr(), x / 2 - 110, y / 2 - 44);
            std::vector<std::vector<std::string>> gekObjNamen;
            std::vector<std::vector<std::string>> gebObjNamen;
            std::vector<int> tempBudgets;
            std::vector<int> gekObjAnz;
            std::vector<int> gebObjAnz;               
            std::cout << MRobj[IndexReihenfolge[MomentanerSpieler]].Msg << "\n";
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

