#ifndef __MapManager_h__
#define __MapManager_h__

#include "cocos2d.h"
USING_NS_CC;

class MapManager
{
public:
	static MapManager* getInstance();
	bool isInRange(const Vec2& pos);
	Vec2 randPos();
    Vec2 randPos(float disHor, float disVer);
	Rect getMapArea() { return _mapArea; }
	Size getMapSize() { return _mapArea.size; }

private:
	void init();

private:
	static MapManager* s_instance;
	Rect _mapArea;
	Size _mapSize;
};

#endif