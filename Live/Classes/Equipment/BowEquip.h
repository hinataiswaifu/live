#pragma once

#include "Equipment.h"
#include "Player.h"
#include "Arrow.h"

class BowEquip : public Equipment {
public:
	BowEquip(Player& p, Direction orientation);
	Arrow* action(Player& p);
	Direction getOrientation();
	void updateOnMove(Player& p, cocos2d::Vec2 new_pos);
private:
	Direction m_orientation;
	float m_xpos;
	float m_ypos;
};
