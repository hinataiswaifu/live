#include "EventManager.h"
#include "MainScene.h"
#include "Direction.h"
#include "AudioManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;
// Because cocos2d-x requres createScene to be static, we need to make other
// non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point>
    EventManager::keys;
bool EventManager::m_key_c_released = true;
bool EventManager::m_key_v_released = true;
// used to track gameover state, currently used to reject keyboard input
bool EventManager::m_game_over = false;
MainScene* EventManager::m_scene = nullptr;
int EventManager::m_footsteps_audio_queue_id = AudioManager::getInstance()->createNewAudioQueue();
AudioManager* EventManager::m_audio_mgr = AudioManager::getInstance();

EventListenerKeyboard* EventManager::initializeEventManager(MainScene* scene) {
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

    EventManager::m_scene = scene;

    // preload footsteps
    for(int i = 1; i < 7; i++) {
      CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
        ("Audio/Footsteps/footstep"
        + std::to_string(i)
        + ".mp3").c_str());
    }

    return kb_listener;
}

bool EventManager::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if (keys.find(code) != keys.end()) {
            return true;
    }
    return false;
}

double EventManager::keyPressedDuration(EventKeyboard::KeyCode code) {
    if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously

    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - keys[code])
        .count();
}

void EventManager::enqueueFootstep(int id) {
  if (EventManager::m_audio_mgr->getAudioQueueSize(id) < 1) {
    EventManager::m_audio_mgr->enqueueIntoAudioQueue(
      id,
      AudioComponent( "Audio/Footsteps/footstep"
                      + std::to_string(rand()%6+1)
                      + ".mp3",
                    1000)
    );
  }
}

void EventManager::update(float delta) {
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
    m_scene->setDroppedFood(nullptr);

    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
        EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
        position_lookahead += Point(-(MOVE_STEP * delta), 0);
        // Check if the movement results in collision. If so, undo the movement
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(-(MOVE_STEP * delta), 0);
        }
        dir = Direction::DIR_LEFT;
        EventManager::enqueueFootstep(m_footsteps_audio_queue_id);
    }
    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
        EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
        position_lookahead += Point(MOVE_STEP * delta, 0);
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(+(MOVE_STEP * delta), 0);
        }
        dir = Direction::DIR_RIGHT;
        EventManager::enqueueFootstep(m_footsteps_audio_queue_id);
    }
    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) ||
        EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
        position_lookahead += Point(0, MOVE_STEP * delta);
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(0, MOVE_STEP * delta);
        }
        dir = Direction::DIR_UP;
        EventManager::enqueueFootstep(m_footsteps_audio_queue_id);
    }
    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
        EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
        position_lookahead += Point(0, -(MOVE_STEP * delta));
        if (m_scene->getMapManager()->checkCollision(position_lookahead)) {
            position_lookahead -= Point(0, -(MOVE_STEP * delta));
        }
        dir = Direction::DIR_DOWN;
        EventManager::enqueueFootstep(m_footsteps_audio_queue_id);
    }
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_Z)) {
        for (auto it : m_scene->getMapItems()) {
            if (m_scene->getPlayer()->distanceFrom(*it) < 20 && m_scene->getPlayer()->pickup(it)) {
                m_scene->getHUD()->enqueueMessage("You picked up a " + it->getName());
                m_scene->getMapItems().erase(
                        std::remove(m_scene->getMapItems().begin(), m_scene->getMapItems().end(), it));
                Food* dummy = new Food();
                dummy->setName("x");
                m_scene->setDroppedFood(dummy);
                break;  // Only allow one pick up at a time
            }
        }
        if(!m_scene->getPlayer()->get_inventory()->isFull()) {
            Item* resource = m_scene->getMapManager()->gatherResource(position_lookahead, dir);
            if (resource != nullptr) {
                // Drop the resource and add it to the map
                resource->setPosition(position_lookahead);
                if (m_scene->getPlayer()->pickup(resource)) {
                    m_scene->getHUD()->enqueueMessage("You picked up a " + resource->getName());
                } else {
                    resource->getSprite()->removeFromParent();
                    m_scene->addMapItem(resource, m_scene->getPlayer()->getPosition());
                }
            }
        }
    }
    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_C)) {
        if(m_key_c_released) {
            m_scene->getHUD()->dismissMessage();
        }
        m_key_c_released = false;
    } else {
        m_key_c_released = true;
    }
    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_V)) {
        if(m_key_v_released) {
            Arrow* arrow = m_scene->getPlayer()->action();
            if(arrow != NULL) {
                m_scene->getMapManager()->addArrow(arrow);
            }
        }
        m_key_v_released = false;
    } else {
        m_key_v_released = true;
    }

    for (int i = 1; i <= 10; i++) {
        int code = static_cast<int>(EventKeyboard::KeyCode::KEY_0) + i;
        if (isKeyPressed(static_cast<EventKeyboard::KeyCode>(code))) {
            if (isKeyPressed(EventKeyboard::KeyCode::KEY_X)) {
                Item* item = m_scene->getPlayer()->drop(i);
                if (item != NULL) {
                    m_scene->getHUD()->enqueueMessage("You dropped a " + item->getName());
                    m_scene->addMapItem(item, m_scene->getPlayer()->getPosition());
                    m_scene->setDroppedFood(item);
                }
            } else {
                m_scene->getPlayer()->use(i);
            }
        }
    }

    Point move_distance = position_lookahead - m_scene->getPlayer()->getPosition();
    // update the stamina
    if (EventManager::isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)
            && move_distance.getLengthSq() > 0.0001f) {
        if (m_scene->getPlayer()->getStamina() > 0) {
            position_lookahead += move_distance;
            if(m_scene->getMapManager()->getWeather() == WeatherManager::SUNNY) {
                m_scene->getPlayer()->updateStamina(STAMINA_DEGEN * delta);
            } else {
                m_scene->getPlayer()->updateStamina(STAMINA_DEGEN * delta * 1.5);
            }
        }
    } else {
        if(m_scene->getMapManager()->getWeather() == WeatherManager::SUNNY) {
            m_scene->getPlayer()->updateStamina(STAMINA_REGEN * delta);
        } else {
            m_scene->getPlayer()->updateStamina(STAMINA_REGEN * delta * 0.5);
        }
    }

    // update the player's position
    m_scene->getPlayer()->setPosition(position_lookahead, dir);

    // Set player's z order based on player sprite's lower edge
    m_scene->getPlayer()->setZOrder(-(m_scene->getPlayer()->getPosition().y - PLAYER_SPRITE_HEIGHT / 2));
}
