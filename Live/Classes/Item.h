#pragma once

#include "GameObject.h"

class Player;
class Item : public GameObject {
protected:
    unsigned int weight;
    std::string name;

public:
    Item() : GameObject() {}
    Item(const std::string& sprite_file, unsigned int weight, const std::string name = "")
        : GameObject(sprite_file), weight(weight), name(name) {}
    Item(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
         unsigned int weight, const std::string name = "")
        : GameObject(sprite_file, grid_pos_x, grid_pos_y), weight(weight), name(name) {}
    virtual bool use(Player& p) = 0;
    std::string getName() const { return name; }
    unsigned int getWeight() const { return weight; }
    void setName(std::string t_name) { name = t_name; }
};
