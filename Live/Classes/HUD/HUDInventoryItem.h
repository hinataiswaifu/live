#pragma once

#include "cocos2d.h"
#include "../Item.h"

#define INVENTORY_SLOT_SIZE 54

class HUDInventoryItem : public cocos2d::LayerColor {
public:
    HUDInventoryItem(Item** item, double x, double y);
    ~HUDInventoryItem();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);
    void update();

private:
    Item** item;
};
