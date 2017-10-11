#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SPRITE_GRID_X 1
#define SPRITE_GRID_Y 6
#define SPRITE_DIM 17

#define MOVE_STEP 50

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    // extract the m_player from the m_playersheet
    m_player = Sprite::create("Spritesheet/roguelikeChar_transparent.png",
            Rect(SPRITE_GRID_X*SPRITE_DIM, SPRITE_GRID_Y*SPRITE_DIM, SPRITE_DIM, SPRITE_DIM));
    m_player->setPosition(100, 100);
    m_player->setScale(2.0);

    this->addChild(m_player, 0);


    auto kb_listener = EventListenerKeyboard::create();
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    kb_listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    kb_listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(kb_listener,this);

    // Let cocos know we have an update function to be called.
    this->scheduleUpdate();

    return true;
}

bool MainScene::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double MainScene::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously

    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void MainScene::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);

    Vec2 loc = m_player->getPosition();
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)) delta *= 2;
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
                m_player->setPosition(loc.x-(MOVE_STEP*delta),loc.y);
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
                m_player->setPosition(loc.x+(MOVE_STEP*delta),loc.y);
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
                m_player->setPosition(loc.x,loc.y+(MOVE_STEP*delta));
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
                m_player->setPosition(loc.x,loc.y-(MOVE_STEP*delta));
    }
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> MainScene::keys;
