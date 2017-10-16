#include "ResourceObstacle.h"

USING_NS_CC;

#define TREE_WIDTH 64
#define TREE_HEIGHT 64

ResourceObstacle::ResourceObstacle(const std::string spritesheet, int spritesheet_x, int spritesheet_y, float posX, float posY) 
	: RigidGameObject(spritesheet, spritesheet_x, spritesheet_y), m_resource_count(3)
{
	newSprite(TREE_WIDTH, TREE_HEIGHT);
    setPosition(posX, posY);
    m_hitbox = Rect(posX-(TREE_WIDTH/2),posY-(TREE_HEIGHT/2), TREE_WIDTH, TREE_HEIGHT/2);		// Set hitbox to lower half of sprite

    // Set Z-order based on bottom of sprite, so that
    //    obstacles lower on the y-axis are rendered in front of obstacles above it, enabling overlap
    setZOrder(-(posY-(TREE_HEIGHT/2)));
}

ResourceObstacle::ResourceObstacle(float x, float y) 
	: ResourceObstacle("Spritesheet/mapPack_spritesheet.png", 5*64, 7*64, x, y)
{}

// Gather resource, given that you are facing the obstacle
bool ResourceObstacle::gather(cocos2d::Point pt, Direction dir) {

	// Create a point in front of the player
	Point ray = pt;

	if(m_resource_count <= 0) {
		return false;
	}

	if(dir == DIR_LEFT) {
		ray += Point(-6, 0);
	} else if(dir == DIR_RIGHT) {
		ray += Point(6, 0);
	} else if(dir == DIR_DOWN) {
		ray += Point(0, -6);
	} else if(dir == DIR_UP) {
		ray += Point(0, 6);
	}

	if(m_hitbox.containsPoint(ray)) {
		m_resource_count -= 1;
		//Change sprite
		return true;
	}
	return false;
}