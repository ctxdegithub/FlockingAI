//
//  ViewCheck.h
//  AIGether
//
//  Created by MAC on 15/9/23.
//
//

#ifndef __AIGether__ViewCheck__
#define __AIGether__ViewCheck__

#include "cocos2d.h"
USING_NS_CC;

class ViewCheck
{
public:
    enum class ViewType {
        VIEW_WIDE,
        VIEW_LIMITED,
        VIEW_NARROW,
    };
    struct ViewInfo {
        ViewType type;
        float viewRadius;
    };
public:
    int inView(const Vec2& curPos, float dir, const Vec2& targetPos, bool ignoreRadius = false);
    int inView(ViewType type, const Vec2& curPos, float dir, const Vec2& targetPos, bool ignoreRadius = false);
    bool isInRange(const Vec2& curPos, const Vec2& targetPos);
    bool isCloser(const Vec2& curPos, const Vec2& targetPos);
    void calcViewAngleRange(float& startAngle, float& endAngle);
    void calcViewAngleRange(ViewType type, float& startAngle, float& endAngle);
    
private:
    CC_SYNTHESIZE(float, _closerRadius, CloserRadius);
    CC_SYNTHESIZE(float, _viewRadius, ViewRadius);
    CC_SYNTHESIZE(ViewType, _viewType, ViewType);
    CC_SYNTHESIZE(float, _backViewFactor, BackViewFactor);
    CC_SYNTHESIZE(float, _frontViewFactor, FrontViewFactor);
    
};

#endif /* defined(__AIGether__ViewCheck__) */
