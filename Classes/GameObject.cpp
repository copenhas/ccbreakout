
#include "Breakout.h"

using namespace std;

GameObject::GameObject() : _listeners{}, _children{} {

}

void GameObject::update() {
    for(auto child : _children) child->update();
}

void* GameObject::getData() {
    return _data;
}

void GameObject::setData(void *data){
    _data = data;
}

void GameObject::addListener(GameObjectListener *listener){
    _listeners.push_back(listener);
}

void GameObject::removeListener(GameObjectListener *listener){
    for(vector<GameObjectListener*>::iterator i = _listeners.begin(); i != _listeners.end(); ) {
        if (*i == listener) i = _listeners.erase(i);
        else ++i;
    }
}

void GameObject::addChild(GameObject *obj){
    _children.push_back(obj);
}

void GameObject::removeChild(GameObject *obj){
    for(vector<GameObject*>::iterator i = _children.begin(); i != _children.end(); ) {
        if (*i == obj) i = _children.erase(i);
        else ++i;
    }
}

void GameObject::triggerUpdated() {
    for(auto listener : _listeners) listener->onUpdated(getId(), this);
    for(auto child : _children) child->triggerUpdated();
}

void GameObject::triggerAddedToWorld() {
    for(auto listener : _listeners) listener->onAddedToWorld(getId(), this);
}

void GameObject::triggerRemovedFromWorld() {
    for(auto listener: _listeners) listener->onRemovedFromWorld(getId(), this);
}

void GameObject::triggerCollision() {
    for(auto listener: _listeners) listener->onCollision(getId(), this);
}