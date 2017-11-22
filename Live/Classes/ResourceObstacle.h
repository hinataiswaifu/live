#pragma once

#include "GameObject.h"
#include "Direction.h"
#include "RigidGameObject.h"
#include "Item.h"

#define TREE_WIDTH 64
#define TREE_HEIGHT 64

#define FRUIT_PADDING_X 5
#define FRUIT_PADDING_Y 30

#define MAX_FRUITS 3

class ResourceObstacle : public RigidGameObject {
public:
    ResourceObstacle() : RigidGameObject() {};
	ResourceObstacle(const std::string spritesheet, int spritesheet_x, int spritesheet_y, float posX, float posY);
    ResourceObstacle(float x, float y);
    virtual Item* gather(cocos2d::Point, Direction);		// Gather a resource from an obstacle you are facing
protected:
    std::queue<Item*> m_items;
};
