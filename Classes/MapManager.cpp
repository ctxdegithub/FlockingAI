#include "MapManager.h"

MapManager* MapManager::s_instance = nullptr;

MapManager* MapManager::getInstance() {
	if (s_instance == nullptr) {
		s_instance = new MapManager;
		s_instance->init();
	}

	return s_instance;
}

void MapManager::init() {
	_mapArea.origin = Vec2(0.f, 0.f);
	_mapArea.size = Director::getInstance()->getVisibleSize();
//	_mapArea.size.width -= 100.f;
//	_mapArea.size.height -= 100.f;
}

bool MapManager::isInRange(const Vec2& pos) {
	return _mapArea.containsPoint(pos);
}

Vec2 MapManager::randPos() {
	return Vec2(CCRANDOM_0_1() * _mapArea.size.width + _mapArea.origin.x, CCRANDOM_0_1() * _mapArea.size.height + _mapArea.origin.y);
}

Vec2 MapManager::randPos(float disHor, float disVer) {
    return Vec2(disHor + CCRANDOM_0_1() * (_mapArea.size.width - disHor * 2),
         disVer + CCRANDOM_0_1() * (_mapArea.size.height - disVer * 2));
}
