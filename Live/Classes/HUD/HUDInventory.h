#pragma once

#include "cocos2d.h"
#include "HUDInventoryItem.h"

#define INVENTORY_SLOTS 9

class HUDInventory : public cocos2d::LayerColor
{
    public:
        HUDInventory();
        ~HUDInventory();

        virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

        //
        // void addItem();

        // Update views
        void update();

    private:
        // Components of a HUDInventory
        HUDInventoryItem* m_items[INVENTORY_SLOTS];
};
