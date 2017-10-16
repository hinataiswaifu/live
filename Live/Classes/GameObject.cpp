#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(const std::string sprite_file, unsigned int grid_pos_x,
                       unsigned int grid_pos_y)
    : m_sprite_file(sprite_file), m_grid_pos_x(grid_pos_x), m_grid_pos_y(grid_pos_y) {
    m_sprite = NULL;
}

void GameObject::setPosition(float x, float y) { m_sprite->setPosition(x, y); }

void GameObject::setPosition(Vec2 pos) { m_sprite->setPosition(pos); }

Vec2 GameObject::getPosition() const { return m_sprite->getPosition(); }

void GameObject::setZOrder(float z) {
    m_sprite->setZOrder(z);
}

Sprite* GameObject::newSprite() {
    m_sprite = Sprite::create(m_sprite_file,
                              Rect(m_grid_pos_x * SPRITE_DIM, m_grid_pos_y * SPRITE_DIM,
                                   SPRITE_DIM, SPRITE_DIM));
    m_sprite->setScale(2.0);
    return m_sprite;
}

Sprite* GameObject::newSprite(int width, int length) {
    m_sprite = Sprite::create(m_sprite_file,
                              Rect(m_grid_pos_x, m_grid_pos_y,
                                   width, length));
    return m_sprite;
}

Sprite* GameObject::getSprite() { return m_sprite; }

const float GameObject::distanceFrom(const GameObject& other) {
    // TODO: Note we don't actually have a sense of where objects are on the map
    // as of right now, so we only check the position of their sprites.
    // Once we having a working map, we should either change how this function calculates
    // distance, or the vec getPosition returns
    return getPosition().distance(other.getPosition());
}

GameObject::~GameObject() {}  // m_sprite deleted by game instance