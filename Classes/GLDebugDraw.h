//
//  GLDebugDraw.h
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#ifndef __Breakout__GLDebugDraw__
#define __Breakout__GLDebugDraw__

#include "cocos2d.h"
#include "Box2D.h"

class GLDebugDraw : public b2Draw {    
public:
    
    GLDebugDraw(cocos2d::CCSize winSize);
    
    void DrawSolidPolygon(const b2Vec2* aVertices, int32 aVertexCount, const b2Color& aColor);
    void DrawSolidCircle(const b2Vec2& aCenter, float32 aRadius, const b2Vec2& aAxis, const b2Color& aColor);
    
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
    void DrawTransform(const b2Transform& xf);

private:
    cocos2d::CCSize _winSize;
};

#endif /* defined(__Breakout__GLDebugDraw__) */
