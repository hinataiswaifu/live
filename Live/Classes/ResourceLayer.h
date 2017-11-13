#ifndef __RESOURCE_LAYER_H__
#define __RESOURCE_LAYER_H__

#include "cocos2d.h"
#include <vector>
#include <stdlib.h>
#include "Tree.h"
#include "ResourceObstacle.h"

#define MAX_RESOURCES 75

class ResourceLayer : public cocos2d::Layer
{
public:
    ResourceLayer();
    bool checkCollision(cocos2d::Point position);
    Item* gather(cocos2d::Point position, Direction);	// Attempt to gather a resource from a resource obstacle you are facing
    void update();

private:
    ResourceObstacle* m_resources[MAX_RESOURCES];
    std::vector<Tree*> m_trees;
};


#endif // __RESOURCE_LAYER_H__
