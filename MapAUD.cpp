#include <iostream>
#include <string>
#include <map>
#include "Map.h"

using namespace std;

int main()
{
    string out = "";
    for (int i = 0; i < 16; i++)
    {
        out += _symbolchars[i];
    }
    std::cout << out.c_str() << "\n\n";
    Map board = Map(4);
    int player = 0;
    int distance = 0;
    while (1)
    {
        cout << board.toStr().c_str();
        while (board.getPlayerProps(player, 0, 0).flag)
        {
            cout << board.toStr().c_str();
        }
        cout << board.getPlayerProps(player, 0, 0).Rent << "\n";
        cin >> player;
        cin >> distance;
        cout << board.clear();
        if (distance == -1)
        {
            board.buyStreet(player, 1000);
        }
        else if (distance == -2)
        {
            board.buyHouses(player, 1000);
        }
        else
        {
            board.movePlayer(player, distance, 0);
        }
    }
    return -1;
}