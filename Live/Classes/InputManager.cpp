#include "InputManager.h"
#include "MainScene.h"
#include "Direction.h"

USING_NS_CC;
// Because cocos2d-x requres createScene to be static, we need to make other
// non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point>
    InputManager::keys;
bool InputManager::m_key_c_released = true;
// used to track gameover state, currently used to reject keyboard input
bool InputManager::m_game_over = false;
MainScene* InputManager::m_scene = nullptr;

EventListenerKeyboard* InputManager::initializeInputManager(MainScene* scene) {
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

    InputManager::m_scene = scene;

    return kb_listener;
}

bool InputManager::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if (keys.find(code) != keys.end()) {
            return true;
    }
    return false;
}

double InputManager::keyPressedDuration(EventKeyboard::KeyCode code) {
    if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously

    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - keys[code])
        .count();
}
void InputManager::update(float delta) {
    // check if the game is over
    if (!m_game_over) {
        if (m_scene->getPlayer()->getHunger() <= 0) {
            m_scene->getHUD()->enqueueMessage("Game over!");
            m_game_over = true;
        }
    }

    // Lookahead variable stores result of movement to be used in collision checks
    Point position_lookahead = m_scene->getPlayer()->getPosition();
    Direction dir = Direction::DIR_DOWN;

    if (InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
        position_lookahead += Point(-(MOVE_STEP * delta), 0);
        // Check if the movement results in collision. If so, undo the movement
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(-(MOVE_STEP * delta), 0);
        }
        dir = Direction::DIR_LEFT;
        AudioManager::getInstance()->enqueueSFX("footstep" + std::to_string(rand()%6]) + ".mp3");
    }
    if (InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
        position_lookahead += Point(MOVE_STEP * delta, 0);
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(+(MOVE_STEP * delta), 0);
        }
        dir = Direction::DIR_RIGHT;
        AudioManager::getInstance()->enqueueSFX("footstep" + std::to_string(rand()%6]) + ".mp3");
    }
    if (InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
        position_lookahead += Point(0, MOVE_STEP * delta);
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(0, MOVE_STEP * delta);
        }
        dir = Direction::DIR_UP;
        AudioManager::getInstance()->enqueueSFX("footstep" + std::to_string(rand()%6]) + ".mp3");
    }
    if (InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
        position_lookahead += Point(0, -(MOVE_STEP * delta));
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(0, -(MOVE_STEP * delta));
        }
        dir = Direction::DIR_DOWN;
        AudioManager::getInstance()->enqueueSFX("footstep" + std::to_string(rand()%6]) + ".mp3");
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_Z)) {
        for (auto it : m_scene->getMapItems()) {
            if (m_scene->getPlayer()->distanceFrom(*it) < 20 && m_scene->getPlayer()->pickup(it)) {
                m_scene->getMapItems().erase(
                        std::remove(m_scene->getMapItems().begin(), m_scene->getMapItems().end(), it));
                break;  // Only allow one pick up at a time
            }
        }
        Item* resource = m_scene->getMapManager()->gatherResource(position_lookahead, dir);
        if (resource != nullptr) {
            // Drop the resource and add it to the map
            resource->setPosition(position_lookahead);
            m_scene->getPlayer()->pickup(resource);
        }
    }
    if (InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_C) && m_key_c_released) {
        m_scene->getHUD()->dismissMessage();
        m_key_c_released = false;
    } else {
        m_key_c_released = true;
    }

    for (int i = 1; i <= 10; i++) {
        int code = static_cast<int>(EventKeyboard::KeyCode::KEY_0) + i;
        if (isKeyPressed(static_cast<EventKeyboard::KeyCode>(code))) {
            if (isKeyPressed(EventKeyboard::KeyCode::KEY_X)) {
                Item* item = m_scene->getPlayer()->drop(i);
                if (item != NULL) {
                    m_scene->getMapItems().push_back(item);
                    m_scene->getMapManager()->getTileMap()->addChild(item->newSprite());
                    item->setPosition(m_scene->getPlayer()->getPosition());
                }
            } else {
                m_scene->getPlayer()->use(i);
            }
        }
    }

    Point move_distance = position_lookahead - m_scene->getPlayer()->getPosition();
    // update the stamina
    if (InputManager::isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)
            && move_distance.getLengthSq() > 0.0001f) {
        if (m_scene->getPlayer()->getStamina() > 0) {
            position_lookahead += move_distance;
            m_scene->getPlayer()->updateStamina(STAMINA_DEGEN * delta);
        }
    } else {
        m_scene->getPlayer()->updateStamina(STAMINA_REGEN * delta);
    }

    // update the player's position
    m_scene->getPlayer()->setPosition(position_lookahead, dir);

    // Set player's z order based on player sprite's lower edge
    m_scene->getPlayer()->setZOrder(-(m_scene->getPlayer()->getPosition().y - PLAYER_SPRITE_HEIGHT / 2));
}
