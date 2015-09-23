#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Bird;
class Obstacle;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
	void update(float dt);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

private:
    void initRes();
	void initKey();
	void initBirds();
    void initObstacles();

	void doBirdAI(Bird* bird);
    void updateBirds(float dt);
    void updateObstacles(float dt);
    
    float calcRotVelByBirds(Bird* bird);
    float calcRotVelByObstacles(Bird* bird);
    
private:
    DrawNode* _drawDebug;
	Bird *_bird;
	std::vector<Bird*> _birds;
    std::vector<Obstacle*> _obstacles;
	bool _bWideView, _bLimitedView, _bNarrowView;
	bool _key[256];
	std::map<EventKeyboard::KeyCode, bool> _keyMap;
    std::vector<int> _birdsIndex;
};

#endif // __HELLOWORLD_SCENE_H__
