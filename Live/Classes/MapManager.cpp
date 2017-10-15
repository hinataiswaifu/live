#include "MapManager.h"

USING_NS_CC;

// Half the length of the player square's side
// Needed to form the player hitbox, since the player is defined by a center position
#define PLAYER_HALF_SIZE 12

// Default constructor
MapManager::MapManager() {
    m_tile_map = TMXTiledMap::create(MAP_FILE_NAME);
    m_collision_layer = m_tile_map->getLayer("Meta");
    m_map_width = m_tile_map->getMapSize().width * m_tile_map->getTileSize().width;
    m_map_height = m_tile_map->getMapSize().height * m_tile_map->getTileSize().height;
}

// Return reference to tile map so that it can be added to scene
TMXTiledMap* MapManager::getTileMap() { return m_tile_map; }

// Checks if a pixel coordinate lies on a collision tile
bool MapManager::checkCollision(Point position) {
    // TODO: Implement using Rect

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