#pragma once

#include "cocos2d.h"

#define SPRITE_DIM 17

class GameObject {
public:
    GameObject(const std::string sprite_file, unsigned int grid_pos_x,
               unsigned int grid_pos_y);
    virtual ~GameObject();
    virtual void setPosition(float x, float y);
    virtual void setPosition(cocos2d::Vec2);
    virtual cocos2d::Vec2 getPosition() const;
    const float distanceFrom(const GameObject& other);
    virtual cocos2d::Sprite* newSprite();
    virtual cocos2d::Sprite* getSprite();

protected:
    cocos2d::Sprite* m_sprite;
    const std::string m_sprite_file;
    unsigned int m_grid_pos_x;
    unsigned int m_grid_pos_y;
};
