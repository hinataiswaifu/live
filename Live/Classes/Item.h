#pragma once

#include "GameObject.h"

class Player;
class Item : public GameObject {
protected:
    const unsigned int weight;
    const std::string name;

public:
    Item(const std::string& sprite_file, unsigned int weight, const std::string name = "")
        : GameObject(sprite_file), weight(weight), name(name) {}
    Item(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
         unsigned int weight, const std::string name = "")
        : GameObject(sprite_file, grid_pos_x, grid_pos_y), weight(weight), name(name) {}
    virtual bool use(Player& p) = 0;
    unsigned int getWeight() { return weight; }
    std::string getName() { return name; }
};
