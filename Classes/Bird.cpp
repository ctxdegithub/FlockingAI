#include "Bird.h"

#ifndef DEBUG_BIRD
//    #define DEBUG_BIRD
#endif

bool Bird::init() {
	if (!Node::init()) {
		return false;
	}
    initAnimation();
	initUI();
	initPhysics();
	return true;
}

void Bird::initAnimation() {
    _deathNode = CSLoader::createNode("death.csb");
    addChild(_deathNode);
    _animate = CSLoader::createTimeline("death.csb");
    _deathNode->runAction(_animate);
    _animate->play("walk", true);
    _deathNode->setScale(0.3f);
}

void Bird::initUI() {
#ifdef DEBUG_BIRD
    _label = Label::createWithSystemFont("", "Arail", 14);
    addChild(_label, 10);
    _drawNode = DrawNode::create();
    addChild(_drawNode);
    
    _viewDraw = DrawNode::create();
    addChild(_viewDraw);

	_points.push_back(Vec2(-8, 3));
	_points.push_back(Vec2(0, 3));
	_points.push_back(Vec2(2, 0));
	_points.push_back(Vec2(0, -3));
	_points.push_back(Vec2(-8, -3));

	_drawNode->drawPoly(&_points[0], _points.size(), true, Color4F::BLUE);
	_drawNode->drawLine(Vec2(0, 0), Vec2(20, 0), Color4F::RED);

    _bUpdateUI = true;
#endif

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
#ifdef DEBUG_BIRD
    if (_bUpdateUI) {
        _bUpdateUI = false;
        // id
        _label->setString(StringUtils::format("%d", _id));
        
        float startAngle, endAngle;
        _viewCheck.calcViewAngleRange(startAngle, endAngle);
        float deltaAngle = (endAngle - startAngle) / 24.f;
        viewCirclePoints[0] = Vec2::ZERO;
        for (int i=0; i<24; ++i) {
            viewCirclePoints[i+1].x = cosf(startAngle + deltaAngle * i - M_PI_2) * _viewCheck.getViewRadius();
            viewCirclePoints[i+1].y = sinf(startAngle + deltaAngle * i - M_PI_2) * _viewCheck.getViewRadius();
        }
        _viewDraw->clear();
        _viewDraw->drawPoly(viewCirclePoints, 25, true, Color4F(0.f, 0.5f, 0.f, 0.5f));
    }
#endif
}