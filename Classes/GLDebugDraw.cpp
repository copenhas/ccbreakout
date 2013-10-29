//
//  GLDebugDraw.cpp
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#include "GLDebugDraw.h"
#include "BreakoutCocos.h"

using namespace cocos2d;

GLDebugDraw::GLDebugDraw(CCSize winSize) {
    _winSize = winSize;
}

void GLDebugDraw::DrawSolidPolygon(const b2Vec2* aVertices, int32 aVertexCount, const b2Color& aColor) {
    CCPoint* vertices = new CCPoint[aVertexCount];
    
    // convert vertices to screen resolution
	for (int32 i = 0; i < aVertexCount; i++)
	{
        Position pos{aVertices[i].x, aVertices[i].y};
        auto point = Convert::PhysicalPositionToPixelPoint(_winSize, pos);
		vertices[i] = CCPoint(point.x + 1, point.y + 1);
	}
    
    ccDrawColor4F(aColor.r, aColor.g, aColor.b, 1.0f);
    ccDrawPoly(vertices, aVertexCount, true);
}

void GLDebugDraw::DrawSolidCircle(const b2Vec2& aCenter, float32 aRadius, const b2Vec2& aAxis, const b2Color& aColor) {
    ccDrawColor4F(aColor.r, aColor.g, aColor.b, 1.0f);
    
    Position pos{aCenter.x, aCenter.y};
    ccDrawCircle(Convert::PhysicalPositionToPixelPoint(_winSize, pos), aRadius * Convert::PixelsPerMeter, 0.0, 100, false, 1.0, 1.0);
}

void GLDebugDraw::DrawPolygon(const b2Vec2* aVertices, int32 aVertexCount, const b2Color& aColor){

}

void GLDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color){
    
}

void GLDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color){
    
}

void GLDebugDraw::DrawTransform(const b2Transform& xf){
    
}