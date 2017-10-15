#include "HUDInventoryItem.h"

USING_NS_CC;

HUDInventoryItem::HUDInventoryItem(Item** item, double x, double y) : item(item) {
    LayerColor::initWithColor(Color4B(170, 170, 170, 170));
    setPosition(Vec2(x, y));
    setContentSize(Size(INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE));
}

void HUDInventoryItem::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                            bool transformUpdated) {}

void HUDInventoryItem::update() {
    removeAllChildren();
    if (*item == NULL) return;
    addChild((*item)->newSprite());
    (*item)->setPosition(0, INVENTORY_SLOT_SIZE);
    (*item)->getSprite()->setScale(2 * INVENTORY_SLOT_SIZE / SPRITE_DIM);
}

HUDInventoryItem::~HUDInventoryItem() {}