#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MapManager.h"
#include "Bird.h"
#include "Obstacle.h"

using namespace cocostudio::timeline;

const int OBSTACLE_COUNT = 10;
const int BIRD_MAX_COUNT = 20;

// bird
const float WIDEVIEW_RADIUS = 200.f;
const float LIMITEDVIEW_RADIUS = 50.f;
const float NARROWVIEW_RADIUS = 50.f;
const float SEPARATION_FACTOR = 5.f;
const float STEERING_FORCE = 4.f;
const float BACK_VIEW_ANGLE_FACTOR = 0.5;
const float FRONT_VIEW_ANGLE_FACTOR = 1.0f;
const float MAX_SPEED = 200.f;
const float BIRD_LENGTH = 15.f;

const float COLLISION_FACTOR = 0.5f;

// obstacle
const float OBSTACLE_MIN_RADIUS = 10.f;
const float OBSTACLE_MAX_RADIUS = 20.f;

const float OBSTACLE_MIN_WARNINGRADIUS = 50.f;
const float OBSTACLE_MAX_WARNINGRADIUS = 80.f;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    //	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    srand(time(nullptr));
    _drawDebug = DrawNode::create();
    addChild(_drawDebug);
    initRes();
    initKey();
    initBirds();
    initObstacles();
    
    scheduleUpdate();
    return true;
}

void HelloWorld::initRes() {

}


void HelloWorld::initBirds() {
    _bWideView = _bLimitedView = _bNarrowView = false;
    _bWideView = true;
    
    _bird = Bird::create();
    addChild(_bird);
    _bird->setPosition(MapManager::getInstance()->randPos());
    _bird->setRotation(-90);
    _bird->getPhysicsBody()->setVelocity(Vec2(0, MAX_SPEED));
    
    float rot;
    Bird* bird;
    for (int i = 0; i < BIRD_MAX_COUNT; ++i) {
        rot = CCRANDOM_0_1() * 360;
        bird = Bird::create();
        bird->setID(i);
        bird->setViewType(ViewCheck::ViewType::VIEW_WIDE);
        bird->setViewRadius(WIDEVIEW_RADIUS);
        bird->setBackViewFactor(BACK_VIEW_ANGLE_FACTOR);
        bird->setFrontViewFactor(FRONT_VIEW_ANGLE_FACTOR);
        bird->setCloserRadius(BIRD_LENGTH * SEPARATION_FACTOR);
        addChild(bird);
        bird->setPosition(MapManager::getInstance()->randPos());
        bird->setRotation(-rot);
        rot = CC_DEGREES_TO_RADIANS(rot);
        bird->getPhysicsBody()->setVelocity(Vec2(cosf(rot), sinf(rot)) * MAX_SPEED);
        _birds.push_back(bird);
    }
    
}

void HelloWorld::initObstacles() {
    for (int i=0; i<OBSTACLE_COUNT; ++i) {
        auto obstacle = Obstacle::create();
        obstacle->setID(i);
        obstacle->setRadius(random(OBSTACLE_MIN_RADIUS, OBSTACLE_MAX_RADIUS));
        obstacle->setWarningRadius(random(OBSTACLE_MIN_WARNINGRADIUS, OBSTACLE_MAX_WARNINGRADIUS));
        obstacle->setPosition(MapManager::getInstance()->randPos(100, 80));
        addChild(obstacle);
        _obstacles.push_back(obstacle);
    }
}


void HelloWorld::initKey() {
    memset(_key, 0, sizeof(_key));
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    _key[(int)keyCode] = true;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    _key[(int)keyCode] = false;
}

void HelloWorld::update(float dt) {
    updateBirds(dt);
    updateObstacles(dt);
    
    // debug
    _drawDebug->clear();
    Vec2 posAve(0,0), velAve(0, 0);
    for (int i = 0; i < BIRD_MAX_COUNT; ++i) {
        posAve += _birds[i]->getPosition();
        velAve += _birds[i]->getPhysicsBody()->getVelocity();
    }
    posAve = posAve / BIRD_MAX_COUNT;
    velAve = velAve / BIRD_MAX_COUNT;
    velAve.normalize();
    _drawDebug->drawLine(posAve, posAve + velAve * 200, Color4F::GREEN);
}

void HelloWorld::doBirdAI(Bird* bird) {
    float angulorVel = 0.f;
    angulorVel = calcRotVelByBirds(bird) + calcRotVelByObstacles(bird);
    
    float rot = -CC_DEGREES_TO_RADIANS(bird->getRotation());
    bird->getPhysicsBody()->setAngularVelocity(-angulorVel);
    bird->getPhysicsBody()->setVelocity(Vec2(cosf(rot) * MAX_SPEED, sinf(rot) * MAX_SPEED));
}

float HelloWorld::calcRotVelByBirds(Bird *bird) {
    int j, viewRet, n = 0;
    Vec2 pAve(0,0), vAve(0,0);
    Vec2 d, u, v, w;
    float m = 0, angulorVel = 0;
    bool bDoFlock = _bWideView || _bNarrowView || _bLimitedView;
    for (j = 0; j < BIRD_MAX_COUNT; ++j) {
        if (_birds[j] != bird) {
            viewRet = bird->inView(_birds[j]);
            
            if (viewRet != -2) {
                d = bird->getPosition() - _birds[j]->getPosition();
                if (bird->isInRange(_birds[j])) {
                    pAve += _birds[j]->getPosition();
                    vAve += _birds[j]->getPhysicsBody()->getVelocity();
                    ++n;
                }
                
                if (bird->isCloser(_birds[j])) {
                    if (viewRet == -1) m = 1;
                    if (viewRet == 1) m = -1;
                    
                    angulorVel += m * STEERING_FORCE * BIRD_LENGTH * SEPARATION_FACTOR / d.length();
                }
            }
        }
    }
    if (bDoFlock && (n > 0)) {
        pAve = pAve / n;
        v = bird->getPhysicsBody()->getVelocity();
        v.normalize();
        u = pAve - bird->getPosition();
        u.normalize();
        w.x = u.cross(v);
        m = 0;
        if (w.x < 0) m = -1;
        if (w.x > 0) m = 1;
        if (fabsf(v.dot(u)) < 1.f) {
            angulorVel += m * STEERING_FORCE * acosf(v.dot(u)) / M_PI;
        }
        
        vAve = vAve / n;
        u = vAve;
        u.normalize();
        v = bird->getPhysicsBody()->getVelocity();
        v.normalize();
        w.x = u.cross(v);
        m = 0;
        if (w.x < 0) m = -1;
        if (w.x > 0) m = 1;
        if (fabsf(v.dot(u)) < 1) {
            angulorVel += m * STEERING_FORCE * 2 * acosf(v.dot(u)) / M_PI;
        }
    }
    
    return angulorVel;
}

float HelloWorld::calcRotVelByObstacles(Bird *bird) {
    float m = 0, angulorVel = 0;
    float radius;
    Vec2 a, v, p, b;
    v = bird->getPhysicsBody()->getVelocity();
    v.normalize();
    
    for (int i=0; i<OBSTACLE_COUNT; ++i) {
        a = _obstacles[i]->getPosition() - bird->getPosition();
        p =  v * a.dot(v);
        if (p.lengthSquared() < (v * bird->getViewRadius()).lengthSquared()) {
            radius = _obstacles[i]->getWarningRadius();
            b = p - a;
            if (b.lengthSquared() < radius * radius) {
                m = a.cross(v);
                if (m > 0) {
                    m = -1;
                } else if (m < 0) {
                    m = 1;
                }
                angulorVel += m * COLLISION_FACTOR * BIRD_LENGTH;
            }
        }
    }
    return angulorVel;
}

void HelloWorld::updateBirds(float dt) {
    float rotDelta = 0;
    
    if (_key[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW]) {
        rotDelta = -1;
    }
    if(_key[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW]) {
        rotDelta = 1;
    }
    float rot = -CC_DEGREES_TO_RADIANS(_bird->getRotation());
    _bird->getPhysicsBody()->setAngularVelocity(10 * rotDelta);
    _bird->getPhysicsBody()->setVelocity(Vec2(cosf(rot) * 200, sinf(rot) * 200));
    Bird* bird;
    Rect mapArea = MapManager::getInstance()->getMapArea();
    for (int i = 0; i < BIRD_MAX_COUNT; ++i) {
        bird = _birds[i];
        doBirdAI(bird);
        if (bird->getPositionX() > mapArea.getMaxX()) {
            bird->setPositionX(0);
        }
        if (bird->getPositionX() < 0) {
            bird->setPositionX(mapArea.getMaxX());
        }
        if (bird->getPositionY() > mapArea.getMaxY()) {
            bird->setPositionY(0);
        }
        if (bird->getPositionY() < 0) {
            bird->setPositionY(mapArea.getMaxY());
        }
        bird->update(dt);
    }
}

void HelloWorld::updateObstacles(float dt) {
    for (int i=0; i<OBSTACLE_COUNT; ++i) {
        _obstacles[i]->update(dt);
    }
}