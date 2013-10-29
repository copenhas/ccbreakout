//
//  Level.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/15/13.
//
//

#include "Breakout.h"

Level::Level(GameInstance* game) : _game{game}, _blocks{} {
    
}

Level::~Level() {
    for(auto block : _blocks) delete block;
}

GameObjectId Level::getId() const { return GameObjectId::Level; }

Position Level::getPosition() const {
    auto p = _walls->GetPosition();
    return {p.x, p.y};
}

void Level::setPosition(Position p) {
    _walls->SetTransform({p.x, p.y}, 0);
}

void Level::addToWorld() {
    auto world = _game->getWorld();
    auto worldSize = _game->getSize();
    
    b2BodyDef wallsDef;
    wallsDef.position.Set(0,0);
    wallsDef.userData = this;
    _walls = world->CreateBody(&wallsDef);
    
    b2EdgeShape box;
    //bottom
    box.Set({0,0}, {worldSize.width, 0});
    _floor = _walls->CreateFixture(&box, 0);
    
    //right
    box.Set({worldSize.width, 0}, {worldSize.width, worldSize.height});
    _walls->CreateFixture(&box, 0);
    
    //top
    box.Set({worldSize.width, worldSize.height}, {0, worldSize.height});
    _walls->CreateFixture(&box, 0);

    //left
    box.Set({0, worldSize.height}, {0, 0});
    _walls->CreateFixture(&box, 0);
    
    for(auto block : _blocks) {
        block->addToWorld();
    }
    
    triggerAddedToWorld();
}

void Level::removeFromWorld() {
    for(auto block : _blocks) {
        block->removeFromWorld();
    }
    
    if (_walls) _game->getWorld()->DestroyBody(_walls);
    
    triggerRemovedFromWorld();
}

void Level::addBlock(Block *block){
    _blocks.push_back(block);
    addChild(block);
}

void Level::collision(GameObject* obj, const b2Fixture* fixture) {
    if (obj->getId() == GameObjectId::Ball && fixture == _floor) {
        _game->gameOver(false);
    }
    
    triggerCollision();
}