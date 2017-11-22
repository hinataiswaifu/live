#pragma once

#include <iomanip>
#include <sstream>

#include "Direction.h"

#define ANIM_SEC    0.2f

namespace Live {
class Animate {
protected:
    cocos2d::SpriteFrameCache* m_frame_cache;
    cocos2d::Animation* m_move_anim;

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format,
           int start, int count);

    std::map<Direction, cocos2d::Vector<cocos2d::SpriteFrame*> > m_anim_map;
    Direction m_orientation;    // store which way the player is facing

    typedef enum {
        MOVING,
        STANDING,

        NUM_STATES
    } State;
    State m_state;              // Holds whether the player is currently moving

    // only children can use the constructor
    /**
     * index            Index of the sprite we want to load
     * frame_count      Number of frames per animation cycle
     * num_characters   Number of characters in the sprite sheet
     */
    Animate(const std::string& sprite_frame_file, unsigned int index,
            unsigned int frame_count,
            unsigned int num_characters)
        : m_orientation(DIR_DOWN), m_state(STANDING)
    {

        m_frame_cache = cocos2d::SpriteFrameCache::getInstance();
        m_frame_cache->addSpriteFramesWithFile(sprite_frame_file);
        m_move_anim = new cocos2d::Animation;

        // initialize the animation frames:
        for (int dir = DIR_DOWN; dir < NUM_DIR; dir++) {
            Direction direnum = static_cast<Direction>(dir);
            for (unsigned int i = 0; i < frame_count; i++) {
                std::stringstream ss;
                ss << "sprite_" << std::setfill('0') << std::setw(2) <<
                    (dir * frame_count * num_characters) + index + i  << ".png";
                m_anim_map[direnum].pushBack(
                        m_frame_cache->getSpriteFrameByName(ss.str()));
            }
        }
    }

    // let children overwrite these functions
    virtual void animateMove() = 0;
    virtual void stopMove() = 0;
};
}
