#include "EngineDateien/TControl.h"
#include "EngineDateien/Config.h"
#include "EngineDateien/CPU_opponent.h"
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
private:
	TControl control;
	cpu_player1 cpu[2];
	player player[4];
	Logger logger;
	Map board = Map(4);

};

