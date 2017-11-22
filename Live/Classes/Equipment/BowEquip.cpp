#include "BowEquip.h"

USING_NS_CC;


BowEquip::BowEquip(Player& p, Direction orientation) : Equipment("Spritesheet/bow_static.png"), m_orientation(orientation) {
	newSprite();
	setPosition(p.getPosition());
	m_orientation = p.getOrientation();
	updateOnMove(p, p.getPosition());
}

Arrow* BowEquip::action(Player& p) {
	Arrow* tmp_arrow = new Arrow(m_xpos, m_ypos, m_orientation);
	p.getSprite()->getParent()->addChild(tmp_arrow->getSprite());
	// TODO Should figure out how to put a delay on this
	p.releaseAction();
	return tmp_arrow;
}

Direction BowEquip::getOrientation() {
	return m_orientation;
}

void BowEquip::updateOnMove(Player& p, Vec2 new_pos) {
    if(p.getOrientation() == DIR_LEFT) {
        setPosition(Vec2(new_pos.x - 12, new_pos.y - 2));
		m_xpos = new_pos.x - 12;
		m_ypos = new_pos.y - 2;
		if(m_orientation != DIR_LEFT) {
	        getSprite()->setScale(-1);
		}
    } else if (p.getOrientation() == DIR_RIGHT){
        setPosition(Vec2(new_pos.x + 12, new_pos.y - 2));
		if(m_orientation == DIR_LEFT) {
	        getSprite()->setScale(1);
		}
		m_xpos = new_pos.x + 12;
		m_ypos = new_pos.y - 2;
    } else if (p.getOrientation() == DIR_DOWN || p.getOrientation() == DIR_UP) {
        setPosition(Vec2(new_pos.x + 16, new_pos.y - 2));
		if(m_orientation == DIR_LEFT) {
	        getSprite()->setScale(1);
		}
		m_xpos = new_pos.x + 16;
		m_ypos = new_pos.y - 2;
	}
	m_orientation = p.getOrientation();
}
