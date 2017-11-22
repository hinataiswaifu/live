#pragma once

#include "Item.h"

class DroppedItem : public Item {
public:
    DroppedItem(const std::string& sprite_file, unsigned int weight)
        : Item(sprite_file, weight) {}
    DroppedItem(const std::string& sprite_file, unsigned int grid_pos_x, unsigned int grid_pos_y,
         unsigned int weight)
        : Item(sprite_file, grid_pos_x, grid_pos_y, weight) {}
		void setHitbox(int x, int y, int width, int length);
	    virtual cocos2d::Rect getHitbox();
	    bool checkCollision(cocos2d::Point);
	protected:
		cocos2d::Rect m_hitbox;
};
