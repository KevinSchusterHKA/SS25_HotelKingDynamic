#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

class player
{
private:
	float Budget = 1000.0;
	int Position = 0;
	int Augenzahl;
	vector<string> gekaufteStrasse; 
	vector<string> gebauteHaeuser; 

public:
	player();
	~player();
	float getBudget();
	void setBudget(float f);

	int getPosition();
	void setPosition(int p);

	int getAugenzahl();
	void setAugenzahl(int a);
	int wurfel();
	float handel(string request, int preowner);
};

player::player()
{
}

player::~player()
{
}

