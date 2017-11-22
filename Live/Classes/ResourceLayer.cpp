#include "ResourceLayer.h"
#include <ctime>
#include <cstdlib>

USING_NS_CC;

#define ANCHOR_OFFSET 32

#define MAP_WIDTH 12500
#define MAP_HEIGHT 8600

ResourceLayer::ResourceLayer() : Layer() {
    srand ( time(NULL) );

    // Note that resources can be generated on top of each other no issue,
    //      just watch out for collisions with map file's collision layer
    for(unsigned int i = 0; i < m_resources.size(); i++) {
        // TODO: Implement collision detection with main map during generation
        //  Randomly generate resource locations based on demo map
        //  Currently hardcoded to ensure no collision with water or beach areas
        int r = rand() % MAP_WIDTH;
        float x = r/10;
        r = rand() % MAP_HEIGHT;
        float y = r/10;

        //This is a hack to avoid the pond on the bottom right of the demo map
        //  as well as the player spawn location
        while((x >= 1050 && y <= 380) ||
                (std::abs(x-512)<50 && std::abs(y-364) < 50) ||
                x < ANCHOR_OFFSET || y < ANCHOR_OFFSET) {
            r = rand() % MAP_WIDTH;
            x = r/10;
            r = rand() % MAP_HEIGHT;
            y = r/10;
        }

        //Choose between rock or tree
        // TODO We need this part to be zonal
        r = rand() % 8;
        if(r == 1) {
            m_resources[i] = new ResourceObstacle("Spritesheet/mapPack_spritesheet.png", 10*64, 3*64, x, y);
        } else {
            m_resources[i] = new ResourceObstacle(x,y);
        }

        this->addChild(m_resources[i]->getSprite());

    }

    for (auto iter : m_trees) {
        this->addChild(iter->getSprite());
    }

    for (auto iter : m_animals) {
        this->addChild(iter->getSprite());
    }

}

ResourceLayer::ResourceLayer(std::vector<ResourceObstacle*> &obstacles, std::vector<Tree*> &trees, std::vector<Animal*> &animals) :
    Layer(),
    m_resources(obstacles),
    m_trees(trees),
    m_animals(animals)
{
    for(unsigned int i = 0; i < m_resources.size(); i++) {
        this->addChild(m_resources[i]->getSprite());
    }

    for(unsigned int i = 0; i < m_trees.size(); i++) {
        this->addChild(m_trees[i]->getSprite());
    }

    for(unsigned int i = 0; i < m_animals.size(); i++) {
        this->addChild(m_animals[i]->getSprite());
    }
}

bool ResourceLayer::checkCollision(cocos2d::Point position) {
    // TODO: Replace point with rect, update MainScene.cpp to pass in a rect
    Rect playerHitbox = Rect(position.x-2,position.y-24, 4, 12);
    for(int i = 0; i < m_resources.size(); i++) {
        if(m_resources[i]->checkCollision(playerHitbox)) {
            return true;
        }
    }
    for (int i = 0; i < m_trees.size(); i++) {
        if(m_trees[i]->checkCollision(playerHitbox)) {
            return true;
        }
    }
    return false;
}

Item* ResourceLayer::gather(cocos2d::Point position, Direction dir) {

    for(auto it : m_dropped_items) {
        if (it->getPosition().distance(position) < 20) {
            Item* temp = it;
            m_dropped_items.erase( std::remove(m_dropped_items.begin(),
                        m_dropped_items.end(), it));
            return temp;

        }
    }

    // Check trees
    for(int i = 0; i < m_trees.size(); i++) {
        Item* res = m_trees[i]->gather(position, dir);
        if (res) return res;
    }

    return nullptr;
}

void ResourceLayer::update(float delta) {
    for (auto iter : m_trees) {
        iter->update();
    }

    for (auto iter : m_animals) {
        iter->update(delta);
    }

    for(int i = 0; i < m_projectiles.size(); i++) {
        m_projectiles[i]->update();
        if(m_projectiles[i]->isExpired()) {
            Arrow* temp = m_projectiles[i];
            m_projectiles.erase(m_projectiles.begin() + i);
            delete temp;
        } else {
            for (auto iter = m_animals.begin(); iter != m_animals.end(); iter++) {
                if (m_projectiles[i]->distanceFrom(**iter) < 20) {
                    Animal* an = *iter;
                    m_dropped_items.push_back(new Meat(an->getPosition()));
                    m_animals.erase(iter);
                    this->addChild(m_dropped_items.back()->getSprite(), 5);
                    Arrow* temp = m_projectiles[i];
                    m_projectiles.erase(m_projectiles.begin() + i);
                    delete temp;
                    delete an;
                    break;
                }
            }
        }
    }
}

void ResourceLayer::addArrow(Arrow* arrow) {
    m_projectiles.push_back(arrow);
}
