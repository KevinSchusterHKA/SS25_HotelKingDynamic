#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib> // rand()
#include "Map.h"
#include "SpaceConfig.h"



using namespace std;
enum PlayerType { HUMAN, CPU1, CPU2, }; // human player ,level 1,level 2
class TPlayer
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
	vector<int> GebauteHaeuserSpeicherFormat;



public:
	TPlayer();
	TPlayer(int id, int budget, int position);
	TPlayer(int id, string name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeser);
	TPlayer(int id, string name, int budget, int position, bool imgefaengnis, int gefaengnisrunden, vector<int> gekauftestrassen, vector<int> gebautehaeuserspeicher, vector<int> gebautehaeuser);
	~TPlayer();

	int Score(vector<TPlayer*>& spielerListe);
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

	void addStrasse(int strasse);
	void deleteStrasse(int strasse);
	void verkaufeStrasse(int strasse, vector<TPlayer*>& spielerListe);
	bool besitztStrasse(int strasse);
	bool istStrassenSetHandelbar(int feld, vector<TPlayer*>& spielerListe);
	int Handeln(vector<TPlayer*>& spielerListe, int feld, int angebot);

	void baueHaus(int strasse, Map& map);
	int baueHausTEMP(int strasse, vector<TPlayer*>& spielerListe);
	void verkaufeHaus(int strasse, int anz, vector<TPlayer*>& spielerListe);
	int anzahlHaeuserAuf(int strasse);
	int WieVieleHaueserAufSet(int feld);

	vector<string> getGekObjNamen();
	vector<string> getGebObjNamen();

	int getGekObjAnz();
	int getGebObjAnz();
	vector<int> getGekObjVector();
	vector<int> getGebObjVector();

	//cpu logic 
	int handelcpu(int cpuID, int totalPlayers, vector<TPlayer*>& spielerListe, int& targetPlayerOut, int& propertyIndexOut, Map& map);
	bool acceptTradecpu(int spaceIndex, int offer, int kaufer, vector<TPlayer*>& spielerListe, Map& map);
	bool tryBuyStreetcpu(Map& map);
	bool tryBuildHousecpu(vector<TPlayer*>& spielerListe, Map& map);
	bool takebahn(vector<TPlayer*>& spielerListe, int costofbahn, int bahnpos, int anzahlplayers, Map& map);
	void cpuHausOderStrassenVerkauf(vector<TPlayer*>& spielerListe, Map& map);
};


string LUT(int i);
//int getPreisStrasse(int feld, Map& map);
//int getPreisHaus(int feld, Map& map);

int colorcheck(int playerID, int space, std::vector<int>& ownedProperties);

int streetpricewith2(int position, vector<TPlayer*>& spielerListe);
int housepricewith2(int position, vector<TPlayer*>& spielerListe);
vector<int> SpeicherZuInternFormat(vector<int> gebauteHaueserSpeicher);
int WemGehoertStrasse(int feld, vector<TPlayer*>& spielerListe);
int check_bahn_pos(int pos);