#pragma once

#include "cocos2d.h"

class HUDBar : public cocos2d::Layer {
public:
    HUDBar(const std::string& _title, double max, int x, int y);
    ~HUDBar();

    // static method to create instance of HUDBar
    static HUDBar* createLayer(const std::string& title, double max);

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    // Setters
    void updateMax(double max);
    void updateCurr(double curr);
    void setTitle(const std::string& _title);

    // Update views
    void update();

private:
    // Components of a HUDBar
    cocos2d::Label* m_label;
    cocos2d::ProgressTimer* m_bar;

    // Stored properties
    std::string m_title;
    double m_max_value;
    double m_curr_value;
};
