#pragma once

#include "GameObject.h"
#include "cocos2d.h"

class Player : public GameObject {
public:
    Player(const std::string& sprite_file, unsigned int grid_pos_x,
           unsigned int grid_pos_y, int sprite_x, int sprite_y);
    void updateHealth(float difference);
    void moveX(float x);
    void moveY(float y);
    void move(float x, float y);
    float getHealth() const;

private:
    float m_health;
    float m_stamina;
};
