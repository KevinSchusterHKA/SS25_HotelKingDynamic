#pragma once
#include <string>

using namespace std;

class MapReturnObj
{
public:
	int SpaceNr;
	int Owner;
	int Rent;
	int Prison;
	string Msg;
	int flag = 0;

	MapReturnObj(int spaceNr, int owner, int rent, int prison, string msg)
	{
		SpaceNr = spaceNr;
		Owner = owner;
		Rent = rent;
		Prison = prison;
		Msg = msg;
	}
};

