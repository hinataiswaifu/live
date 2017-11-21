#include "Animal.h"

#include <cstdlib>

USING_NS_CC;

#define STATIONARY_INDEX 1
Animal::Animal(const std::string& sprite_frame_file,
        float pos_x,
        float pos_y,
        unsigned int index,
        float speed) :
    Live::Animate(sprite_frame_file, index, ANIMAL_FRAME_COUNT, NUM_ANIMALS),
    m_health(ANIMAL_MAX_HEALTH),
    m_speed(speed)
{
    std::stringstream ss;
    ss << "sprite_" << std::setfill('0') << std::setw(2) <<
        index + STATIONARY_INDEX << ".png";
    m_sprite = new Sprite;
    m_sprite->initWithSpriteFrameName(ss.str());
    m_sprite->setPosition(pos_x, pos_y);
}

void Animal::update() {
    bool change_state = rand() % 100 < 10;
    // should it be moving?
    if (change_state) {
        if (m_state == STANDING) { m_state = MOVING; }
        else { m_state = STANDING; }
    }

    if (m_state == STANDING) {
        Direction dir = m_orientation;
        // should it change direction?
        if (rand() % 100 < 1) {
            dir = (Direction)(rand() % NUM_DIR);
        }

        // update direction and state
        if (m_state == STANDING || dir != m_orientation) {
            m_state = MOVING;
            m_orientation = dir;
            m_sprite->stopAllActions();

            // do animation here
            animateMove();
        }
    } else {
        stopMove();
    }
}

void Animal::animateMove() {
    Animation* move_anim = new Animation;
    move_anim->initWithSpriteFrames(m_anim_map[m_orientation], ANIM_SEC);
    m_sprite->runAction(RepeatForever::create(cocos2d::Animate::create(move_anim)));
}

void Animal::stopMove() {
    m_state = STANDING;
    m_sprite->stopAllActions();
    m_sprite->setDisplayFrame(m_anim_map[m_orientation].at(STATIONARY_INDEX));
}
