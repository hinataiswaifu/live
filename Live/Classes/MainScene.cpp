#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SPRITE_GRID_X 1
#define SPRITE_GRID_Y 6
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
    m_player = new Player("Spritesheet/roguelikeChar_transparent.png",
            SPRITE_GRID_X, SPRITE_GRID_Y, 100,100);
    // extract the m_player from the m_playersheet
    this->addChild(m_player->getSprite(), 0);

    auto _hud = MessageHUD::createLayer("helloworld");
    this->addChild(_hud, 2);

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

    TMXTiledMap* _tileMap = TMXTiledMap::create("map2.tmx");
    this->addChild(_tileMap, -1);

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

    if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_SHIFT)) delta *= 2;
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_A)) {
                m_player->moveX(-(MOVE_STEP*delta));
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_D)) {
                m_player->moveX(+(MOVE_STEP*delta));
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_W)) {
                m_player->moveY(+(MOVE_STEP*delta));
    }
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) ||
                isKeyPressed(EventKeyboard::KeyCode::KEY_S)) {
                m_player->moveY(-(MOVE_STEP*delta));
    }
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> MainScene::keys;
