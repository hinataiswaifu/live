#pragma once

#include "ResourceObstacle.h"
#include "Fruit.h"

#include <queue>

#define AVERAGE_DAY 1

#define TREE_SCALE_FACTOR 0.5
class Tree : public ResourceObstacle {
public:
	enum FruitType { CHERRY, APPLE };
    Tree(const std::string& sprite_sheet, float pos_x, float pos_y);
    Tree(const std::string& sprite_sheet, float pos_x, float pos_y, FruitType ftype);
    virtual void update();
    virtual Item* gather(cocos2d::Point, Direction);		// Gather a resource from an obstacle you are facing
    virtual ~Tree();
private:
    std::queue<Food*> m_fruits;
    // store the last day a fruit blossomed
    int m_last_day;
    int m_width;
    int m_height;
    FruitType m_fruit_type;
};
