#ifndef  _MESSAGEHUD_HPP_
#define  _MESSAGEHUD_HPP_

#include "cocos2d.h"

class MessageHUD : public cocos2d::LayerColor
{
    public:
        MessageHUD();
        ~MessageHUD();

        static MessageHUD* createLayer(const std::string& _message);
        void initOptions(const std::string& _message);

        virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

        inline virtual cocos2d::Label* getMessageLabel() { return _messageLabel; };

    private:
        cocos2d::Label* _messageLabel;
};

#endif // _MESSAGEHUD_HPP_
