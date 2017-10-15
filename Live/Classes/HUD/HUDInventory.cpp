#include "HUDInventory.h"

USING_NS_CC;

HUDInventory::~HUDInventory() {

}

HUDInventory::HUDInventory() {
    LayerColor::initWithColor(Color4B(255, 255, 255, 255));
    double inv_width = INVENTORY_SLOT_PADDING+(INVENTORY_SLOT_SIZE+INVENTORY_SLOT_PADDING)*INVENTORY_SLOTS;
    setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2 - inv_width/2,0));
    setContentSize(Size(inv_width,INVENTORY_SLOT_SIZE+INVENTORY_SLOT_PADDING*2));

    for(int i = 0; i < INVENTORY_SLOTS; i++) {
        HUDInventoryItem* item = new HUDInventoryItem( INVENTORY_SLOT_PADDING + (INVENTORY_SLOT_PADDING + INVENTORY_SLOT_SIZE)*i, INVENTORY_SLOT_PADDING );
        m_items[i] = item;
        // positioning stuff
        addChild(item, i);
    }
}

void HUDInventory::update() {
    for (int i = 0; i < INVENTORY_SLOTS; i++) {

    }
}

void HUDInventory::draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated) {

}
