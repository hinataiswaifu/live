#include "HUDInventory.h"

USING_NS_CC;

HUDInventory::HUDInventory(Inventory* inventory) : inventory(inventory) {
    double inv_width = INVENTORY_HORIZONTAL_PADDING_PX + (INVENTORY_SLOT_SIZE +
        INVENTORY_HORIZONTAL_PADDING_PX) * MAX_ITEMS;
    setPosition(
        Vec2(Director::getInstance()->getVisibleSize().width / 2 - inv_width / 2, 0));
    setContentSize(Size(inv_width, INVENTORY_SLOT_SIZE + INVENTORY_VERTICAL_PADDING_PX * 2));

    Sprite* inventory_background = Sprite::create("spr_inventory_background.png");
    inventory_background->setAnchorPoint(Vec2(0.5, 0));
    inventory_background->setPosition(Vec2(getContentSize().width/2, 0));
    addChild(inventory_background,-1);

    for (int i = 0; i < MAX_ITEMS; i++) {
        hud_items[i] = new HUDInventoryItem(
            inventory->getItemSlot(i), INVENTORY_HORIZONTAL_PADDING_PX + (INVENTORY_HORIZONTAL_PADDING_PX + INVENTORY_SLOT_SIZE) * i,
            INVENTORY_VERTICAL_PADDING_PX);
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

HUDInventory::~HUDInventory() {}
