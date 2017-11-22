#pragma once

#include "Food.h"

#define PEAR_WEIGHT 5
#define ORANGE_WEIGHT 4
#define APPLE_WEIGHT 6
#define CHERRY_WEIGHT 6

#define PEAR_SCALE 0.05
#define ORANGE_SCALE 0.05
#define APPLE_SCALE 0.14
#define CHERRY_SCALE 0.4

// all the same for now
#define FRUIT_HEALTH_INCREASE 11
USING_NS_CC;

class Apple : public Food {
public:
    Apple() : Food("Spritesheet/trees/apple.png", APPLE_WEIGHT, "Apple") {
        Food::health_increase = FRUIT_HEALTH_INCREASE;
        m_scale = APPLE_SCALE;
        m_sprite = newSprite();
    }
    Apple(float x, float y) : Apple() {
        setPosition(x,y);
    }
};

class Cherry : public Food {
public:
    Cherry() : Food("Spritesheet/trees/cherry.png", CHERRY_WEIGHT, "Cherry") {
        Food::health_increase = FRUIT_HEALTH_INCREASE;
        m_scale = CHERRY_SCALE;
        m_sprite = newSprite();
    }
    Cherry(float x, float y) : Cherry() {
        setPosition(x,y);
    }

};
