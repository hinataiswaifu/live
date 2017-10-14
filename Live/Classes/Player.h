#pragma once

#include "cocos2d.h"
#include "GameObject.h"

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

private:
    float m_hunger;
    float m_stamina;
};
