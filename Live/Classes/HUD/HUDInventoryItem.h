#pragma once

#include "cocos2d.h"

#define INVENTORY_SLOT_SIZE 60

class HUDInventoryItem : public cocos2d::LayerColor
{
    public:
        HUDInventoryItem(double x, double y);
        ~HUDInventoryItem();

        virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

        // Update views
        void update();

    private:
        // Components of a HUDInventory

};
