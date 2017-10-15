#include "HUD.h"

HUD::HUD(const Player* player) {
    // Store references to game objects
    m_player = player;

    // Create and customize HUD
    create();
    setColor(cocos2d::Color3B(0, 0, 0));
    setContentSize(cocos2d::Size(1, 1));
    setAnchorPoint(cocos2d::Vec2(0, 0));

    // Create and add components to HUD
    initComponents();
}

HUD::~HUD() {}

void HUD::initComponents() {
    // Add Hunger HUDBar
    m_hungerBar =
        new HUDBar("Hunger", 100, 50,
                   cocos2d::Director::getInstance()->getVisibleSize().height - 50);
    addChild(m_hungerBar, 1);

    // Add Stamina HUDBar
    m_staminaBar =
        new HUDBar("Stamina", 100, 50,
                   cocos2d::Director::getInstance()->getVisibleSize().height - 150);
    addChild(m_staminaBar, 2);
}

void HUD::update() {
    // Update values in HUDBars with appropriate Player values
    m_hungerBar->updateCurr(m_player->getHunger());
    m_staminaBar->updateCurr(m_player->getStamina());

    // Update views
    m_hungerBar->update();
    m_staminaBar->update();
}

void HUD::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
               bool transformUpdated) {}
