#pragma once

#include "GameObject.h"
#include "cocos2d.h"
#include "Item.h"
#include "Inventory.h"

#define MAX_PICKUP_DISTANCE 40

#define START_X     100
#define START_Y     100
#define ANIM_SEC    0.3f
#define STATIONARY_INDEX 1  // Refers to where in the sprite frames the stationary
                            // sprite is
#define FRAME_COUNT 3
#define NUM_CHAR    4       // This indicates the number of different characters
                            // in the animation sprite sheet, required for index
                            // jumping


class Player : public GameObject {
public:
    // Define all the different directions
    typedef enum {
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT,
        DIR_UP,

        NUM_DIR
    } Direction;
    // Takes in the plist file and the initial sprite frame file index
    Player(const std::string& sprite_frame_file, unsigned int index);
    void updateHunger(float difference);
    void moveX(float x);
    void moveY(float y);
    void setPosition(cocos2d::Point point, Direction dir = DIR_DOWN);
    void move(float x, float y);
    void stopMove();
    float getHunger() const;
    float getStamina() const;
    bool pickup(Item* item);
    Item* drop(int i);
    bool use(int i);
    Inventory* get_inventory();

private:
    float m_hunger;
    Inventory* m_inventory;
    float m_stamina;
    typedef enum {
        MOVING,
        STANDING,

        NUM_STATES
    } State;
    Direction m_orientation;    // store which way the player is facing
    State m_state;              // Holds whether the player is currently moving

    cocos2d::SpriteFrameCache* m_frame_cache;
    cocos2d::Animation* m_move_anim;

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format,
           int start, int count);

    std::map<Direction, cocos2d::Vector<cocos2d::SpriteFrame*> > m_anim_map;
};
