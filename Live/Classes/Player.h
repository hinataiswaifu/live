#pragma once

#include "GameObject.h"
#include "cocos2d.h"
#include "Item.h"
#include "Inventory.h"

#define MAX_PICKUP_DISTANCE 40

class Player : public GameObject {
public:
    Player(const std::string& sprite_file, unsigned int grid_pos_x,
           unsigned int grid_pos_y);
    void updateHunger(float difference);
    void moveX(float x);
    void moveY(float y);
    void setPosition(cocos2d::Point point);
    void move(float x, float y);
    float getHunger() const;
    float getStamina() const;
    bool pickup(Item* item);
    Item* drop(int i);
    bool use(int i);
    Inventory* get_inventory();

private:
    float m_hunger;
    Inventory* m_inventory;
    float m_stamina;
};
