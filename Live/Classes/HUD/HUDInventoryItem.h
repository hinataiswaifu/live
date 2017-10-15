#pragma once

#include "cocos2d.h"
#include "../Inventory.h"

#define INVENTORY_SLOT_SIZE 60

class HUDInventoryItem : public cocos2d::LayerColor {
public:
    HUDInventoryItem(Inventory* inventory, int index, double x, double y);
    ~HUDInventoryItem();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    // Update views
    void update();

private:
    int index;
    Inventory* inventory;
};
