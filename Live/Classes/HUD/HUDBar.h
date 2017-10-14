#ifndef  _HUD_BAR_
#define  _HUD_BAR_

#include "cocos2d.h"

class HUDBar : public cocos2d::Layer
{
    public:
        HUDBar(const std::string& _title, double max, int x, int y);
        ~HUDBar();

        static HUDBar* createLayer(const std::string& _title, double max);
        void initOptions(const std::string& _title);

        virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);
        void updateMax(double max);
        void updateCurr(double curr);

        void setTitle(const std::string& _title);

        void update();

    private:
        cocos2d::Label* m_label;
        cocos2d::ProgressTimer* m_bar;
        std::string m_title;
        double m_maxValue;
        double m_currValue;
};

#endif // _MESSAGEHUD_HPP_
