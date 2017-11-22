#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include <map>
#include <vector>
#include "HUD/HUD.h"
#include "Item.h"
#include "Player.h"
#include "cocos2d.h"
#include "MapManager.h"
#include "NetworkManager.h"
#include "Tree.h"
#include "Animal.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


class MainScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void startGame( int seed );
    Player* getPlayer(int id = 0);
    MapManager* getMapManager();
    std::vector<Item*>& getMapItems();
    HUD* getHUD();
    bool isStarted();
    void update(float delta);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

private:
    bool m_started = false;
    Player* m_player;
#if MULTIPLAYER
    Player* m_player2;
    NetworkManager* m_network_manager;
#endif
    HUD* m_hud;
    std::vector<Item*> m_map_items;
    MapManager* m_map_manager;
    cocos2d::Follow* m_camera;
    cocos2d::Layer* m_game_layer;
};

#endif  // __MAIN_SCENE_H__
