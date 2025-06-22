#include "EngineDateien/TControl.h"
#include "EngineDateien/Config.h"
#include "EngineDateien/Logger.h"
#include "EngineDateien/LookUp.h"
#include "EngineDateien/Map.h"
#include "EngineDateien/MapReturnObj.h"
#include "EngineDateien/Player.h"
#include "EngineDateien/Space.h"
#include "EngineDateien/SpaceConfig.h"
class TServer
{
public:
	TServer();
	~TServer();
	void UnitTest();
	int GetLongestStringVector(std::vector<std::string> s) {
		int temp = 0;
		for (std::string var : s) {
			if (var.size() > temp)
			{
				temp = var.size();
			}
		}
		return temp;
	}
	void clearInputBuffer() {
		while (_kbhit()) {
			_getch(); // Discard characters in the buffer
		}
	}
private:
	TControl ControlEngine;
	cpu_player1 cpu[2]; 
	TPlayer player[4];
	Logger ConfigEngineLogging;
	Map MapEngine;

};

