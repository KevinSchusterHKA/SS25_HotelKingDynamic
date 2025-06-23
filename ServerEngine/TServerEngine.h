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
	int GetLongestStringVector(std::vector<std::string> s);
private:
	TControl ControlEngine;
	TPlayer player[4];
	Logger ConfigEngineLogging;
	Map MapEngine;

};

