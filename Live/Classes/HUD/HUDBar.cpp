#include "HUDBar.h"

USING_NS_CC;

HUDBar::HUDBar(const std::string& _title, double max, int x, int y) {
  // Set properties
  HUDBar::m_title = _title;
  HUDBar::m_maxValue = max;
  HUDBar::m_currValue = max;

  // Create, customize, and add label
  m_label = Label::createWithSystemFont(m_title.c_str(), "Ubuntu", 12);
  m_label->setColor(Color3B(0, 0, 0));
  m_label->setPosition(Vec2(x, y));
  this->addChild(m_label, 1);

  // Create, customize and add the bar
  m_bar = ProgressTimer::create(Sprite::create("loadingBar.png"));
  m_bar->setType(ProgressTimer::Type::BAR);
  m_bar->setPercentage(100.0);
  m_bar->setMidpoint(Vec2(0.0f, 0.0f));
  m_bar->setBarChangeRate(Vec2(1,0));
  m_bar->setPosition(Vec2(x + 100, y));
  this->addChild(m_bar, 2);
}

void HUDBar::update() {
  // update view
  m_bar->setPercentage(m_currValue/m_maxValue*100.0);
  m_label->setString(m_title);
}

void HUDBar::updateCurr(double curr) {
  m_currValue = curr;
}

void HUDBar::updateMax(double max) {
  m_maxValue = max;
}

void HUDBar::setTitle(const std::string& _title) {
  m_title = _title;
}

HUDBar::~HUDBar() {}

void HUDBar::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
                         bool transformUpdated) {}
