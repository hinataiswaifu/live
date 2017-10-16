#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "cocos2d.h"
#include "ResourceLayer.h"
#include <map>
#include "Player.h"

#define MAP_FILE_NAME "sample_map.tmx"
#define COLLISION_LAYER_NAME "Meta"

class MapManager
{
public:
    MapManager();

    bool checkCollision(cocos2d::Point position);
    bool checkCollision(cocos2d::Point position, float x, float y);
    cocos2d::TMXTiledMap* getTileMap();
    void addPlayer(Player* player);

private:
    cocos2d::TMXTiledMap *m_tile_map;
    cocos2d::TMXLayer *m_collision_layer;
    cocos2d::Point tileCoordForPosition(cocos2d::Point);
    ResourceLayer *m_resources;
    float m_map_width; 
    float m_map_height; 
};

#endif // __MAIN_SCENE_H__
