#pragma once

#include "cocos2d.h"
#include "HUDBar.h"
#include "HUDInventory.h"
#include "Player.h"
#include "HUDMessage.h"
#include "HUDTimer.h"

class HUD : public cocos2d::Layer {
public:
    // HUD stores a reference to game objects that have the potential to update the HUD
    HUD(Player* player);

    ~HUD();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    // Update HUD based on current state of members
    void update();
    void enqueueMessage(const std::string& message);
    void dismissMessage();

private:
    // Helper method to initialize components
    void initComponents();

    // Bars to display
    HUDBar* m_hunger_bar;
    HUDBar* m_stamina_bar;
    HUDInventory* m_inventory;
    HUDMessage* m_message_box;
    HUDTimer* m_timer_hud;

    // Stored references to game objects
    Player* m_player;
};
