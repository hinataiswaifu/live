#ifndef __RESOURCE_LAYER_H__
#define __RESOURCE_LAYER_H__

#include "cocos2d.h"
#include <map>
#include <stdlib.h> 
#include "ResourceObstacle.h"

#define MAX_RESOURCES 75

class ResourceLayer : public cocos2d::Layer
{
public:
    ResourceLayer();
    bool checkCollision(cocos2d::Point position);
    bool gather(cocos2d::Point position, Direction);	// Attempt to gather a resource from a resource obstacle you are facing

private:
    ResourceObstacle* m_resources[MAX_RESOURCES];
};


#endif // __RESOURCE_LAYER_H__