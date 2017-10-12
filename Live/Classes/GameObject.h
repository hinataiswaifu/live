#pragma once

#include "cocos2d.h"

#define SPRITE_DIM 17

class GameObject {
public:
    GameObject(const std::string& sprite_file, unsigned int grid_pos_x,
            unsigned int grid_pos_y, int sprite_x, int sprite_y);
    virtual ~GameObject();
    virtual void setPosition(float x, float y);
    virtual cocos2d::Vec2 getPosition() const;
    virtual cocos2d::Sprite* getSprite();

protected:
    cocos2d::Sprite* m_sprite;
};
