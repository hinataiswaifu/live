#include "DroppedItem.h"

USING_NS_CC;

void DroppedItem::setHitbox(int x, int y, int width, int length) {
	m_hitbox = Rect(x,y,length,width);
}

 cocos2d::Rect DroppedItem::getHitbox() {
 	return m_hitbox;
 }

bool DroppedItem::checkCollision(cocos2d::Point point) {
	if(m_hitbox.containsPoint(point)) {
		return true;
	}
	return false;
}
