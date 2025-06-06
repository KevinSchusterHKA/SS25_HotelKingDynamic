#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

class player
{
private:
	int ID;
	bool Human; // "CPU" or "HUMAN"	
	int Budget	 = 1500;
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
	player(int budget, int position);
	~player();

	void setID(int id);
	int getID();
	bool getHuman();
	void setHuman(bool h);

	int getBudget();
	void setBudget(int b);

	int getPosition();
	void setPosition(int p);

	int getWurfel(int index);
	void setWurfel(int w, int index);
	void Wurfelmechn();
	void Paschwurf();

	int getAugenzahl();
	void setAugenzahl(int a);

	int getPaschCounter();
	void setPaschCounter(int p);
	void incPaschCounter();

	void insGefaengnis();

	int wurfeln();
	bool paschcheck();
	int handel(string request, int preowner);
};

