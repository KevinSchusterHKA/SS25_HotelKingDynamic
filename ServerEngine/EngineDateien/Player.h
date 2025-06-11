#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;
enum PlayerType {HUMAN,  CPU1,  CPU2,  }; // human player ,level 1,level 2
class player
{
private:
	int ID;
	int Human; //"HUMAN" or "CPU1" or "CPU2"....
	int Budget	 = 0;
	int Position = 0;
	vector<int> Wurfelzahl	= { 0, 0 };
	int Augenzahl			= 0;
	int PaschCounter		= 0;
	bool ImGefaengnis	 = false;
	int GefaengnisRunden = 0;
	vector<string> GekaufteStrassen; 
	vector<string> GebauteHaeuser;



public:
	player();
	player(int id, int budget, int position);
	~player();

	void getData();
	void setID(int id);
	int getID();
	int getHuman();
	void setHuman(int h);

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

	void addStrasse(string strasse);
	void deleteStrasse(string strasse);
	bool besitztStrasse(string strasse);
	int handel(string request, int preowner);
	bool verkaufeStrasseAn(player* zielspieler, string strasse, int betrag);

	void baueHaus(string strasse);
	void verkaufeHaus(string strasse);
	int anzahlHaeuser(string strasse);
};

