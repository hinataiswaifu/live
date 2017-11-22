#pragma once

#include "TileParam.h"
#include "GeneratedResources.h"
#include "ResourceObstacle.h"
#include <memory>
#include <vector>

#define WATER_TILE_ID 253
#define BEACH_TILE_ID 1
#define FOREST_TILE_ID 137
#define MAP_OUTPUT_FILE_NAME "Resources/sample_map.tmx"

class MapGenerator
{
public:
    MapGenerator( int seed );
    GeneratedResources createMap(int width, int length);
private:
    void applyGradient(int width, int length, TileParam** map);
    void applyNoise(int width ,int length, TileParam** map, int seed);
    void outputToFile(int width, int length, TileParam** map);
    void generateEnvironmentFromHeight(int width ,int length, TileParam** map);
    cocos2d::Point generateSpawnPoint(int width, int length, TileParam** map);
    std::vector<ResourceObstacle*>* generateObstacles(int width, int length, TileParam** map, cocos2d::Point spawn);
    std::vector<Tree*>* generateTrees(int width, int length, TileParam** map, cocos2d::Point spawn);
};
