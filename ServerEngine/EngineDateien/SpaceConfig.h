#pragma once
#include <string>

using namespace std;

class SpaceConfig
{
public:
	string Name;
	int Type = 0;
	int Price = -1;
	int HousePrice = -1;
	int Rentarr[7] = { -1 };
	int Color = 0;

	SpaceConfig() {};

	SpaceConfig(string name, int type, int price, int houseprice, int rentarr[7], int color)
	{
		Name = name;
		Type = type;
		Price = price;
		HousePrice = houseprice;
		for (int i = 0; i < 6; i++)
		{
		Rentarr[i + 1] = rentarr[i];
		}
		Rentarr[0] = rentarr[0];
		Rentarr[1] = rentarr[0] * 2;
		Color = color;
	};

	SpaceConfig(string name, int type, int rent, int color)
	{
		Name = name;
		Type = type;
		for (int i = 0; i < 7; i++)
		{
			Rentarr[i] = rent;
		}
		Color = color;
	};

	SpaceConfig(string name, int type, int color)
	{
		Name = name;
		Type = type;
		Color = color;
	};
};

