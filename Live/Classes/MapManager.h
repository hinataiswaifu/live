#pragma once

#include "cocos2d.h"
#include "ResourceLayer.h"
#include <map>
#include "Player.h"
#include "WeatherManager.h"
<<<<<<< HEAD
#include "Mapgen/GeneratedResources.h"
=======
>>>>>>> 24becdae7fa8bcdf6da2e0d64c47f0590ac86d20
#include "Equipment/Arrow.h"

#define MAP_FILE_NAME "sample_map.tmx"
#define COLLISION_LAYER_NAME "Meta"

#define RESOURCE_LAYER_Z_ORDER 2       // Needs to be >1 for now due to foreground layer on demo map

class MapManager
{
public:
    MapManager();
    MapManager(GeneratedResources&);
    bool checkCollision(cocos2d::Point position);
    bool checkCollision(cocos2d::Point position, float x, float y);
    cocos2d::TMXTiledMap* getTileMap();
    cocos2d::Layer* getMap();
    void addPlayer(Player* player);
    void update(float delta);
    Item* gatherResource(cocos2d::Point position, Direction dir);
    std::vector<Arrow*>& getProjectiles();

private:
    cocos2d::TMXTiledMap *m_tile_map;
    cocos2d::TMXLayer *m_collision_layer;
    cocos2d::Point tileCoordForPosition(cocos2d::Point);
    ResourceLayer *m_resources;
    float m_map_width;
    float m_map_height;
    Layer* m_base_layer;
    WeatherManager* m_weather_manager;
    // Hack should have generic list here but who cares, ya feel?
    std::vector<Arrow*> m_projectiles;

};
