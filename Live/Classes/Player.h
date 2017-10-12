#pragma once

#include "GameObject.h"
#include "cocos2d.h"
#include "Item.h"
#include "Inventory.h"

#define MAX_PICKUP_DISTANCE 40

class Player : public GameObject {
public:
    Player(const std::string& sprite_file, unsigned int grid_pos_x,
           unsigned int grid_pos_y, int sprite_x, int sprite_y);
    void updateHunger(float difference);
    void moveX(float x);
    void moveY(float y);
    void move(float x, float y);
    float getHunger() const;
    float getStamina() const;
    bool pickup(Item *item);
private:
    float m_hunger;
    Inventory inventory;
    float m_stamina;
};
