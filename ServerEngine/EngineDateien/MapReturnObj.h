#pragma once
#include <string>

using namespace std;

class MapReturnObj
{
public:
	int SpaceNr;
	int Type;
	int Owner;
	int Rent;
	int Prison;
	string Msg;
	int flag = 0;

	MapReturnObj()
	{
		SpaceNr = 0;
		Type = 0;
		Owner = 0;
		Rent = 0;
		Prison = 0;
		Msg = "";
	}

	MapReturnObj(int spaceNr, int type, int owner, int rent, int prison, string msg)
	{
		SpaceNr = spaceNr;
		Type = type;
		Owner = owner;
		Rent = rent;
		Prison = prison;
		Msg = msg;
	}
};

