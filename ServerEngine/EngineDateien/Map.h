#pragma once
#include <string>
#include <vector>
#include "LookUp.h"
#include "Space.h"
#include "MapReturnObj.h"

using namespace std;

class Map
{
private:
	Space Spaces[40];
	string Buffer;
	int Playerpos[4] = { 0 };
	int PlayerPrison[4] = { 0 };
	int RemainingSpaces = 22;

public:
	int getStreetPrice(int player) {
		return Spaces[Playerpos[player]].getPrice();
	}
	int getPropertyPrice(int spaceIndex) {
		if (spaceIndex < 0 || spaceIndex >= 40) {
			return -1;
		}
		return Spaces[spaceIndex].getPrice();
	}
	std::vector<int> getOwnedProperties(int playerID) {
		std::vector<int> owned;
		for (int i = 0; i < 40; i++) {
			if (Spaces[i].getOwner() == playerID) {
				owned.push_back(i);
			}
		}
		return owned;
	}


	Map() {
		for (int i = 0; i < 40; i++)
		{
			Spaces[i] = Space(_boardarr[i]);
		}
		for (int i = 0; i < 9 * _dimX; i++)
		{
			Buffer += " ";
		}
	};

	void SetPlayerNumber(int playernumber)
	{
		for (int i = 0; i < playernumber; i++)
		{
			Spaces[0].setPlayer(i);
		}
	}

	string toStr()
	{
		string out = _fgcolortable[4];
		for (int i = 0; i < _dimY; i++)
		{
			for (int j = 20; j < 31; j++)
			{
				out += Spaces[j].toStr(i);
			}
			out += "\n";
		}
		for (int i = 19; i > 10; i--)
		{
			for (int j = 0; j < _dimY; j++)
			{
				out += Spaces[i].toStr(j) + Buffer + Spaces[50 - i].toStr(j);
				out += "\n";
			}

		}
		for (int i = 0; i < _dimY; i++)
		{
			for (int j = 10; j >= 0; j--)
			{
				out += Spaces[j].toStr(i);

			}
			out += "\n";
		}
		out += "\033[0m";
		return out;
	}

	int movePlayer(int player, int distance, int flag)
	{
		Spaces[Playerpos[player]].removePlayer(player);
		vector<int> pos;
		for (int i = 0; i < 40; i++)
		{
			int j = (i + Playerpos[player]) % 40;
			if (_moveMatrix[Playerpos[player]][j] == distance)
			{
				pos.push_back(j);
			}
		}
		int	out = flag % pos.size();
		return setPlayer(player, pos.at(out), flag);
	}

	int setPlayer(int player, int space, int flag)
	{
		Spaces[Playerpos[player]].removePlayer(player);
		int out = (Playerpos[player] > space && flag == 0) ? -200 : 0;
		Playerpos[player] = space;
		if (flag == -1)
		{
			Spaces[Playerpos[player]].prisonPlayer(player);
		}
		else {
			Spaces[Playerpos[player]].setPlayer(player);
		}
		return out;
	}

	void freePlayer(int player)
	{
		if (Playerpos[player] == 10)
		{
			Spaces[Playerpos[player]].setPlayer(player);
		}
	}

	int buyStreet(int player, int funds)
	{
		int out = Spaces[Playerpos[player]].getPrice();
		if (out != -1 && out < funds)
		{
			Spaces[Playerpos[player]].buyStreet(player);
			RemainingSpaces--;
			for (int i = 0; i < 40; i++)
			{
				Spaces[i].setPrice(_factor);
			}
			int streetcolor = ownsStreets(player, Playerpos[player]);
			if (streetcolor != -1)
			{
				Spaces[_streetarr[streetcolor][0]].buyHouse();
				Spaces[_streetarr[streetcolor][1]].buyHouse();
				if (_streetarr[streetcolor][2] != -1)
				{
					Spaces[_streetarr[streetcolor][2]].buyHouse();
				}
			}
			return out;
		}
		return -1;
	}

	int setOwner(int oldowner, int newowner, int space)
	{
		if (space < 0 || space > 39)
		{
			return -1;
		}
		int streetcolor = ownsStreets(oldowner, space);
		if (streetcolor != -1)
		{
			Spaces[_streetarr[streetcolor][0]].sellHouse();
			Spaces[_streetarr[streetcolor][1]].sellHouse();
			if (_streetarr[streetcolor][2] != -1)
			{
				Spaces[_streetarr[streetcolor][2]].sellHouse();
			}
		}
		if (Spaces[space].getOwner() == oldowner)
		{
			Spaces[space].setOwner(newowner);
			return 1;
		}
		return -1;
	}

	int ownsStreets(int player, int space)
	{
		int color = 0;
		for (bool contains = false; color < 8 && !contains; color++)
		{
			contains |= (_streetarr[color][0] == space);
			contains |= (_streetarr[color][1] == space);
			contains |= (_streetarr[color][2] == space);
		}
		color--;
		bool colorOwned = true;
		for (int i = 0; i < 3; i++)
		{
			int pos = _streetarr[color][i];
			colorOwned &= (player == Spaces[(pos != -1) ? pos : _streetarr[color][0]].getOwner());
		}
		if (colorOwned)
		{
			return color;
		}
		return -1;
	}

	int buyHouses(int player, int space, int funds)
	{
		if (space < 0 || space > 39)
		{
			return -1;
		}
		int out = Spaces[space].getHousePrice(player);
		if (out != -1 && out < funds)//&&RemainingSpaces==0 // Bug
		{
			Spaces[space].buyHouse();
			return out;
		}
		return -1;
	}

	MapReturnObj getSpaceProps(int player)
	{
		MapReturnObj out(Spaces[Playerpos[player]].getProps(player));
		if (out.SpaceNr == -1)
		{
			out.SpaceNr = Playerpos[player];
		}
		else {
			out.Rent += setPlayer(player,out.SpaceNr, out.Prison);
			out.flag = 1;
		}
		if (out.Type == TypeTax)
		{
			Spaces[20].addTax(out.Rent);
		}
		if (out.Owner == -3)
		{
			int j = out.Rent;
			out.Rent = 0;
			for (int i = 0; i < 40; i++)
			{
				out.Rent += j * Spaces[i].HouseCount(player);
			}
		}
		return out;
	}

	string clear() {
		// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
		return "\x1B[2J\x1B[H";
	}
};


