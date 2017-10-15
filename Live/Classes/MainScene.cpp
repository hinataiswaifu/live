#include "Food.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SPRITE_GRID_X 1
#define SPRITE_GRID_Y 6
#define MOVE_STEP 100

Scene* MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init() {
    m_tile_map = TMXTiledMap::create("map2.tmx");
    // extract the m_player from the m_playersheet
    m_player = new Player("Spritesheet/roguelikeChar_transparent.png", SPRITE_GRID_X,
                          SPRITE_GRID_Y);

    // Instantiate HUD and add to scene
    m_hud = new HUD(m_player);
    this->addChild(m_tile_map, -1);
    this->addChild(m_hud, 2);

    m_tile_map->addChild(m_player->newSprite(), INT_MAX);  // Player always on top
    m_player->setPosition(100, 100);

    m_map_items.push_back(new Food());
    m_map_items.push_back(new Food());
    for (auto it : m_map_items) {
        m_tile_map->addChild(it->newSprite());
    }
    m_map_items[0]->setPosition(200, 300);
    m_map_items[1]->setPosition(300, 400);

    auto kb_listener = EventListenerKeyboard::create();
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    kb_listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if (keys.find(keyCode) == keys.end()) {
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    kb_listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(kb_listener, this);

    // Let cocos know we have an update function to be called.
    this->scheduleUpdate();

    return true;
}

bool MainScene::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if (keys.find(code) != keys.end()) {
        // For now, let's update hunger here until we abstract away input into a separate
        // class?
        m_player->updateHunger(-0.01);
        return true;
    }
    return false;
}

double MainScene::keyPressedDuration(EventKeyboard::KeyCode code) {
    if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously

    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() - keys[code])
        .count();
}

void MainScene::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)) delta *= 2;
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
        m_player->moveX(-(MOVE_STEP * delta));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
        m_player->moveX(+(MOVE_STEP * delta));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
        m_player->moveY(+(MOVE_STEP * delta));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
        m_player->moveY(-(MOVE_STEP * delta));
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_Z)) {
        for (auto it : m_map_items) {
            if (m_player->pickup(it)) {
                m_map_items.erase(
                    std::remove(m_map_items.begin(), m_map_items.end(), it));
                break;  // Only allow one pick up at a time
            }
        }
    }

    for (int i = 1; i <= 10; i++) {
        int code = static_cast<int>(EventKeyboard::KeyCode::KEY_0) + i;
        if (isKeyPressed(static_cast<EventKeyboard::KeyCode>(code))) {
            if (isKeyPressed(EventKeyboard::KeyCode::KEY_X)) {
                Item* item = m_player->drop(i);
                if (item != NULL) {
                    m_map_items.push_back(item);
                    m_tile_map->addChild(item->newSprite());
                    item->setPosition(m_player->getPosition());
                }
            } else {
                m_player->use(i);
            }
        }
    }
    m_hud->update();
}
// Because cocos2d-x requres createScene to be static, we need to make other
// non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point>
    MainScene::keys;