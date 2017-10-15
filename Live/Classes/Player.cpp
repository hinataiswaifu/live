#include "Player.h"

USING_NS_CC;

Player::Player(const std::string& sprite_file, unsigned int grid_pos_x,
               unsigned int grid_pos_y, int sprite_x, int sprite_y)
    : GameObject(sprite_file, grid_pos_x, grid_pos_y, sprite_x, sprite_y) {
    m_hunger = 100;
    m_stamina = 100;
}

void Player::updateHunger(float diff) { m_hunger += diff; }

float Player::getHunger() const { return m_hunger; }

bool Player::pickup( Item *item ) {
    if( distanceFrom(*item) < 20 ) {
        return inventory.pickup(item);
    }
    return false;
}

bool Player::drop(int i) {
    cocos2d::Vec2 pos = getPosition();
    return inventory.drop(i, pos.x, pos.y);
}

bool Player::use(int i) { return inventory.use(i, *this); }

float Player::getStamina() const { return m_stamina; }

void Player::moveX(float x) { move(x, 0); }

void Player::moveY(float y) { move(0, y); }

void Player::move(float x, float y) {
    Vec2 loc = m_sprite->getPosition();
    m_sprite->setPosition(loc.x + x, loc.y + y);
}
