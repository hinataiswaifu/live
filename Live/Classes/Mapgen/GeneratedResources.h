#pragma once

#include "cocos2d.h"
#include "ResourceObstacle.h"
#include "Tree.h"
#include <vector>

class GeneratedResources {
public:
	GeneratedResources(std::vector<ResourceObstacle*> &o, std::vector<Tree*> &r, cocos2d::Point p) : m_obstacles(o), m_resources(r), m_spawn_point(p){}
	std::vector<ResourceObstacle*> &m_obstacles;
	std::vector<Tree*> &m_resources;
	cocos2d::Point m_spawn_point;
};