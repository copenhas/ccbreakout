
#include "Breakout.h"

Paddle::Paddle(GameInstance* game) {
    _game = game;
}

Paddle::~Paddle() {
    
}

GameObjectId Paddle::getId() const { return GameObjectId::Paddle; }

Position Paddle::getPosition() const {
    auto point = _body->GetPosition();
    return { point.x, point.y };
}

void Paddle::setPosition(Position p) {
    auto current = getPosition();
    _body->SetTransform({p.x, current.y}, 0);
}

void Paddle::addToWorld() {
    auto size = _game->getSize();
    
    b2BodyDef bodyDef;
    bodyDef.position.Set(size.width / 2 + 1.5, 3);
    bodyDef.userData = this;
    _body = _game->getWorld()->CreateBody(&bodyDef);
    
    b2PolygonShape shape;
    shape.SetAsBox(1.5, 0.25);
    
    b2FixtureDef fixture;
    fixture.restitution = 4;
    fixture.shape = &shape;
    _body->CreateFixture(&fixture);
    
    _lastPos = _body->GetPosition();
    
    triggerAddedToWorld();
}

void Paddle::removeFromWorld() {
    _game->getWorld()->DestroyBody(_body);
    
    triggerRemovedFromWorld();
}

void Paddle::update() {
    _xVelocity = _lastPos.x - _body->GetPosition().x;
    _lastPos = _body->GetPosition();
}

void Paddle::collision(GameObject* obj, const b2Fixture* fixture) {
    if (obj->getId() == GameObjectId::Ball) {
        auto ball = (Ball*) obj;
        ball->addForce(-_xVelocity * 100, 0);
    }
    
    triggerCollision();
}
