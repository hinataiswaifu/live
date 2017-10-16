#include <iomanip>
#include <sstream>
#include <algorithm>

#include "Player.h"

USING_NS_CC;

Player::Player(const std::string& sprite_frame_file, unsigned int index) :
    m_hunger(DEFAULT_MAX_HUNGER),
    m_stamina(DEFAULT_MAX_STAMINA),
    m_orientation(DIR_DOWN),        // look in the down direction by default
    m_state(STANDING),
    m_max_hunger(DEFAULT_MAX_HUNGER),
    m_max_stamina(DEFAULT_MAX_STAMINA)
{
    m_inventory = new Inventory();
    m_frame_cache = SpriteFrameCache::getInstance();
    std::stringstream ss;
    ss << "sprite_" << std::setfill('0') << std::setw(2) <<
        index + STATIONARY_INDEX << ".png";
    m_frame_cache->addSpriteFramesWithFile(sprite_frame_file);
    m_sprite = new Sprite;
    m_sprite->initWithSpriteFrameName(ss.str());
    m_move_anim = new Animation;
    m_sprite->setPosition(START_X, START_Y);

    // initialize the animation frames:
    for (int dir = DIR_DOWN; dir < NUM_DIR; dir++) {
        Direction direnum = static_cast<Direction>(dir);
        for (int i = 0; i < FRAME_COUNT; i++) {
            std::stringstream ss;
            ss << "sprite_" << std::setfill('0') << std::setw(2) <<
                (dir * FRAME_COUNT * NUM_CHAR) + index + i  << ".png";
            m_anim_map[direnum].pushBack(
                    m_frame_cache->getSpriteFrameByName(ss.str()));
        }
    }
}

void Player::updateHunger(float diff) {
    m_hunger += diff;
    m_hunger = std::min(m_hunger, m_max_hunger);
    m_hunger = std::max(m_hunger, 0.0f);
}

void Player::updateStamina(float diff) {
    m_stamina += diff;
    m_stamina = std::min(m_stamina, m_max_stamina);
    m_stamina = std::max(m_stamina, 0.0f);
}

float Player::getHunger() const { return m_hunger; }

Inventory* Player::get_inventory() { return m_inventory; }

bool Player::pickup(Item* item) {
    if (distanceFrom(*item) < 20) {
        return m_inventory->pickup(item);
    }
    return false;
}

Item* Player::drop(int i) { return m_inventory->drop(i); }

bool Player::use(int i) { return m_inventory->use(i, *this); }

float Player::getStamina() const { return m_stamina; }

void Player::moveX(float x) { move(x, 0); }

void Player::moveY(float y) { move(0, y); }

void Player::move(float x, float y) {
    Vec2 loc = m_sprite->getPosition();
    m_sprite->setPosition(loc.x + x, loc.y + y);
}

void Player::setPosition(cocos2d::Point new_pos, Direction dir) {
    if (new_pos == m_sprite->getPosition()) {
        if (m_state != STANDING) stopMove();
        return;
    }
    // update direction and state
    if (m_state == STANDING || dir != m_orientation) {
        m_state = MOVING;
        m_orientation = dir;
        m_sprite->stopAllActions();

        // do animation here
        Animation* move_anim = new Animation;
        move_anim->initWithSpriteFrames(m_anim_map[m_orientation], ANIM_SEC);
        m_sprite->runAction(RepeatForever::create(Animate::create(move_anim)));
    }
    m_sprite->setPosition(new_pos);
}

void Player::stopMove() {
    m_state = STANDING;
    m_sprite->stopAllActions();
    m_sprite->setDisplayFrame(m_anim_map[m_orientation].at(STATIONARY_INDEX));
}
