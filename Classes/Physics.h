//
//  Physics.h
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#ifndef Breakout_Physics_h
#define Breakout_Physics_h

#include "Box2D.h"

class Physics {
public:
    static constexpr float Gravity = -18.0;
    static constexpr float TicksPerSecond = 1.0 / 90.0;
    static constexpr int IterationsPerTick = 10;
    static constexpr bool DrawBodies = true;
};

#endif
