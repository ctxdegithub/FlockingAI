#ifndef __Bird_h__
#define __Bird_h__

#include "ViewCheck.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocostudio::timeline;

class Bird : public Node
{
public:
	CREATE_FUNC(Bird);
    Bird();
	bool init();
	void setID(int id);
    
    float getViewRadius() { return _viewCheck.getViewRadius(); }
    void setViewRadius(float radius);
    void setCloserRadius(float radius);
    void setViewType(ViewCheck::ViewType type);
    void setBackViewFactor(float factor);
    void setFrontViewFactor(float factor);
    
    bool isLeader() { return _bLeader; }
    bool isInterceptor() { return _bInterceptor; }
    void setIsLeader(bool bLeader);
    void setIsInterceptor(bool bInterceptor);
    
    int inView(Bird* bird, bool ignoreRadius = true);
    int inView(Bird *bird, ViewCheck::ViewType type, bool ignoreRadius = true);
    bool isInRange(Bird* bird);
    bool isCloser(Bird* bird);
    
    void printInfo();
    void update(float dt);
    
private:
	void initUI();
	void initPhysics();

private:
    bool _bUpdateUI;
    Vec2 viewCirclePoints[25];
    DrawNode* _drawNode;
    DrawNode* _viewDraw;
	Label* _label;
    
    
private:
    int _id;
    bool _bInterceptor;
    bool _bLeader;
    ViewCheck _viewCheck;
    std::vector<Vec2> _points;
    PhysicsBody* _body;
    Node* _deathNode;
    ActionTimeline* _animate;
    
};

#endif
