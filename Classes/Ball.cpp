
#include "Breakout.h"

Ball::Ball(GameInstance* game) {
    _game = game;
}

Ball::~Ball() {
    
}

GameObjectId Ball::getId() const { return GameObjectId::Ball; }

Position Ball::getPosition() const {
    auto point = _body->GetPosition();
    return { point.x, point.y };
}

void Ball::setPosition(Position p) {
    _body->SetTransform({p.x, p.y}, 0);
}

void Ball::addToWorld() {
    auto size = _game->getSize();
    
    b2BodyDef bodyDef;
    bodyDef.position.Set(size.width / 2 + 1.5, 5);
    bodyDef.userData = this;
    bodyDef.bullet = true;
    bodyDef.gravityScale = 0.25;
    bodyDef.type = b2BodyType::b2_dynamicBody;
    _body = _game->getWorld()->CreateBody(&bodyDef);
    
    b2CircleShape shape;
    shape.m_radius = 0.25;
    
    b2FixtureDef fixture;
    fixture.restitution = 0.5;
    fixture.shape = &shape;
    _body->CreateFixture(&fixture);
}

void Ball::removeFromWorld() {
    _game->getWorld()->DestroyBody(_body);
}

void Ball::collision(GameObject* obj, const b2Fixture* fixture) {
    if (obj->getId() == GameObjectId::Paddle) {
    }
}