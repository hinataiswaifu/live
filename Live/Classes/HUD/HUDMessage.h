#pragma once

#include "cocos2d.h"
#include <queue>

#define MSG_WIDTH 590
#define MSG_PADDING 60

class HUDMessage : public cocos2d::Layer {
public:
    HUDMessage();
    ~HUDMessage();

    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                      bool transformUpdated);

    // Setters
    void enqueueMessage(const std::string& message);

    // Dequeue and display message
    void readMessage();

    // Update views
    void update();

    // Show/Dismiss component
    void dismissMessage();
    void show();

private:
    // Components of a HUDMessage
    cocos2d::Label* m_label;
    cocos2d::Sprite* m_background;

    // Stored properties
    std::queue<std::string> m_message_queue;
};
