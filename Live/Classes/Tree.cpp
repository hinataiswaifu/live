#include "Tree.h"
#include "GameTimer.h"
#include <iostream>
#include <cstdlib>

USING_NS_CC;

// TODO This should be implemented in GameObject
Tree::Tree(const std::string& sprite_file, float pos_x, float pos_y)
{
    m_sprite = Sprite::create(sprite_file);
    m_sprite->setScale(TREE_SCALE_FACTOR);
    setPosition(pos_x, pos_y);

    // TODO This part should be added to the parent class, since it generically
    // generates a hit box around an object
    const Rect dim = m_sprite->getTextureRect();
    m_width = (dim.getMaxX() - dim.getMinX()) * TREE_SCALE_FACTOR;
    m_height = (dim.getMaxY() - dim.getMinY()) * TREE_SCALE_FACTOR;
    m_hitbox = Rect(pos_x-(m_width/2),pos_y - m_height/2,
            m_width, m_height/4);		// Set hitbox to lower quarter of sprite

    m_last_day = GameTimer::getDaysElapsed();
    m_fruit_type = Tree::FruitType::CHERRY;

    setZOrder(-(pos_y-(m_height/2)));
}

Tree::Tree (const std::string& sprite_file, float pos_x, float pos_y, Tree::FruitType ftype) : Tree(sprite_file, pos_x, pos_y)
{
    m_fruit_type = ftype;
}

void Tree::update() {
    // randomly places a new fruit on the tree
    if ((rand() % (AVERAGE_DAY*2) < (GameTimer::getDaysElapsed() - m_last_day)) &&
            m_items.size() < MAX_FRUITS) {
        // generate a fruit
        int x = rand() % (m_width - FRUIT_PADDING_X);
        int y = rand() % (m_height - FRUIT_PADDING_Y);

        if(m_fruit_type == Tree::CHERRY) {
             m_items.push(new Cherry(x + FRUIT_PADDING_X, y + FRUIT_PADDING_Y));
        } else {
             m_items.push(new Apple(x + FRUIT_PADDING_X, y + FRUIT_PADDING_Y));
        }

        m_sprite->addChild(m_items.back()->getSprite());
    }
    m_last_day = GameTimer::getDaysElapsed();
}

<<<<<<< HEAD
// Gather resource, given that you are facing the obstacle
Item* Tree::gather(cocos2d::Point pt, Direction dir) {

    // Create a point in front of the player
    Point ray = pt;

    if(m_fruits.size() <= 0) {
        return nullptr;
    }

    if(dir == DIR_LEFT) {
        ray += Point(-6, 0);
    } else if(dir == DIR_RIGHT) {
        ray += Point(6, 0);
    } else if(dir == DIR_DOWN) {
        ray += Point(0, -6);
    } else if(dir == DIR_UP) {
        ray += Point(0, 6);
    }

    if(m_hitbox.containsPoint(ray)) {
        Food* pickup = m_fruits.front();
        m_fruits.pop();
        //Change sprite
        return pickup;
    }
    return nullptr;
}

=======
>>>>>>> 1b96fb2... Squashed commits manually for bow and arrow
Tree::~Tree() {
    while (!m_items.empty()) {
        m_items.pop();
    }
    delete m_sprite;
}
