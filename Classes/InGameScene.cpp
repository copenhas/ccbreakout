//
//  InGameScene.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#include "BreakoutCocos.h"

using namespace cocos2d;

InGameScene::InGameScene() {
    auto size = CCDirector::sharedDirector()->getWinSizeInPixels();
    _game = new GameInstance(Convert::PixelSizeToPhysicalSize(size));
    Level* level = new Level(_game);
    _game->addToGame(level);
    
    _levelLayer = new LevelLayer(_game);
    addChild(_levelLayer);
}

InGameScene::~InGameScene() {
    delete _game;
}