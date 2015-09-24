#include "Bird.h"
#include "Defines.h"

const Color3B COLOR_LEADER = Color3B(255, 255, 0);
const Color3B COLOR_INTERCEPTOR = Color3B(0, 255, 255);
const Color3B COLOR_LEADER_INTERCEPTOR = Color3B(255, 0, 255);

Bird::Bird() :
_bLeader(false),
_bInterceptor(false)
{
    
}

bool Bird::init() {
	if (!Node::init()) {
		return false;
	}
	initUI();
	initPhysics();
	return true;
}

void Bird::initUI() {
#ifdef AI_DEBUG
    _label = Label::createWithSystemFont("", "Arail", 16);
    _label->setColor(Color3B::BLACK);
    _label->setPositionX(-10);
    addChild(_label, 10);
    _drawNode = DrawNode::create();
    addChild(_drawNode);
    
    _viewDraw = DrawNode::create();
    addChild(_viewDraw);

	_points.push_back(Vec2(-15, 6));
	_points.push_back(Vec2(0, 6));
	_points.push_back(Vec2(10, 0));
	_points.push_back(Vec2(0, -6));
	_points.push_back(Vec2(-15, -6));
#endif
    _bUpdateUI = true;
}

void Bird::initPhysics() {
	_body = PhysicsBody::createBox(Size(10, 6));
	_body->setGravityEnable(false);
	this->setPhysicsBody(_body);
}

void Bird::setID(int id) {
    _id = id;
    _bUpdateUI = true;
}

void Bird::setIsLeader(bool bLeader) {
    _bLeader = bLeader;
    _bUpdateUI = true;
}

void Bird::setIsInterceptor(bool bInterceptor) {
    _bInterceptor = bInterceptor;
    _bUpdateUI = true;
}


void Bird::setViewRadius(float radius) {
    _viewCheck.setViewRadius(radius);
    _bUpdateUI = true;
}

void Bird::setViewType(ViewCheck::ViewType type) {
    _viewCheck.setViewType(type);
    _bUpdateUI = true;
}

void Bird::setCloserRadius(float radius) {
    _viewCheck.setCloserRadius(radius);
    _bUpdateUI = true;
}

void Bird::setBackViewFactor(float factor) {
    if (factor < 0.f) {
        factor = 0.f;
    }
    _viewCheck.setBackViewFactor(factor);
    _bUpdateUI = true;
}

void Bird::setFrontViewFactor(float factor) {
    if (factor < 0.f) {
        factor = 0.f;
    }

    _viewCheck.setFrontViewFactor(factor);
    _bUpdateUI = true;
}

int Bird::inView(Bird *bird, bool ignoreRadius) {
    return _viewCheck.inView(getPosition(), getRotation(), bird->getPosition(), ignoreRadius);
}

int Bird::inView(Bird *bird, ViewCheck::ViewType type, bool ignoreRadius) {
    return _viewCheck.inView(type, getPosition(), getRotation(), bird->getPosition(), ignoreRadius);
}

bool Bird::isInRange(Bird *bird) {
    return _viewCheck.isInRange(getPosition(), bird->getPosition());
}

bool Bird::isCloser(Bird *bird) {
    return _viewCheck.isCloser(getPosition(), bird->getPosition());
}

void Bird::printInfo() {
    CCLOG("ID(%d): pos(%.2f,%.2f), velocity(%f,%f)", _id, getPositionX(), getPositionY(),
          _body->getVelocity().x, _body->getVelocity().y);
}

void Bird::update(float dt) {
#ifdef AI_DEBUG
    if (_bUpdateUI) {
        _bUpdateUI = false;
        // id
        _label->setString(StringUtils::format("%d", _id));
        
        // body
        Color4F clr = Color4F::WHITE;
        if (_bLeader && _bInterceptor) {
            clr = Color4F(COLOR_LEADER_INTERCEPTOR);
        } else if (_bLeader) {
            clr = Color4F(COLOR_LEADER);
        } else if (_bInterceptor) {
            clr = Color4F(COLOR_INTERCEPTOR);
        }
        _drawNode->drawPolygon(&_points[0], _points.size(), clr, 1, clr);
        _drawNode->drawLine(Vec2(0, 0), Vec2(20, 0), Color4F::RED);
        
        float startAngle, endAngle;
        // wide
        _viewCheck.calcViewAngleRange(ViewCheck::ViewType::VIEW_WIDE, startAngle, endAngle);
        float deltaAngle = (endAngle - startAngle) / 24.f;
        viewCirclePoints[0] = Vec2::ZERO;
        for (int i=0; i<24; ++i) {
            viewCirclePoints[i+1].x = cosf(startAngle + deltaAngle * i - M_PI_2) * _viewCheck.getViewRadius();
            viewCirclePoints[i+1].y = sinf(startAngle + deltaAngle * i - M_PI_2) * _viewCheck.getViewRadius();
        }
        _viewDraw->clear();
        _viewDraw->drawPoly(viewCirclePoints, 25, true, Color4F(0.f, 0.5f, 0.f, 0.5f));
        
        // narrow
        _viewCheck.calcViewAngleRange(ViewCheck::ViewType::VIEW_NARROW, startAngle, endAngle);
        deltaAngle = (endAngle - startAngle) / 24.f;
        viewCirclePoints[0] = Vec2::ZERO;
        for (int i=0; i<24; ++i) {
            viewCirclePoints[i+1].x = cosf(startAngle + deltaAngle * i - M_PI_2) * _viewCheck.getViewRadius();
            viewCirclePoints[i+1].y = sinf(startAngle + deltaAngle * i - M_PI_2) * _viewCheck.getViewRadius();
        }
        _viewDraw->drawPoly(viewCirclePoints, 25, true, Color4F(0.5f, 0.f, 0.f, 0.5f));
    }
#endif
    
//    if (_bLeader && _bInterceptor) {
//        _deathNode->setColor(COLOR_LEADER_INTERCEPTOR);
//    } else if (_bLeader) {
//        _deathNode->setColor(COLOR_LEADER);
//    } else if (_bInterceptor) {
//        _deathNode->setColor(COLOR_INTERCEPTOR);
//    } else {
//        _deathNode->setColor(Color3B::WHITE);
//    }
}