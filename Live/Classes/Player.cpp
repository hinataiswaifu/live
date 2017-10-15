#include "Player.h"

USING_NS_CC;

Player::Player(const std::string& sprite_file, unsigned int grid_pos_x,
               unsigned int grid_pos_y)
    : GameObject(sprite_file, grid_pos_x, grid_pos_y) {
    m_inventory = new Inventory();
    m_hunger = 100;
    m_stamina = 100;
}

void Player::updateHunger(float diff) { m_hunger += diff; }

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

void Player::setPosition(cocos2d::Point pt) { m_sprite->setPosition(pt.x, pt.y); }
