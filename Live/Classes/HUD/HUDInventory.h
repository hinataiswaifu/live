#pragma once

#include "cocos2d.h"
#include "HUDInventoryItem.h"
#include "../Inventory.h"

class HUDInventory : public cocos2d::LayerColor {
public:
    HUDInventory(Inventory* inventory);
    ~HUDInventory();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    //
    // void addItem();

    // Update views
    void update();

private:
    // Components of a HUDInventory
    Inventory* inventory;
    HUDInventoryItem* hud_items[MAX_ITEMS];
};
