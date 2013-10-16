//
//  BreakoutCocos.h
//  Breakout
//
//  Created by Sean Copenhaver on 10/16/13.
//
//

#ifndef Breakout_BreakoutCocos_h
#define Breakout_BreakoutCocos_h

#include <cocos2d.h>
#include "Breakout.h"

class Convert {
public:
    static constexpr float PixelsPerMeter = 20.0;

    static Position PixelPointToPhysicalPosition(cocos2d::CCSize winSize, cocos2d::CCPoint point) {
        return {point.x / PixelsPerMeter, (winSize.height - point.y) / PixelsPerMeter};
    }
    
    static Size PixelSizeToPhysicalSize(cocos2d::CCSize size) {
        return {size.height / PixelsPerMeter, size.width / PixelsPerMeter};
    }
};

class LevelLayer: public cocos2d::CCLayer {
public:
    LevelLayer(GameInstance* level);
    ~LevelLayer();

private:
    GameInstance* _game;
    Level* _level;
    cocos2d::CCTMXTiledMap* _map;
    
    void loadLevel();
};

class InGameScene: public cocos2d::CCScene {
public:
    InGameScene();
    ~InGameScene();
    
private:
    GameInstance* _game;
    LevelLayer* _levelLayer;
};

#endif
