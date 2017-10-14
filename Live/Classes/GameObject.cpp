#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(const std::string& sprite_file, unsigned int grid_pos_x,
                       unsigned int grid_pos_y, int sprite_x, int sprite_y) {
    m_sprite = Sprite::create(
        sprite_file,
        Rect(grid_pos_x * SPRITE_DIM, grid_pos_y * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM));

    m_sprite->setPosition(sprite_x, sprite_y);
    m_sprite->setScale(2.0);
}

void GameObject::setPosition(float x, float y) { m_sprite->setPosition(x, y); }

Vec2 GameObject::getPosition() const { return m_sprite->getPosition(); }

Sprite* GameObject::getSprite() { return m_sprite; }

const float GameObject::distanceFrom(const GameObject &other) {
    // TODO: Note we don't actually have a sense of where objects are on the map
    // as of right now, so we only check the position of their sprites. 
    // Once we having a working map, we should either change how this function calculates
    // distance, or the vec getPosition returns
    return getPosition().distance(other.getPosition());
}

GameObject::~GameObject () {
    delete m_sprite;
}