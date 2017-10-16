#pragma once

#include "cocos2d.h"

#define MSG_WIDTH 590
#define MSG_PADDING 60

class HUDMessage : public cocos2d::Layer {
public:
    HUDMessage(const std::string& message);
    ~HUDMessage();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    // Setters
    void setMessage(const std::string& message);

    // Update views
    void update();

    // Show/Dismiss component
    void dismiss();
    void show();

private:
    // Components of a HUDMessage
    cocos2d::Label* m_label;

    // Stored properties
    std::string m_message;
};
