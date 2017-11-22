#include <iomanip>
#include <sstream>
#include <algorithm>

#include "Player.h"

USING_NS_CC;

Player::Player(const std::string& sprite_frame_file, unsigned int index, Mapping mapping) :
    Live::Animate(sprite_frame_file, index, FRAME_COUNT, NUM_CHAR),
    m_hunger(DEFAULT_MAX_HUNGER),
    m_stamina(DEFAULT_MAX_STAMINA),
    m_max_hunger(DEFAULT_MAX_HUNGER),
    m_max_stamina(DEFAULT_MAX_STAMINA),
    m_mapping(mapping)
{
    m_equip = nullptr;
    m_action_lock = false;
    m_inventory = new Inventory();
    std::stringstream ss;
    ss << "sprite_" << std::setfill('0') << std::setw(2) <<
        index + STATIONARY_INDEX << ".png";
    m_sprite = new Sprite;
    m_sprite->initWithSpriteFrameName(ss.str());
    m_sprite->setPosition(START_X, START_Y);
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
    // FIXME the logic for picking up game objects should be in map manager
    if (distanceFrom(*item) < PICKUP_RADIUS) {
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
    if(m_equip) {
        m_equip->move(x, y);
    }
}

// We suck this should be GameObject* or something
Arrow* Player::action() {
    if(m_equip) {
        m_action_lock = true;
        return m_equip->action(*this);
    }
}

void Player::releaseAction() {
    m_action_lock = false;
}

void Player::equip(Equipment* equip) {
    // TODO potential memory leak here
    m_equip = equip;
    getSprite()->getParent()->addChild(m_equip->getSprite());
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
        animateMove();
    }
    m_sprite->setPosition(new_pos);

    if(m_equip) {
        m_equip->updateOnMove(*this, new_pos);
    }
}

void Player::animateMove() {
    Animation* move_anim = new Animation;
    move_anim->initWithSpriteFrames(m_anim_map[m_orientation], ANIM_SEC);
    m_sprite->runAction(RepeatForever::create(cocos2d::Animate::create(move_anim)));
}

void Player::stopMove() {
    m_state = STANDING;
    m_sprite->stopAllActions();
    m_sprite->setDisplayFrame(m_anim_map[m_orientation].at(STATIONARY_INDEX));
}

Rect Player::getHitbox() {
    return Rect(getPosition().x-PLAYER_HITBOX_WIDTH/2,getPosition().y-PLAYER_HITBOX_HEIGHT/2, PLAYER_HITBOX_WIDTH, PLAYER_HITBOX_HEIGHT);
}

Direction Player::getOrientation() {
    return m_orientation;
}
