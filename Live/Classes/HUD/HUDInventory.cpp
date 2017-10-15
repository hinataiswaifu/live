#include "HUDInventory.h"

USING_NS_CC;

HUDInventory::~HUDInventory() {

}

HUDInventory::HUDInventory() {
  LayerColor::initWithColor(Color4B(255, 255, 255, 255));
  double inv_width = 5+(INVENTORY_SLOT_SIZE+5)*INVENTORY_SLOTS;
  setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2 - inv_width/2,0));
  setContentSize(Size(inv_width,INVENTORY_SLOT_SIZE+10));

  for(int i = 0; i < INVENTORY_SLOTS; i++) {
    HUDInventoryItem* item = new HUDInventoryItem( 5 + (5 + INVENTORY_SLOT_SIZE)*i, 5 );
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
