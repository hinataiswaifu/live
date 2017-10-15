#include "HUDInventory.h"

USING_NS_CC;

HUDInventory::~HUDInventory() {}

HUDInventory::HUDInventory(Inventory* inventory) : inventory(inventory) {
    LayerColor::initWithColor(Color4B(255, 255, 255, 255));
    double inv_width = BORDER_PX + (INVENTORY_SLOT_SIZE + BORDER_PX) * MAX_ITEMS;
    setPosition(
        Vec2(Director::getInstance()->getVisibleSize().width / 2 - inv_width / 2, 0));
    setContentSize(Size(inv_width, INVENTORY_SLOT_SIZE + BORDER_PX * 2));

    for (int i = 0; i < MAX_ITEMS; i++) {
        hud_items[i] = new HUDInventoryItem(
            inventory->getItemSlot(i), BORDER_PX + (BORDER_PX + INVENTORY_SLOT_SIZE) * i,
            BORDER_PX);
        addChild(hud_items[i], i);
    }
}

void HUDInventory::update() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        hud_items[i]->update();
    }
}

void HUDInventory::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                        bool transformUpdated) {}
