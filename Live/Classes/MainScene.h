#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include <map>

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
    double keyPressedDuration(cocos2d::EventKeyboard::KeyCode);
    void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

private:
    static std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
    Player* m_player;
};

#endif // __MAIN_SCENE_H__
