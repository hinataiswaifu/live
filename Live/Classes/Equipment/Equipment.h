#pragma once

#include "GameObject.h"
#include "Arrow.h"

class Player;

class Equipment : public GameObject {
public:
	Equipment(const std::string& sprite_frame_file) : GameObject(sprite_frame_file) {

	};
	void move(float x, float y);
	virtual Arrow* action(Player& p) = 0;
	virtual void updateOnMove(Player& p, cocos2d::Vec2 new_pos) = 0;
};
