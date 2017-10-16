#pragma once

#include "cocos2d.h"
#include "GameTimer.h"

class HUDTimer : public cocos2d::Layer {
public:
    HUDTimer();
    ~HUDTimer();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    // Update views
    void update();

private:
    // Components of a HUDTimer
    cocos2d::Label* m_label;
};
