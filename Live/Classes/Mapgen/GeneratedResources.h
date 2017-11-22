#pragma once

#include "cocos2d.h"
#include "ResourceObstacle.h"
#include "Tree.h"
#include "Animal.h"
#include <vector>

class GeneratedResources {
public:
	GeneratedResources(std::vector<ResourceObstacle*> &o, std::vector<Tree*> &r, std::vector<Animal*> &a, cocos2d::Point p) : m_obstacles(o), m_resources(r), m_animals(a), m_spawn_point(p){}
	std::vector<ResourceObstacle*> &m_obstacles;
	std::vector<Tree*> &m_resources;
	std::vector<Animal*> &m_animals;
	cocos2d::Point m_spawn_point;
};