#pragma once

#include "GameObject.h"

// Obstacles are game objects with hitboxes
class RigidGameObject : public GameObject {
public:
    RigidGameObject() : GameObject() {};
    RigidGameObject(const std::string sprite_file, unsigned int grid_pos_x,
               unsigned int grid_pos_y);

    void setHitbox(int x, int y, int width, int length);
    virtual cocos2d::Rect getHitbox();

    bool checkCollision(cocos2d::Rect&);
protected:
	cocos2d::Rect m_hitbox;
};
