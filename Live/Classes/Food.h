#pragma once

#include "Item.h"
#include "Player.h"

#include <iostream>

USING_NS_CC;

class Food : public Item {
protected:
    int health_increase = 0;
    float m_scale;

public:
    Food() : Item() {}
    Food(const std::string& sprite_file, unsigned int weight, std::string name)
        : Item(sprite_file, weight, name) {}
    Food(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
         unsigned int weight, std::string name)
        : Item(sprite_file, grid_pos_x, grid_pos_y, weight, name) {}
    bool use(Player& p) {
        p.updateHunger(health_increase);
        return true;
    }

    int getHealthInc() const {
        return health_increase;
    }

    virtual Sprite* newSprite() {
        Sprite* temp = GameObject::newSprite();
        temp->setScale(m_scale);
        return temp;
    }

    float getScale() const { return m_scale; }
    void setScale(float scale) { m_scale = scale; }

    void setHealthInc(int health) { health_increase = health; }
};
