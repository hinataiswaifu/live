#include "HUDMessage.h"

USING_NS_CC;

HUDMessage::HUDMessage() {

    // Set size and position of this component
    setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2 - MSG_WIDTH/2, 70));
    setContentSize(Size(MSG_WIDTH,100));

    // Create sprite as background
    m_background = Sprite::create("spr_messaging_background.png");
    m_background->setPosition(Vec2(MSG_WIDTH/2, MSG_PADDING));
    m_background->setOpacity(0);
    this->addChild(m_background, 0);

    // Create, customize, and add label
    m_label = Label::createWithTTF("", "fonts/emulogic.ttf", 14);
    m_label->setColor(Color3B(0, 0, 0));
    m_label->setPosition(Vec2(MSG_WIDTH/2, MSG_PADDING));
    m_label->setOpacity(0);
    this->addChild(m_label, 1);
}

HUDMessage::~HUDMessage() {}

void HUDMessage::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                  bool transformUpdated){}

void HUDMessage::enqueueMessage(const std::string& message) {
    // Show text and background
    m_label->setOpacity(255);
    m_background->setOpacity(255);
    // enqueue copy of message onto message queue
    std::string cpy = message;
    m_message_queue.push(cpy);
    readMessage();
}

void HUDMessage::readMessage() {
    // Set label to be the front-most message in queue
    m_label->setString(m_message_queue.front());
}

void HUDMessage::dismissMessage() {
    // dismiss message hud if no more messages
    if (m_message_queue.size() == 0) {
        m_label->setOpacity(0);
        m_background->setOpacity(0);
    } else {
        // read next message
        m_message_queue.pop();
        readMessage();
    }
}

void HUDMessage::show() {
    setOpacity(255);
}
