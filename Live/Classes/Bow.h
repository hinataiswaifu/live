#pragma once

#include "DroppedItem.h"
#include "Player.h"

#define BOW_WEIGHT 20
USING_NS_CC;

class Bow : public DroppedItem {
public:
    Bow() : DroppedItem("Spritesheet/bow_static.png", BOW_WEIGHT) {
    	newSprite();
        // setScale(BOW_SCALE);
        setHitbox(450, 450, 200, 200);
    }
    bool use(Player& p);
};
