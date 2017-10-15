#pragma once

#include "Item.h"
#include "Player.h"

#define FOOD_X 36
#define FOOD_Y 1
#define FOOD_WEIGHT 6

class Food : public Item {
public:
    Food(int sprite_x, int sprite_y)
        : Item("Spritesheet/roguelikeChar_transparent.png", FOOD_X, FOOD_Y, sprite_x,
               sprite_y, FOOD_WEIGHT) {}
    bool use(Player& p) {
        p.updateHunger(50);
        return true;
    }
};