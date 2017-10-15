#include "HUDBar.h"

USING_NS_CC;

HUDBar::HUDBar(const std::string& title, double max, int x, int y, Sprite* bar_sprite) {
    // Set properties
    HUDBar::m_title = title;
    HUDBar::m_max_value = max;
    HUDBar::m_curr_value = max;

    // Create, customize, and add label
    // m_label = Label::createWithSystemFont(m_title.c_str(), "Ubuntu", 12);
    m_label = Label::createWithTTF(m_title, "fonts/emulogic.ttf", 12);
    m_label->setColor(Color3B(255, 255, 255));
    m_label->setPosition(Vec2(x, y));
    this->addChild(m_label, 1);

    // Create, customize and add the bar
    m_bar = ProgressTimer::create(bar_sprite);
    m_bar->setType(ProgressTimer::Type::BAR);
    m_bar->setPercentage(100.0);
    m_bar->setMidpoint(Vec2(0.0f, 0.0f));
    m_bar->setBarChangeRate(Vec2(1, 0));
    m_bar->setPosition(Vec2(x + 201, y));
    this->addChild(m_bar, 2);

    // Add bar background
    Sprite* bg_bar_sprite = Sprite::create("UI/spr_bar_background.png");
    bg_bar_sprite->setPosition(Vec2(x + 200, y));
    addChild(bg_bar_sprite, 1);


}

void HUDBar::update() {
    // update view
    m_bar->setPercentage(m_curr_value / m_max_value * 100.0);
    m_label->setString(m_title);
}

void HUDBar::updateCurr(double curr) { m_curr_value = curr; }

void HUDBar::updateMax(double max) { m_max_value = max; }

void HUDBar::setTitle(const std::string& title) { m_title = title; }

HUDBar::~HUDBar() {}

void HUDBar::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                  bool transformUpdated) {}
