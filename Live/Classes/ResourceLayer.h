#ifndef __RESOURCE_LAYER_H__
#define __RESOURCE_LAYER_H__

#include "cocos2d.h"
#include <vector>
#include <stdlib.h>
#include "Tree.h"
#include "ResourceObstacle.h"
#include "Animal.h"
#include "DroppedItem.h"

#define MAX_RESOURCES 75

class ResourceLayer : public cocos2d::Layer
{
public:
    ResourceLayer();
    ResourceLayer(std::vector<ResourceObstacle*> &obstacles, std::vector<Tree*> &trees, std::vector<Animal*> &animals);
    bool checkCollision(cocos2d::Point position);
    Item* gather(cocos2d::Point position, Direction);	// Attempt to gather a resource from a resource obstacle you are facing
    void update(float delta);

private:
    std::vector<ResourceObstacle*> m_resources;
    std::vector<Tree*> m_trees;
    std::vector<Animal*> m_animals;
    std::vector<DroppedItem*> m_dropped_items;
};


#endif // __RESOURCE_LAYER_H__
