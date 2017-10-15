#include "HUD.h"

USING_NS_CC;

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
    Sprite* hunger_bar_sprite = Sprite::create("UI/spr_bar_hunger.png");
    m_hunger_bar =
        new HUDBar("Hunger", 100, 50,
                   Director::getInstance()->getVisibleSize().height - 25, hunger_bar_sprite);
    addChild(m_hunger_bar, 1);

    // Add Stamina HUDBar
    Sprite* stamina_bar_sprite = Sprite::create("UI/spr_bar_stamina.png");
    m_stamina_bar =
        new HUDBar("Stamina", 100, 50,
                   Director::getInstance()->getVisibleSize().height - 60, stamina_bar_sprite);
    addChild(m_stamina_bar, 2);

    m_inventory = new HUDInventory();
    addChild(m_inventory, 3);
    
    // Add Message Box
    m_message_box = new HUDMessage("hello world");
    addChild(m_message_box, 4);
}

void HUD::update() {
    // Update values in HUDBars with appropriate Player values
    m_hunger_bar->updateCurr(m_player->getHunger());
    m_stamina_bar->updateCurr(m_player->getStamina());

    // Update views
    m_hunger_bar->update();
    m_stamina_bar->update();
}

void HUD::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
               bool transformUpdated) {}
