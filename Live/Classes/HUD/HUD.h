#ifndef  _HUD_HPP_
#define  _HUD_HPP_

#include "cocos2d.h"
#include "HUDBar.h"
#include "Player.h"

class HUD : public cocos2d::Layer
{
    public:
        HUD(Player* player);
        ~HUD();

        static HUD* createLayer(Player* player);
        void initOptions();

        virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

        void update();
    private:
        HUDBar* m_hungerBar;
        HUDBar* m_staminaBar;

        Player* m_player;
};

#endif // _HUD_HPP_
