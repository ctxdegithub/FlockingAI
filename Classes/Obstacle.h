//
//  Obstacle.h
//  AIGether
//
//  Created by MAC on 15/9/23.
//
//

#ifndef __AIGether__Obstacle__
#define __AIGether__Obstacle__

#include "cocos2d.h"
USING_NS_CC;

class Obstacle : public Node
{
public:
    CREATE_FUNC(Obstacle);
    bool init();
    void setID(int id);
    void setRadius(float radius);
    void setWarningRadius(float radius);
    void update(float dt);
    
private:
    void initUI();
    
private:
    CC_SYNTHESIZE_READONLY(float, _warningRadius, WarningRadius);
    CC_SYNTHESIZE_READONLY(float, _radius, Radius);
    DrawNode* _drawNode;
    Label* _label;
    int _id;
    bool _bUpdateUI;
};

#endif /* defined(__AIGether__Obstacle__) */
