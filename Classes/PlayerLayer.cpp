
#include "BreakoutCocos.h"

using namespace cocos2d;

PlayerLayer::PlayerLayer(GameInstance* game) {
    _game = game;
    setTouchEnabled(true);
    
    _paddle = new Paddle(_game);
    _game->addToGame(_paddle);
    _paddle->addToWorld();
    
    _winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    _paddleSprite = CCSprite::create("paddle.png");
    _paddleSprite->setPosition(Convert::PhysicalPositionToPixelPoint(_winSize, _paddle->getPosition()));
    addChild(_paddleSprite);
    
    _ball = new Ball(_game);
    _game->addToGame(_ball);
    _ball->addToWorld();
    
    _ballSprite = CCSprite::create("ball.png");
    _ballSprite->setPosition(Convert::PhysicalPositionToPixelPoint(_winSize, _ball->getPosition()));
    addChild(_ballSprite);
}

PlayerLayer::~PlayerLayer() {
    
}

void PlayerLayer::draw() {
    _ballSprite->setPosition(Convert::PhysicalPositionToPixelPoint(_winSize, _ball->getPosition()));
    CCLayer::draw();
}

void PlayerLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent){
    auto touch = (CCTouch*)pTouches->anyObject();
    if (!touch) return;
    
    auto delta = touch->getDelta();
    Position distance{delta.x / Convert::PixelsPerMeter, delta.y / Convert::PixelsPerMeter};
    
    auto pos = _paddle->getPosition();
    pos.x += distance.x;
    pos.y += distance.y;
    
    _paddle->setPosition(pos);
    _paddleSprite->setPositionX(_paddleSprite->getPositionX() + delta.x);
}