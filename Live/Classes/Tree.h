#pragma once

#include "ResourceObstacle.h"
#include "Fruit.h"

#include <queue>

#define AVERAGE_DAY 1

#define TREE_SCALE_FACTOR 0.5
class Tree : public ResourceObstacle {
public:
    Tree(const std::string& sprite_sheet, float pos_x, float pos_y);
    virtual void update();
    virtual Item* gather(cocos2d::Point, Direction);		// Gather a resource from an obstacle you are facing
    virtual ~Tree();

private:
    std::queue<Cherry*> m_fruits;
    // store what the last day a fruit blossomed
    int m_last_day;
    int m_width;
    int m_height;
};
