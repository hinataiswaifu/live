#pragma once

#include "GameObject.h"
#include "cocos2d.h"

class Player : public GameObject {
public:
    Player(const std::string& sprite_file, unsigned int grid_pos_x,
           unsigned int grid_pos_y, int sprite_x, int sprite_y);
    void updateHunger(float difference);
    void moveX(float x);
    void moveY(float y);
    void setPosition(cocos2d::Point point);
    void move(float x, float y);
    float getHunger() const;
    float getStamina() const;

private:
    float m_hunger;
    float m_stamina;
};
