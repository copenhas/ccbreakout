//
//  InGameScene.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#include "BreakoutCocos.h"
#include "GLDebugDraw.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

InGameScene::InGameScene() {

}

InGameScene::~InGameScene() {

}

void InGameScene::draw() {
    CCScene::draw();
    if (_debugDraw) _game->getWorld()->DrawDebugData();
}

void InGameScene::update(float delta) {
    _game->update();
    
    if (_game->getState() == GameState::Lost) {
        unschedule(schedule_selector(InGameScene::update));
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(1.0, new GameOverScene()));
    }
}

void InGameScene::onExit() {
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    unschedule(schedule_selector(InGameScene::update));
    if (_debugDraw) delete _debugDraw;
    removeAllChildren();
    delete _game;
    
    CCScene::onExit();
}

void InGameScene::onEnter() {
    CCScene::onEnter();
    auto size = CCDirector::sharedDirector()->getWinSizeInPixels();
    
    _game = new GameInstance(Convert::PixelSizeToPhysicalSize(size));
    Level* level = new Level(_game);
    _game->addToGame(level);
    
    _levelLayer = new LevelLayer(_game);
    addChild(_levelLayer);
    
    _playerLayer = new PlayerLayer(_game);
    addChild(_playerLayer);
    
    if (Physics::DrawBodies) {
        _debugDraw = new GLDebugDraw(size);
        _debugDraw->SetFlags(b2Draw::e_shapeBit);
        _game->getWorld()->SetDebugDraw(_debugDraw);
    }
    
    schedule(schedule_selector(InGameScene::update), Physics::TicksPerSecond);
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.m4a", true);
}
