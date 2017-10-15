#include "HUDMessage.h"

USING_NS_CC;

HUDMessage::HUDMessage(const std::string& message) {
    // store message
    m_message = message;

    // Set size and position of this component
    double msg_width = 590;
    setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2 - msg_width/2, 60));
    setContentSize(Size(msg_width,100));

    // Create sprite as background
    Sprite* bg = Sprite::create("messageBackground.png");
    bg->setPosition(Vec2(msg_width/2, 60));
    bg->setOpacity(100);
    this->addChild(bg, 0);

    // Create, customize, and add label
    m_label = Label::createWithSystemFont(message.c_str(), "Ubuntu", 22);
    m_label->setColor(Color3B(0, 0, 0));
    m_label->setPosition(Vec2(msg_width/2, 30));
    this->addChild(m_label, 1);
}

HUDMessage::~HUDMessage() {}

void HUDMessage::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                  bool transformUpdated){}

void HUDMessage::setMessage(const std::string& message) {
    m_message = message;
}

void HUDMessage::update() {
   m_label->setString(m_message);
}

void HUDMessage::dismiss() {
    setOpacity(0);
}

void HUDMessage::show() {
    setOpacity(255);
}
