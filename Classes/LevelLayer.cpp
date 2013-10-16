//
//  LevelLayer.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#include "BreakoutCocos.h"

using namespace cocos2d;

LevelLayer::LevelLayer(GameInstance* game) {
    _game = game;
    _level = new Level(_game);
    _game->addToGame(_level);
    
    _map = CCTMXTiledMap::create("level1.tmx");
    loadLevel();
    _level->addToWorld();
    
    addChild(_map);
}

LevelLayer::~LevelLayer() {
    
}

void LevelLayer::loadLevel() {
    auto winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    
    CCObject* obj = nullptr;
    CCARRAY_FOREACH(_map->getChildren(), obj){
        auto tileLayer = dynamic_cast<CCTMXLayer*>(obj);
        if (!tileLayer) continue;
        
        auto layerSize = tileLayer->getLayerSize();
        for(int y = 0; y < layerSize.height; y++) {
            for(int x = 0; x < layerSize.width; x++){
                auto sprite = tileLayer->tileAt({x, y});
                if (!sprite) continue;
                _level->addBlock(new Block(_game, Convert::PixelPointToPhysicalPosition(winSize, sprite->getPosition())));
            }
        }
    }
}