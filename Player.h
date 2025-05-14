#pragma once

#include <iostream>;
#include <string>;
#include <vector>;
using namespace std;

class players
{
public:
	players();
	~players();
	float getBudget();
	void setBudget(float f);

	int getPosition();
	void setPosition(int p);

	int getAugenzahl();
	void setAugenzahl(int a);

	int wuerfeln();

	//Handeln

private:
	float Budget;
	int Position;
	int Augenzahl;
	vector<string> gekaufteStrasse; //vector<Strasse> vom Objekt Strasse vielleicht sinnvoller?
	vector<string> gebauteHaueser; //vector<Hotel> vom Objekt Hotel vielleicht sinnvoller?
};

players::players()
{
}

players::~players()
{
}
