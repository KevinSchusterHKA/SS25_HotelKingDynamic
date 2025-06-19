#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib> // rand()

using namespace std;
enum PlayerType { HUMAN, CPU1, CPU2, }; // human player ,level 1,level 2
class player
{
private:
	int ID;
	int Human; //"HUMAN" or "CPU1" or "CPU2"....
	string Name;
	int Budget = 1500;
	int Position = 0;
	vector<int> Wurfelzahl = { 0, 0 };
	int Augenzahl = 0;
	int PaschCounter = 0;
	bool ImGefaengnis = false;
	int GefaengnisRunden = 0;
	vector<int> GekaufteStrassen;
	vector<int> GebauteHaeuser;



public:
	player();
	player(int id, int budget, int position);
	player(int id, int name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeser);
	~player();

	int Score();
	void getData();
	void setID(int id);
	int getID();
	int getHuman();
	void setHuman(int h);
	string getName();
	void setName(string name);

	int getBudget();
	void setBudget(int b);

	int getPosition();
	void setPosition(int p);
	void incPosition(int p);

	// Würfeln und Pasch
	int getWurfel(int index);
	void setWurfel(int w, int index);
	int wurfeln();
	bool paschcheck();
	void Wurfelmechn();
	void Paschwurf();
	int getAugenzahl();
	void setAugenzahl(int a);
	int getPaschCounter();
	void setPaschCounter(int p);
	void incPaschCounter();

	// Gefängnis
	void insGefaengnis();
	void decGefaengnisRunden();
	bool imGefaengnis();

	void bezahle(int betrag);
	void erhalte(int betrag);
	bool istPleite();
	void geheZu(int feld);

	void addStrasse(int strasse);
	void deleteStrasse(int strasse);
	bool besitztStrasse(int strasse);
	int handel(int request, int preowner);
	bool kaufeStrasseVon(player* von, int strasse, int betrag);
	bool verkaufeStrasseAn(player* zielspieler, int strasse, int betrag);

	void baueHaus(int strasse);
	void verkaufeHaus(int strasse);
	int anzahlHaeuserAuf(int strasse);

	vector<string> getGekObjNamen();
	vector<string> getGebObjNamen();

	int getGekObjAnz();
	int getGebObjAnz();
	vector<int> getGekaufteStrassen();
	vector<int> getGebauteHaeuser();
};


string LUT(int i);
int getPreisStrasse(int i);

class cpu_player1 : public player {
public:
	cpu_player1();

	int handel(int cpuID, int totalPlayers, std::vector<player*>& p, int& targetPlayerOut, int& propertyIndexOut);
	bool acceptTrade(int spaceIndex, int offer);
	bool tryBuyStreet(std::vector<player*>& p);
};
