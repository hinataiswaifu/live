#include "Fruit.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "InputManager.h"
#include "Direction.h"
#include "ResourceLayer.h"
#include "Mapgen/MapGenerator.h"
#include "Mapgen/GeneratedResources.h"
#include <iostream>

USING_NS_CC;

#define TREE_X 5
#define TREE_Y 7
#define MAP_SPR_SHT_PX 64
#define SPRITE_INDEX 6
#define MAP_WIDTH 128
#define MAP_HEIGHT 128

Scene* MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init() {
    m_network_manager = new NetworkManager(this);
    return true;
}

void MainScene::startGame( int seed ) {
    m_started = true;
    m_game_layer = Layer::create();

    m_player = new Player("Animation/boy_walk_down.plist", SPRITE_INDEX);
    m_player2 = new Player("Animation/boy_walk_down.plist", SPRITE_INDEX);

    MapGenerator* mapgen = new MapGenerator( seed );
    GeneratedResources mapResources = mapgen->createMap(MAP_WIDTH, MAP_HEIGHT);
    delete mapgen;
    
    m_player->setPosition(mapResources.m_spawn_point);
    m_player2->setPosition(mapResources.m_spawn_point);

    m_map_manager = new MapManager(mapResources);
    m_game_layer->addChild(m_map_manager->getMap());

    // Instantiate HUD and add to scene
    m_hud = new HUD(m_player);
    // add HUD to the root layer
    this->addChild(m_hud, 2);
    this->addChild(m_game_layer, 0);

    m_map_manager->addPlayer(m_player);
    m_map_manager->addPlayer(m_player2);

    for (auto it : m_map_items) {
        m_map_manager->getTileMap()->addChild(it->newSprite());
    }

    // Let cocos know we have an update function to be called.
    this->scheduleUpdate();

    // Setup camera to follow the player
    m_camera = Follow::create(m_player->getSprite(), Rect::ZERO);
    m_camera->retain();
    m_game_layer->runAction(m_camera);


    // set up the input/event manager
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(
            InputManager::initializeInputManager(this), this);
}

void MainScene::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);

    InputManager::update(delta);
    m_map_manager->update(delta);
    m_player->updateHunger(delta*HUNGER_DEGEN);
    m_hud->update();
    m_network_manager->update();
}

Player* MainScene::getPlayer(int id) {
    if(id == 1) return m_player2;
    return m_player;
}

MapManager* MainScene::getMapManager() {
    return m_map_manager;
}

std::vector<Item*>& MainScene::getMapItems() {
    return m_map_items;
}

HUD* MainScene::getHUD() {
    return m_hud;
}

bool MainScene::isStarted() {
    return m_started;
}