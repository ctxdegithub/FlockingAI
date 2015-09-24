//
//  Obstacle.cpp
//  AIGether
//
//  Created by MAC on 15/9/23.
//
//

#ifndef DEBUG_OBSTACLE
    #define DEBUG_OBSTACLE
#endif

#include "Obstacle.h"

bool Obstacle::init() {
    if (!Node::init()) {
        return false;
    }
    
    _radius = 1.f;
    _warningRadius = 4.f;
    _bUpdateUI = true;
    
    initUI();
    
    return true;
}

void Obstacle::initUI() {
    _drawNode = DrawNode::create();
    addChild(_drawNode);
#ifdef DEBUG_OBSTACLE
    _label = Label::createWithSystemFont("", "Arail", 20);
    _label->setColor(Color3B::BLACK);
    addChild(_label);
#endif
}

void Obstacle::setID(int id) {
    _id = id;
    _bUpdateUI = true;
}

void Obstacle::setRadius(float radius) {
    _radius = radius;
    _bUpdateUI = true;
}

void Obstacle::setWarningRadius(float radius) {
    _warningRadius = radius;
    _bUpdateUI = true;
}

void Obstacle::update(float dt) {

    if (_bUpdateUI) {
        _bUpdateUI = false;
        _drawNode->clear();
        _drawNode->drawDot(Vec2::ZERO, _radius, Color4F::YELLOW);

#ifdef DEBUG_OBSTACLE
        _label->setString(StringUtils::format("%d", _id));
        _drawNode->drawCircle(Vec2::ZERO, _warningRadius, 0, 24, false, Color4F(0.5f, 0.f, 0.f, 0.5f));
#endif

    }
}