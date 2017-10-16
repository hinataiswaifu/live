#pragma once

#include "GameObject.h"
#include "Direction.h"
#include "RigidGameObject.h"

class ResourceObstacle : public RigidGameObject {
public:
	ResourceObstacle(const std::string spritesheet, int spritesheet_x, int spritesheet_y, float posX, float posY);
    ResourceObstacle(float x, float y);
    bool gather(cocos2d::Point, Direction);		// Gather a resource from an obstacle you are facing
private:
	int m_resource_count;
};