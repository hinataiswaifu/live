
#include "Player.h"

USING_NS_CC;

Player::Player(const std::string& sprite_file, unsigned int grid_pos_x,
        unsigned int grid_pos_y, int sprite_x, int sprite_y)
    : GameObject(sprite_file, grid_pos_x, grid_pos_y, sprite_x, sprite_y) {

    m_health = 100;
    m_stamina = 100;
}

void Player::updateHealth(float diff) {
    m_health += diff;
}

float Player::getHealth() const {
    return m_health;
}

void Player::moveX(float x) {
    move(x, 0);
}

void Player::moveY(float y) {
    move(0, y);
}


void Player::move(float x, float y) {
    Vec2 loc = m_sprite->getPosition();
    m_sprite->setPosition(loc.x + x, loc.y + y);
}
