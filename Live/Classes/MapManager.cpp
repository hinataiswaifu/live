#include "MapManager.h"

USING_NS_CC;

// Default constructor
MapManager::MapManager() {

    m_tile_map = TMXTiledMap::create(MAP_FILE_NAME);
    m_collision_layer = m_tile_map->getLayer("Meta");
    m_map_width = m_tile_map->getMapSize().width * m_tile_map->getTileSize().width;
    m_map_height = m_tile_map->getMapSize().height * m_tile_map->getTileSize().height;
    m_resources = new ResourceLayer();
    m_tile_map->addChild(m_resources, RESOURCE_LAYER_Z_ORDER);

    m_base_layer = Layer::create();
    // make base layer the same size as the map
    m_base_layer->setContentSize(Size(m_map_width, m_map_height));
    m_base_layer->addChild(m_tile_map, -1);

    m_weather_manager = new WeatherManager(m_map_width, m_map_height);
    m_base_layer->addChild(m_weather_manager->getWeatherLayer());
}

MapManager::MapManager(GeneratedResources& resources) {
    m_tile_map = TMXTiledMap::create(MAP_FILE_NAME);
    m_collision_layer = m_tile_map->getLayer("Meta");
    m_map_width = m_tile_map->getMapSize().width * m_tile_map->getTileSize().width;
    m_map_height = m_tile_map->getMapSize().height * m_tile_map->getTileSize().height;
    m_resources = new ResourceLayer(resources.m_obstacles, resources.m_resources, resources.m_animals);
    m_tile_map->addChild(m_resources, RESOURCE_LAYER_Z_ORDER);

    m_base_layer = Layer::create();
    // make base layer the same size as the map
    m_base_layer->setContentSize(Size(m_map_width, m_map_height));
    m_base_layer->addChild(m_tile_map, -1);

    m_weather_manager = new WeatherManager(m_map_width, m_map_height);
    m_base_layer->addChild(m_weather_manager->getWeatherLayer());
}

// Return reference to tile map so that it can be added to scene
TMXTiledMap* MapManager::getTileMap() { return m_tile_map; }

Layer* MapManager::getMap() { return m_base_layer; }

void MapManager::addPlayer(Player* player) {
    m_resources->addChild(player->getSprite());
    m_weather_manager->addPlayer(player);
}

// Checks if a pixel coordinate lies on a collision tile
bool MapManager::checkCollision(Point position) {
    // TODO: Implement using Rect

    if(m_resources->checkCollision(position)) {
        return true;
    }

    // Create a hitbox using 4 corners around the position
    Point* hitbox[4];
    hitbox[0] = new Point(position.x + PLAYER_HALF_SIZE, position.y + PLAYER_HALF_SIZE);
    hitbox[1] = new Point(position.x - PLAYER_HALF_SIZE, position.y + PLAYER_HALF_SIZE);
    hitbox[2] = new Point(position.x + PLAYER_HALF_SIZE, position.y - PLAYER_HALF_SIZE);
    hitbox[3] = new Point(position.x - PLAYER_HALF_SIZE, position.y - PLAYER_HALF_SIZE);

    bool collision = false;

    // Iterate through hitbox corners
    for (int i = 0; i < 4; i++) {
        // Check if the hitbox lies outside map boundaries
        if (hitbox[i]->x >= m_map_width || hitbox[i]->y >= m_map_height ||
            hitbox[i]->x < 0 || hitbox[i]->y < 0) {
            collision = true;
            break;
        }

        // Find associated tile in collision layer of the map
        Point tileCoord = this->tileCoordForPosition(*hitbox[i]);
        unsigned int tileGid = m_collision_layer->getTileGIDAt(tileCoord);

        // Collision tile not found
        if (tileGid != 0) {
            collision = true;
            break;
        }
    }

    // Free memory
    for (int i = 0; i < 4; i++) {
        delete hitbox[i];
    }

    return collision;
}

// Overloaded checkCollision applies an x and y movement to the input position before
// checking for collision
bool MapManager::checkCollision(Point position, float x, float y) {
    Point new_position = position + Point(x, y);
    return checkCollision(new_position);
}

// Helper method converts a position in pixels to a tile position
Point MapManager::tileCoordForPosition(Point position) {
    int x = position.x / m_tile_map->getTileSize().width;
    int y = ((m_tile_map->getMapSize().height * m_tile_map->getTileSize().height) -
             position.y) /
            m_tile_map->getTileSize().height;
    return Point(x, y);
}

Item* MapManager::gatherResource(cocos2d::Point position, Direction dir) {
    return m_resources->gather(position, dir);
}

void MapManager::update(float delta) {
    // delta to be used later on for adding dynamic effects WOW!
    m_resources->update();

    m_weather_manager->update();
}
