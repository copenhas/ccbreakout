

#include "Breakout.h"


Block::Block(GameInstance* game, Position pos) : _game{game} {
    _pos = pos;
    _hitCount = 0;
    _life = 3;
}

Block::~Block() {
    
}

GameObjectId Block::getId() const { return GameObjectId::Block; }

Position Block::getPosition() const {
    auto p = _body->GetPosition();
    return {p.x, p.y};
}

void Block::setPosition(Position p) {
    _body->SetTransform({p.x, p.y}, 0);
}

void Block::addToWorld() {
    auto world = _game->getWorld();
    
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.type = b2BodyType::b2_staticBody;
    bodyDef.position.Set(_pos.x, _pos.y);
    _body = world->CreateBody(&bodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox(1.5, 0.5, {_pos.x + 1.5, _pos.y + 0.5}, 0); //hard coded to be 3 meters wide by 1 meter high
    _body->CreateFixture(&shape, 0);
}

void Block::removeFromWorld() {
    _game->getWorld()->DestroyBody(_body);
}

void Block::collision(GameObject *obj, const b2Fixture *fixture){
    if (obj->getId() == GameObjectId::Ball) {
        _hitCount++;
        
        if (_hitCount >= _life) removeFromWorld();
    }
}