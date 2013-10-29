//
//  GameInstance.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/15/13.
//
//

#include "Breakout.h"

GameInstance::GameInstance(Size size) : _objects{}, _collisions{} {
    _size = size;
    _world = new b2World({0, Physics::Gravity});
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    _world->SetContactListener(this);
    
    //just go ahead and ignore game states for now
    _state = GameState::Playing;
}

GameInstance::~GameInstance() {
    for(auto obj : _objects) delete obj;
}
    
void GameInstance::update() {
    for(auto obj: _objects) obj->update();
    
    _world->Step(Physics::TicksPerSecond, Physics::IterationsPerTick, 1);
    
    for(auto collision : _collisions) {
        collision.obj1->collision(collision.obj2, collision.obj1Fixture);
        collision.obj2->collision(collision.obj1, collision.obj2Fixture);
    }
    
    _collisions.clear();
    
    for(auto obj : _objects) obj->triggerUpdated();
}
    
b2World* GameInstance::getWorld() {
    return _world;
}

const Size GameInstance::getSize() const { return _size; }

GameState GameInstance::getState() { return _state; }

void GameInstance::gameOver(bool won) {
    if (_state != GameState::Playing) return;
        
    if (won) _state = GameState::Won;
    else _state = GameState::Lost;
}

void GameInstance::addToGame(GameObject* obj){
    _objects.push_back(obj);
}

void GameInstance::BeginContact(b2Contact* contact) {
    auto obj1 = (GameObject*)(contact->GetFixtureA()->GetBody()->GetUserData());
    auto obj2 = (GameObject*)(contact->GetFixtureB()->GetBody()->GetUserData());
    
    if (obj1 && obj2) {
        _collisions.push_back({obj1, contact->GetFixtureA(), obj2, contact->GetFixtureB()});
    }
}
