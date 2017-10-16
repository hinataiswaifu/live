#pragma once

#include "Food.h"

#define PEAR_WEIGHT 5
#define ORANGE_WEIGHT 4
#define APPLE_WEIGHT 6

USING_NS_CC;

class Pear : public Food {
public:
    Pear() : Food("Spritesheet/trees/pear.png", PEAR_WEIGHT) {
        Food::health_increase = 11;
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(0.1, 0.1);
        return temp;
    }
};

class Orange : public Food {
public:
    Orange() : Food("Spritesheet/trees/orange.png", ORANGE_WEIGHT) {
        Food::health_increase = 7;
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(0.1, 0.1);
        return temp;
    }
};

class Apple : public Food {
public:
    Apple() : Food("Spritesheet/trees/apple.png", APPLE_WEIGHT) {
        Food::health_increase = 14;
    }
    Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        setScale(0.13, 0.13);
        return temp;
    }
};