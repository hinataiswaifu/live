#include "Fruit.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Direction.h"
#include "ResourceLayer.h"

USING_NS_CC;

#define MOVE_STEP 50
#define SPRITE_INDEX 6

#define TREE_X 5
#define TREE_Y 7
#define MAP_SPR_SHT_PX 64

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

    m_player = new Player("Animation/boy_walk_down.plist", SPRITE_INDEX);

    // Instantiate HUD and add to scene
    m_hud = new HUD(m_player);
    m_game_layer->addChild(m_map_manager->getTileMap(), -1);
    // add HUD to the root layer
    this->addChild(m_hud, 2);
    this->addChild(m_game_layer, 0);

    m_map_manager->addPlayer(m_player);
    m_player->setPosition(Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    m_map_items.push_back(new Pear());
    m_map_items.push_back(new Pear());
    m_map_items.push_back(new Orange());
    m_map_items.push_back(new Apple());

    for (auto it : m_map_items) {
        m_map_manager->getTileMap()->addChild(it->newSprite());
    }
    m_map_items[0]->setPosition(200, 300);
    m_map_items[1]->setPosition(300, 600);
    m_map_items[2]->setPosition(600, 600);
    m_map_items[3]->setPosition(500, 600);


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

    // Setup camera to follow the player
    m_camera = Follow::create(m_player->getSprite(), Rect::ZERO);
    m_camera->retain();
    m_game_layer->runAction(m_camera);

    return true;
}

bool MainScene::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if (keys.find(code) != keys.end() && !m_game_over) {
        // For now, let's update hunger here until we abstract away input into a separate
        // class?
        if (m_player->getHunger() <= 0) {
            m_hud->enqueueMessage("Game over!");
            m_game_over = true;
        }
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

    // Lookahead variable stores result of movement to be used in collision checks
    Point position_lookahead = m_player->getPosition();

    Direction dir = Direction::DIR_DOWN;
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)) {
        if (m_player->getStamina() > 0) {
            delta *= 2;
            m_player->updateStamina(STAMINA_DEGEN * delta);
        }
    } else {
        m_player->updateStamina(STAMINA_REGEN * delta);
    }

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
        position_lookahead += Point(-(MOVE_STEP * delta), 0);
        // Check if the movement results in collision. If so, undo the movement
        if (m_map_manager->checkCollision(position_lookahead)) {
            position_lookahead -= Point(-(MOVE_STEP * delta), 0);
        }
        dir = Direction::DIR_LEFT;
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
        position_lookahead += Point(MOVE_STEP * delta, 0);
        if (m_map_manager->checkCollision(position_lookahead)) {
            position_lookahead -= Point(+(MOVE_STEP * delta), 0);
        }
        dir = Direction::DIR_RIGHT;
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
        position_lookahead += Point(0, MOVE_STEP * delta);
        if (m_map_manager->checkCollision(position_lookahead)) {
            position_lookahead -= Point(0, MOVE_STEP * delta);
        }
        dir = Direction::DIR_UP;
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
        position_lookahead += Point(0, -(MOVE_STEP * delta));
        if (m_map_manager->checkCollision(position_lookahead)) {
            position_lookahead -= Point(0, -(MOVE_STEP * delta));
        }
        dir = Direction::DIR_DOWN;
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_Z)) {
        for (auto it : m_map_items) {
            if (m_player->pickup(it)) {
                m_map_items.erase(
                    std::remove(m_map_items.begin(), m_map_items.end(), it));
                break;  // Only allow one pick up at a time
            }
        }
        Item* resource = m_map_manager->gatherResource(position_lookahead, dir);
        if (resource != nullptr) {
            // regenerate the sprite
            m_map_manager->getTileMap()->addChild(resource->newSprite());
            m_player->pickup(resource);
        }
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_C) && m_key_c_released) {
        m_hud->dismissMessage();
        m_key_c_released = false;
    } else {
        m_key_c_released = true;
    }

    for (int i = 1; i <= 10; i++) {
        int code = static_cast<int>(EventKeyboard::KeyCode::KEY_0) + i;
        if (isKeyPressed(static_cast<EventKeyboard::KeyCode>(code))) {
            if (isKeyPressed(EventKeyboard::KeyCode::KEY_X)) {
                Item* item = m_player->drop(i);
                if (item != NULL) {
                    m_map_items.push_back(item);
                    m_map_manager->getTileMap()->addChild(item->newSprite());
                    item->setPosition(m_player->getPosition());
                }
            } else {
                m_player->use(i);
            }
        }
    }
    m_map_manager->update(delta);
    m_player->updateHunger(delta*HUNGER_DEGEN);
    m_hud->update();
    m_player->setPosition(position_lookahead, dir);

    // Set player's z order based on player sprite's lower edge
    m_player->setZOrder(-(m_player->getPosition().y - PLAYER_SPRITE_HEIGHT / 2));
}

// Because cocos2d-x requres createScene to be static, we need to make other
// non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point>
    MainScene::keys;
