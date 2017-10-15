#pragma once

#include "GameObject.h"

class Player;
class Item : public GameObject {
protected:
    const unsigned int weight;

public:
    Item(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
         unsigned int weight)
        : GameObject(sprite_file, grid_pos_x, grid_pos_y), weight(weight) {}
    virtual bool use(Player& p) = 0;
    unsigned int getWeight() { return weight; }
};