#include "RigidGameObject.h"

USING_NS_CC;

RigidGameObject::RigidGameObject(const std::string sprite_file, unsigned int grid_pos_x,
               unsigned int grid_pos_y) : GameObject(sprite_file, grid_pos_x, grid_pos_y) {
	m_hitbox = Rect(0,0,0,0);
}

void RigidGameObject::setHitbox(int x, int y, int width, int length) {
	m_hitbox = Rect(x,y,length,width);
}

 cocos2d::Rect RigidGameObject::getHitbox() {
 	return m_hitbox;
 }

bool RigidGameObject::checkCollision(cocos2d::Rect &hitbox) {
	if(m_hitbox.intersectsRect(hitbox)) {
		return true;
	}
	return false;
}