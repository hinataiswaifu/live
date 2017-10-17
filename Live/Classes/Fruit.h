#pragma once

#include "Food.h"

#define PEAR_WEIGHT 5
#define ORANGE_WEIGHT 4
#define APPLE_WEIGHT 6
#define CHERRY_WEIGHT 6

#define PEAR_SCALE 0.05
#define ORANGE_SCALE 0.05
#define APPLE_SCALE 0.07
#define CHERRY_SCALE 0.4

// all the same for now
#define FRUIT_HEALTH_INCREASE 11
USING_NS_CC;

// TODO Change these into a fruit factory
class Pear : public Food {
public:
    Pear() : Food("Spritesheet/trees/pear.png", PEAR_WEIGHT) {
        Food::health_increase = FRUIT_HEALTH_INCREASE;
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(PEAR_SCALE);
        return temp;
    }
};

class Orange : public Food {
public:
    Orange() : Food("Spritesheet/trees/orange.png", ORANGE_WEIGHT) {
        Food::health_increase = FRUIT_HEALTH_INCREASE;
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(ORANGE_SCALE);
        return temp;
    }
};

class Apple : public Food {
public:
    Apple() : Food("Spritesheet/trees/apple.png", APPLE_WEIGHT) {
        Food::health_increase = FRUIT_HEALTH_INCREASE;
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(APPLE_SCALE);
        return temp;
    }
};

class Cherry : public Food {
public:
    Cherry() : Food("Spritesheet/trees/cherry.png", CHERRY_WEIGHT) {
        Food::health_increase = FRUIT_HEALTH_INCREASE;
        m_sprite = newSprite();
    }
    Cherry(float x, float y) : Cherry() {
        setPosition(x,y);
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(CHERRY_SCALE);
        return temp;
    }

};
