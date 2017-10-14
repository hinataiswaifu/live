#include "HUDbar.h"

USING_NS_CC;

HUDBar::HUDBar(const std::string& _title, double max, int x, int y) {
  HUDBar::m_title = _title;
  HUDBar::m_maxValue = max;
  HUDBar::m_currValue = max;
  _label = Label::createWithSystemFont(_title.c_str(), "Ubuntu", 12);
  _label->setColor(cocos2d::Color3B(0, 0, 0));
  _label->setPosition(cocos2d::Vec2(x, y));

  this->addChild(_label, 1);

  _bar = ProgressTimer::create(Sprite::create("loadingBar.png"));
  _bar->setType(ProgressTimer::Type::BAR);
  _bar->setPercentage(100.0);
  _bar->setPosition(cocos2d::Vec2(x + 100, y));
  this->addChild(_bar, 2);
}

HUDBar::~HUDBar() {}

void HUDBar::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
                         bool transformUpdated) {}
