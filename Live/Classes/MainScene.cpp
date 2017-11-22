#include "Fruit.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "AudioComponent.h"

USING_NS_CC;

#define TREE_X 5
#define TREE_Y 7
#define MAP_SPR_SHT_PX 64
#define SPRITE_INDEX 6

Scene* MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init() {
    m_game_layer = Layer::create();
    m_map_manager = new MapManager();
    m_game_layer->addChild(m_map_manager->getMap());

    m_player = new Player("Animation/boy_walk_down.plist", SPRITE_INDEX);

    // Instantiate HUD and add to scene
    m_hud = new HUD(m_player);
    // add HUD to the root layer
    this->addChild(m_hud, 2);
    this->addChild(m_game_layer, 0);

    m_map_manager->addPlayer(m_player);
    m_player->setPosition(Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

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

    // setup the audio manager
    AudioComponent bg_audio = AudioComponent("Audio/global_bg_day.mp3", 168);
    AudioManager::getInstance()->changeBackgroundMusic(bg_audio);

    AudioComponent footsteps[] = {
      AudioComponent("Audio/Footsteps/footstep1.mp3", 1),
      AudioComponent("Audio/Footsteps/footstep2.mp3", 1),
      AudioComponent("Audio/Footsteps/footstep3.mp3", 1),
      AudioComponent("Audio/Footsteps/footstep4.mp3", 1),
      AudioComponent("Audio/Footsteps/footstep5.mp3", 1),
      AudioComponent("Audio/Footsteps/footstep6.mp3", 1)
    };
    for (int i = 0; i < 6; i++) {
      AudioManager::getInstance()->enqueueRandomSFX(footsteps, 6)
    }

    return true;
}

void MainScene::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);

    InputManager::update(delta);
    m_map_manager->update(delta);
    m_player->updateHunger(delta*HUNGER_DEGEN);
    m_hud->update();
}

Player* MainScene::getPlayer(int id) {
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
