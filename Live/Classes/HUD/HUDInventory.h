#pragma once

#include "cocos2d.h"
#include "HUDInventoryItem.h"
#include "../Inventory.h"

#define INVENTORY_HORIZONTAL_PADDING_PX 20
#define INVENTORY_VERTICAL_PADDING_PX 10

class HUDInventory : public cocos2d::Layer {
public:
    HUDInventory(Inventory* inventory);
    ~HUDInventory();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);
    void update();

private:
    Inventory* inventory;
    HUDInventoryItem* hud_items[MAX_ITEMS];
};
