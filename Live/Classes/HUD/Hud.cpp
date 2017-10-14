#include "Hud.h"

MessageHUD::MessageHUD() {}

MessageHUD::~MessageHUD() {}

MessageHUD* MessageHUD::createLayer(const std::string& _message)
{
    MessageHUD* a = new MessageHUD();
    a->create();
    a->setColor(cocos2d::Color3B(0, 0, 0));

    a->setContentSize(cocos2d::Size(1, 1));
    a->setAnchorPoint(cocos2d::Vec2(0, 0));

    a->initOptions(_message);

    return a;
}

void MessageHUD::initOptions(const std::string& _message)
{
    // _messageLabel = cocos2d::Label::createWithBMFont("/Fonts/Emulogic-6.fnt",_message.c_str());
    _messageLabel = cocos2d::Label::createWithSystemFont(_message.c_str(), "Ubuntu", 12);
    _messageLabel->setColor(cocos2d::Color3B(0, 215, 0));

    addChild(_messageLabel, 1);

    _messageLabel->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width/2, cocos2d::Director::getInstance()->getVisibleSize().height/2));

}

void MessageHUD::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
                         bool transformUpdated) {}
