#pragma once

#include "Item.h"
#include "Player.h"

USING_NS_CC;

class Food : public Item {
protected:
    int health_increase = 0;

public:
    Food(const std::string& sprite_file, unsigned int weight)
        : Item(sprite_file, weight) {}
    Food(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
         unsigned int weight)
        : Item(sprite_file, grid_pos_x, grid_pos_y, weight) {}
    bool use(Player& p) {
        p.updateHunger(health_increase);
        return true;
    }
};