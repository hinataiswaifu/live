#include "Arrow.h"

USING_NS_CC;

Arrow::Arrow(float pos_x, float pos_y, Direction dir) : GameObject("Spritesheet/arrow.png"), m_orientation(dir) {
	newSprite();
	m_sprite->setPosition(Vec2(pos_x, pos_y));
	if(dir == DIR_UP) { m_sprite->setRotation(-90); }
	else if (dir == DIR_LEFT) { m_sprite->setRotation(180); }
	else if (dir == DIR_DOWN) { m_sprite->setRotation(90); }
	m_distance_travelled = 0;
	m_expired = false;
}

void Arrow::move(float x, float y) {
    Vec2 loc = m_sprite->getPosition();
    m_sprite->setPosition(loc.x + x, loc.y + y);
}

void Arrow::update() {
	if(m_distance_travelled > EXPIRE_LIMIT) {
		m_expired = true;
		m_sprite->setOpacity(0);
	} else {
		if(m_orientation == DIR_LEFT) { move(-SPEED, 0); }
		else if(m_orientation == DIR_RIGHT) { move(SPEED, 0); }
		else if(m_orientation == DIR_UP) { move(0, SPEED); }
		else if(m_orientation == DIR_DOWN) { move(0, -SPEED); }
		m_distance_travelled += SPEED;
	}

}

bool Arrow::isExpired() {
	return m_expired;
}
