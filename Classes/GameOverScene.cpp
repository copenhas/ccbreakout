
#include "BreakoutCocos.h"

using namespace cocos2d;

GameOverScene::GameOverScene() {
    auto winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
    
    auto gameOverLabel = CCLabelTTF::create("Game Over", "Helvetica", 52);
    auto textureSize = gameOverLabel->getTexture()->getContentSizeInPixels();
    gameOverLabel->setPosition(CCPoint(winSize.width / 2, (winSize.height / 3) * 2));
    addChild(gameOverLabel);
    
    auto restart = CCMenuItemFont::create("Restart", this, menu_selector(GameOverScene::restart));
    auto menu = CCMenu::create(restart, nullptr);
    menu->setPosition(CCPoint(winSize.width / 2, (winSize.height / 3) * 1.5));
    addChild(menu);
}

GameOverScene::~GameOverScene() {
    removeAllChildren();
}

void GameOverScene::cleanup() {
    CCScene::cleanup();
    delete this;
}

void GameOverScene::restart() {
    CCDirector::sharedDirector()->popScene();
}
