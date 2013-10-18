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
#include "Physics.h"


/**************************************************
 * BASE TOP LEVEL TYPES
 *************************************************/

struct Position {
    float x;
    float y;
};

struct Size {
    float width;
    float height;
};

enum class GameObjectId {
    Level,
    Paddle,
    Ball,
    Block
};

class GameObject {
public:
    virtual ~GameObject() {}
    
    virtual GameObjectId getId() const =0;
    
    virtual Position getPosition() const =0;
    virtual void setPosition(Position p) =0;
    
    virtual void addToWorld()=0;
    virtual void removeFromWorld()=0;
    
    virtual void collision(GameObject* obj, const b2Fixture* fixture)=0;
};

enum class GameState {
    Start,
    Playing,
    Lost,
    Won
};

struct Collision {
    GameObject* obj1;
    b2Fixture* obj1Fixture;
    GameObject* obj2;
    b2Fixture* obj2Fixture;
};

class GameInstance : b2ContactListener {
public:
    GameInstance(Size size);
    ~GameInstance();
    
    void update();
    
    b2World* getWorld();
    const Size getSize() const;
    
    GameState getState();
    void start();
    void gameOver(bool won);
    
    void addToGame(GameObject* obj);
    
    void BeginContact(b2Contact* contact);
    
private:
    GameState _state;
    Size _size;
    b2World* _world;
    std::vector<GameObject*> _objects;
    std::vector<Collision> _collisions;
};


/**************************************************
 * GAME OBJECTS
 *************************************************/

class Block: public GameObject {
public:
    Block(GameInstance* game, Position pos, float bounce, float life);
    ~Block();
    
    GameObjectId getId() const;
    Position getPosition() const;
    void setPosition(Position p);
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj, const b2Fixture* fixture);

private:
    Position _pos;
    GameInstance* _game;
    b2Body* _body;
    int _hitCount;
    int _life;
    float _bounce;
};

class Level: public GameObject {
public:
    Level(GameInstance* game);
    ~Level();
    
    GameObjectId getId() const;
    Position getPosition() const;
    void setPosition(Position p);
    void addToWorld();
    void removeFromWorld();
    void addBlock(Block* block); //make the level create the block, you provide the position and size
    void collision(GameObject* obj, const b2Fixture* fixture);
    
private:
    GameInstance* _game;
    b2Body* _walls;
    b2Fixture* _floor;
    std::vector<Block*> _blocks;
};

class Paddle: public GameObject {
public:
    Paddle(GameInstance* game);
    ~Paddle();
    
    GameObjectId getId() const;
    Position getPosition() const;
    void setPosition(Position p);
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj, const b2Fixture* fixture);

private:
    GameInstance* _game;
    b2Body* _body;
};

class Ball: public GameObject {
public:
    Ball(GameInstance* game);
    ~Ball();
    
    GameObjectId getId() const;
    Position getPosition() const;
    void setPosition(Position p);
    void addToWorld();
    void removeFromWorld();
    void collision(GameObject* obj, const b2Fixture* fixture);
    
private:
    GameInstance* _game;
    b2Body* _body;
};

#endif
