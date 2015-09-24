//
//  ViewCheck.cpp
//  AIGether
//
//  Created by MAC on 15/9/23.
//
//

#include "ViewCheck.h"

int ViewCheck::inView(const Vec2& curPos, float dir, const Vec2& targetPos, bool ignoreRadius) {
    return inView(_viewType, curPos, dir, targetPos, ignoreRadius);
}

int ViewCheck::inView(ViewType type, const Vec2& curPos, float dir, const Vec2& targetPos, bool ignoreRadius) {
    bool inView = false;
    auto d = targetPos - curPos;
    if (!ignoreRadius) {
        if (!isInRange(curPos, targetPos)) {
            return false;
        }
    }
    auto w = d.rotateByAngle(Vec2::ZERO, CC_DEGREES_TO_RADIANS(dir + 90));
    
    switch (type) {
        case ViewType::VIEW_WIDE:
            inView = (w.y > 0) || ((w.y < 0) && fabsf(w.x) > fabsf(w.y) * _backViewFactor);
            break;
        case ViewType::VIEW_LIMITED:
            inView = w.y > 0;
            break;
        case ViewType::VIEW_NARROW:
            inView = (w.y > 0) && (fabsf(w.x) < fabsf(w.y) * _frontViewFactor);
            break;
        default:
            break;
    }
    int ret = -2;
    if (inView) {
        ret = (int)(w.x / fabsf(w.x));
    }
    return ret;
}

bool ViewCheck::isInRange(const Vec2& curPos, const Vec2& targetPos) {
    return ((targetPos - curPos).lengthSquared() <= _viewRadius * _viewRadius);
}
    
bool ViewCheck::isCloser(const Vec2& curPos, const Vec2& targetPos) {
    return ((targetPos - curPos).lengthSquared() <= _closerRadius * _closerRadius);
}

void ViewCheck::calcViewAngleRange(float& startAngle, float& endAngle) {
    calcViewAngleRange(_viewType, startAngle, endAngle);
}

void ViewCheck::calcViewAngleRange(ViewType type, float& startAngle, float& endAngle) {
    if (type == ViewCheck::ViewType::VIEW_WIDE) {
        auto v = Vec2(_backViewFactor, 1.f);
        float angle = v.getAngle();
        
        startAngle = -angle;
        endAngle = M_PI + angle;
    } else if (type == ViewCheck::ViewType::VIEW_NARROW) {
        auto v = Vec2(_frontViewFactor, 1.f);
        float angle = v.getAngle();
        
        startAngle = angle;
        endAngle = M_PI - angle;
    }
}