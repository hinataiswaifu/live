#include "HUDInventoryItem.h"

USING_NS_CC;

HUDInventoryItem::~HUDInventoryItem() {}

HUDInventoryItem::HUDInventoryItem(double x, double y) {
  LayerColor::initWithColor(Color4B(170, 170, 170, 170));
  setPosition(Vec2(x, y));
  setContentSize(Size(INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE));
//  DrawNode::drawRect(Vec2(50, 50), Vec2(100,100));
}

void HUDInventoryItem::draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated) {

}
