#include "HUD.h"

HUD::HUD(Player* player) {
    m_player = player;
}

HUD::~HUD() {}

HUD* HUD::createLayer(Player* player)
{
    HUD* a = new HUD(player);
    a->create();
    a->setColor(cocos2d::Color3B(0, 0, 0));

    a->setContentSize(cocos2d::Size(1, 1));
    a->setAnchorPoint(cocos2d::Vec2(0, 0));

    a->initOptions();

    return a;
}

void HUD::initOptions()
{
    m_hungerBar = new HUDBar("Hunger", 100, 50, cocos2d::Director::getInstance()->getVisibleSize().height - 50);
    addChild(m_hungerBar, 1);

    m_staminaBar = new HUDBar("Stamina", 100, 50, cocos2d::Director::getInstance()->getVisibleSize().height - 150);
    addChild(m_staminaBar, 2);

}

void HUD::update() {
    m_hungerBar->updateCurr(m_player->getHunger());
    m_staminaBar->updateCurr(m_player->getStamina());

    m_hungerBar->update();
    m_staminaBar->update();
}

void HUD::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
                         bool transformUpdated) {}
