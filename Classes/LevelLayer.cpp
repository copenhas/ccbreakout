//
//  LevelLayer.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#include "BreakoutCocos.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

LevelLayer::LevelLayer(GameInstance* game) {
    _game = game;
    _level = new Level(_game);
    _game->addToGame(_level);
    
    _background = CCSprite::create("background.jpg");
    _background->setAnchorPoint({0,0});
    _background->setPosition({0, 0});
    _background->setOpacity(100);
    addChild(_background, -1);

    loadLevel();
}

LevelLayer::~LevelLayer() {

}

void LevelLayer::loadLevel() {
    _map = CCTMXTiledMap::create("level1.tmx");

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

                auto tileId = tileLayer->tileGIDAt({x, y});
                auto props = _map->propertiesForGID(tileId);
                
                float bounce = atof(props->valueForKey("bounce")->getCString());
                float life = atof(props->valueForKey("strength")->getCString());
                
                auto block = new Block(_game, Convert::PixelPointToPhysicalPosition(winSize, sprite->getPosition()), bounce, life);
                block->setData(sprite);
                block->addListener(this);
                _level->addBlock(block);
            }
        }
    }
    
    _level->addToWorld();
    addChild(_map);
}

void LevelLayer::onRemovedFromWorld(GameObjectId objId, void* obj){
    if (objId == GameObjectId::Block) {
        auto block = (Block*)obj;
        auto sprite = (CCSprite*)block->getData();
        sprite->runAction(CCFadeOut::create(0.5));
        SimpleAudioEngine::sharedEngine()->playEffect("hit.m4a");
    }
}