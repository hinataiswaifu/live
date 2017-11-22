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

void Animal::update(float delta) {
    bool change_state = (rand() % 10000) < 5;
    // should it be moving?
    if (change_state) {
        if (m_state == STANDING) {
            m_state = MOVING;
            m_orientation = (Direction)(rand() % NUM_DIR);

            // do animation here
            animateMove();
        } else {
            m_state = STANDING;
        }
    }

    if (m_state == MOVING) {
        Direction dir = m_orientation;
        // should it change direction?
        if (rand() % 1000 < 2) {
            dir = (Direction)(rand() % NUM_DIR);
        }

        // update direction and state
        if (dir != m_orientation) {
            m_orientation = dir;
            m_sprite->stopAllActions();
            animateMove();
        }

        Point cur_pos = getPosition();
        if (m_orientation == DIR_DOWN) {
            m_sprite->setPosition(cur_pos.x, cur_pos.y - (delta*m_speed));
        } else if (m_orientation == DIR_UP) {
            m_sprite->setPosition(cur_pos.x, cur_pos.y + (delta*m_speed));
        } else if (m_orientation == DIR_LEFT) {
            m_sprite->setPosition(cur_pos.x - (delta*m_speed), cur_pos.y);
        } else if (m_orientation == DIR_RIGHT) {
            m_sprite->setPosition(cur_pos.x + (delta*m_speed), cur_pos.y);
        }
    } else {
        stopMove();
    }

    setZOrder(-(getPosition().y - ANIMAL_SPRITE_HEIGHT / 2));
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
