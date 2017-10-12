#ifndef __ITEM__H__
#define __ITEM__H__

#include "GameObject.h"

class Player;
class Item : public GameObject {
protected:
    const unsigned int weight;
public:
    Item(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
        int sprite_x, int sprite_y, unsigned int weight) : 
    GameObject(sprite_file, grid_pos_x, grid_pos_y, sprite_x, sprite_y), weight(weight) {}
    virtual void use(Player &p) = 0;
    virtual void consume(Player &p) = 0;
};

#endif