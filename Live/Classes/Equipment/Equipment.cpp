#include "Equipment.h"

USING_NS_CC;

void Equipment::move(float x, float y) {
	CCLOG("Moving");
    Vec2 loc = m_sprite->getPosition();
    m_sprite->setPosition(loc.x + x, loc.y + y);
}
