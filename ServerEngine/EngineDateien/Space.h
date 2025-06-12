#pragma once
#include <string>
#include "LookUp.h"
#include "SpaceConfig.h"
#include "MapReturnObj.h"

using namespace std;

class Space
{
private:
	string Design[_dimY][_dimX + 2] = {};
	const int *DesignBuffer;
	int Owner = -1;
	int Houses = -1;
	int Players[4] = { 0 };
	SpaceConfig Config;

	void SetBuffer(int type)
	{
		switch (type)
		{
		case TypeStreet:
			DesignBuffer = *_designStreet;
			setup();
			insertStr(intToStr(Config.Price), 1);
			break;

		case TypeStation:
			DesignBuffer = *_designStation;
			setup();
			insertStr(intToStr(Config.Rentarr[0]), 1);
			break;

		case TypeTax:
			DesignBuffer = *_designTax;
			setup();
			insertStr(intToStr(Config.Rentarr[0]), 1);
			break;

		case TypeChance:
			DesignBuffer = *_designChance;
			setup();
			break;

		case TypeChest:
			DesignBuffer = *_designChest;
			setup();
			break;

		case TypeGo:
			DesignBuffer = *_designGo;
			setup();
			insertStr(intToStr(Config.Rentarr[0]), 1);
			break;

		case TypePrison:
			DesignBuffer = *_designPrison;
			setup();
			insertStr("Zu Besuch", 1);
			break;

		case TypePark:
			DesignBuffer = *_designPark;
			setup();
			insertStr(intToStr(Config.Rentarr[0]), 1);
			break;

		case TypeGTP:
			DesignBuffer = *_designGTP;
			setup();
			break;

		default:
			throw new exception;
			break;
		}
		return;
	}

	void insertStr(string in, int line)
	{
		int pad = (_dimX - 4 - in.size()) / 2;
		for (int i = 0; i < _dimX - 5; i++)
		{
			Design[line][3 + i] = " ";
		}
		for (int i = 0; i < in.size() && i < _dimX - 5; i++)
		{
			Design[line][3 + i + pad] = in.at(i);
		}
	}

	string intToStr(int in)
	{
		string out = " ";
		for (int i = 1; in / i || (in == 0 && i == 1); i *= 10)
		{
			out = (char)(48 + (in / i) % 10) + out;
		}
		out += _symbolchars[Coin];
		return out;
	}

	void setup()
	{
		for (int i = 0; i < _dimY; i++)
		{
			int offset = 0;
			for (int j = 0; j < _dimX + 2; j++)
			{
				if (j == 2 || j == _dimX - 1)
				{
					Design[i][j] = _bgcolortable[bgblack];
					offset++;
				}
				else
				{
					Design[i][j] = _symbolchars[DesignBuffer[i * _dimX + j - offset]];
				}
			}
		}
		Design[_dimY - 3][2] = _bgcolortable[Config.Color];
		Design[_dimY - 2][2] = _bgcolortable[Config.Color];
		int pos = 0;
		if ((pos = Config.Name.find('|')) != -1)
		{
			insertStr(Config.Name.substr(0, pos), _dimY - 3);
			insertStr(Config.Name.substr(++pos, Config.Name.size() - pos), _dimY - 2);
		}
		else {
			insertStr(Config.Name, _dimY - 3);
		}
	}

public:
	Space() {};

	Space(SpaceConfig config) {
		Config = config;
		SetBuffer(Config.Type);
	}

	string toStr(int line)
	{
		string out = "";
		if (line == 1 && Owner != -1)
		{
			string buffer = "";
			Design[1][2] = _bgcolortable[Owner + bgbrightred];
			switch (Houses)
			{
			case 4:
				buffer += " ";
				buffer += _symbolchars[House];
				buffer += " ";
			case 3:
				buffer += " ";
				buffer += _symbolchars[House];
				buffer += " ";
			case 2:
				buffer += " ";
				buffer += _symbolchars[House];
				buffer += " ";
			case 1:
				buffer += " ";
				buffer += _symbolchars[House];
				buffer += " ";
				break;
			case 5:
				buffer += _symbolchars[DAL];
				buffer += _symbolchars[House];
				buffer += _symbolchars[DAR];
				break;

			default:
				buffer = " ";
				break;
			}
			insertStr(buffer, 1);
		}
		if (line == 3)
		{
			Design[3][6] = (Players[0] == 1) ? _playerchars[0] : _playerchars[4];
			Design[3][9] = (Players[1] == 1) ? _playerchars[1] : _playerchars[4];
			Design[3][12] = (Players[2] == 1) ? _playerchars[2] : _playerchars[4];
			Design[3][15] = (Players[3] == 1) ? _playerchars[3] : _playerchars[4];
		}
		if (line == 6 && Config.Type == TypePrison)
		{
			Design[6][6] = (Players[0] == 2) ? _playerchars[0] : _playerchars[4];
			Design[6][9] = (Players[1] == 2) ? _playerchars[1] : _playerchars[4];
			Design[6][12] = (Players[2] == 2) ? _playerchars[2] : _playerchars[4];
			Design[6][15] = (Players[3] == 2) ? _playerchars[3] : _playerchars[4];
		}
		for (int i = 0; i < _dimX + 2; i++)
		{
			out += Design[line][i];
		}
		return out;
	}

	MapReturnObj getProps(int player)
	{
		MapReturnObj out(-1,Config.Type,Owner,Config.Rentarr[Houses + 1],0,"");
		switch (Config.Type)
		{
		case TypeStreet:
			if (Owner == -1 || player == Owner)
			{
				out.Rent = 0;
			}
			break;
		case TypeStation:

			break;
		case TypeTax:

			break;
		case TypeChance:
			out = _chanceCards[(int)(rand()%14)];
			break;
		case TypeChest:
			out = _chestCards[(int)(rand() %16)];
			break;
		case TypeGo:
			out.Rent = -200;
			break;
		case TypePrison:

			break;
		case TypePark:
			Config.Rentarr[0] = 0;
			insertStr(intToStr(Config.Rentarr[0]), 1);
			break;
		case TypeGTP:
			out.SpaceNr = 10;
			out.Prison = -1;
			out.flag = 1;
			break;
		default:
			break;
		}
		return out;
	}

	void setPlayer(int player)
	{
		Players[player] = 1;
	}

	void prisonPlayer(int player)
	{
		if (Config.Type == TypePrison)
		{
			Players[player] = 2;
		}
		else {
			Players[player] = 1;
		}
	}

	void removePlayer(int player)
	{
		Players[player] = 0;
	}

	int getPrice()
	{
		if (Config.Type == TypeStreet && Owner == -1)
		{
			return Config.Price;
		}
		return -1;
	}

	void buyStreet(int player)
	{
		Owner = player;
	}

	int getHousePrice(int player)
	{
		if (Houses == 5 || Houses == -1 || Owner != player)
		{
			return -1;
		}
		return Config.HousePrice;
	}

	void buyHouse()
	{
		Houses++;
	}

	void sellHouse()
	{
		Houses--;
	}

	int HouseCount(int player)
	{
		int out = 0;
		if (player != Owner)
		{
			return out;
		}
		if (Houses > 0 && Houses < 5)
		{
			out = Houses;
		}
		else if (Houses == 5)
		{
			out = 3;
		}
		return out;
	}

	void setPrice(float mult)
	{
		if (Config.Type == TypeStreet && Owner == -1)
		{
			Config.Price *= mult;
			insertStr(intToStr(Config.Price), 1);
		}
	}

	void addTax(int tax)
	{
		if (Config.Type == TypePark)
		{
			Config.Rentarr[0] += tax;
			insertStr(intToStr(Config.Rentarr[0]), 1);
		}
	}

	int getOwner()
	{
		return Owner;
	}

	void setOwner(int newowner)
	{
		Owner = newowner;
	}
};