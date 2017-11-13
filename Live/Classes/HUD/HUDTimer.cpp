#include "HUDTimer.h"

USING_NS_CC;

HUDTimer::HUDTimer() {
    // Set size and position of this component
    setPosition(Vec2(Director::getInstance()->getVisibleSize().width-100,
        Director::getInstance()->getVisibleSize().height-50));
    setContentSize(Size(200,100));

    // Create, customize, and add label
    m_label = Label::createWithTTF("Day " + std::to_string(GameTimer::getInstance()->getDaysElapsed()),
        "fonts/emulogic.ttf", 16);
    m_label->setColor(Color3B(255, 255, 255));
    m_label->setPosition(Vec2(0, 0));
    this->addChild(m_label, 1);
}

void HUDTimer::update() {
    if(GameTimer::getInstance()->getCurrentDayPhase() == GameTimer::DAY) {
        m_label->setString("Day " + std::to_string(GameTimer::getInstance()->getDaysElapsed()));
    } else {
        m_label->setString("Night " + std::to_string(GameTimer::getInstance()->getDaysElapsed()));
    }
}

HUDTimer::~HUDTimer() {}

void HUDTimer::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, bool transformUpdated){}
