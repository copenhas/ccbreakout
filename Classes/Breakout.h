//
//  Breakout.h
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#ifndef Breakout_Breakout_h
#define Breakout_Breakout_h

#include <vector>
#include "Box2D.h"


/**************************************************
 * BASE TOP LEVEL TYPES
 *************************************************/

enum class GameObjectId {
    Level,
    Paddle,
    Ball,
    Block
};

class GameObject {
public:
    virtual ~GameObject() =0;
    
    virtual GameObjectId getId() const =0;
    virtual void addToWorld()=0;
    virtual void removeFromWorld()=0;
    virtual void collision(GameObject* obj)=0;
};

enum class GameState {
    Start,
    Playing,
    Lost,
    Won
};

class GameInstance {
public:
    GameInstance();
    ~GameInstance();
    
    b2World* getWorld();
    GameState getState();
    void addToGame(GameObject* obj);
    
private:
    GameState _state;
    b2World* _world;
    vector<GameObject*> _objects;
};


/**************************************************
 * GAME OBJECTS
 *************************************************/

class Ball: public GameObject {
    Ball(GameInstance* game);
    ~Ball();
    
    GameObjectId getId() const;
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj);
    
private:
    GameInstance* _game;
    b2Body* _body;
};

class Paddle: public GameObject {
public:
    Paddle(GameInstance* game, Ball* ball);
    ~Paddle();
    
    GameObjectId getId() const;
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj);
    
private:
    GameInstance* _game;
    Ball* ball;
    b2Body* _body;
};

class Block: public GameObject {
public:
    Block(GameInstance* game);
    ~Block();
    
    GameObjectId getId() const;
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj);

private:
    GameInstance* _game;
    b2Body* _body;
    int _hitCount;
    int _life;
};

class Level: public GameObject {
public:
    Level(GameInstance* game);
    ~Level();
    
    GameObjectId getId() const;
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj);
    
private:
    GameInstance* _game;
    b2Body* _walls;
    std::vector<Block> _blocks;
};

#endif
