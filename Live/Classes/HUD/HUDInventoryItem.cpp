#include "HUDInventoryItem.h"
#include <iostream>
USING_NS_CC;

HUDInventoryItem::~HUDInventoryItem() {}

HUDInventoryItem::HUDInventoryItem(Inventory* inventory, int index, double x, double y)
    : inventory(inventory), index(index) {
    LayerColor::initWithColor(Color4B(170, 170, 170, 170));
    setPosition(Vec2(x, y));
    setContentSize(Size(INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE));
    //  DrawNode::drawRect(Vec2(50, 50), Vec2(100,100));
}

void HUDInventoryItem::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                            bool transformUpdated) {}

void HUDInventoryItem::update() {
    removeAllChildren();
    Item* item = inventory->get_item(index);
    if (item == NULL) return;
    std::cerr << item->get_weight() << std::endl;
    addChild(item->newSprite());
    item->setPosition(0, INVENTORY_SLOT_SIZE);
    item->getSprite()->setScale(INVENTORY_SLOT_SIZE / SPRITE_DIM);
}