#ifndef  _HUD_HPP_
#define  _HUD_HPP_

#include "cocos2d.h"
#include "HUDBar.h"
#include "Player.h"

class HUD : public cocos2d::Layer
{
    public:
        // HUD stores a reference to game objects that have the potential to update the HUD
        HUD(Player* player);

        ~HUD();

        virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

        // Update HUD based on current state of members
        void update();
    private:
        // Helper method to initialize components
        void initComponents();

        // Bars to display
        HUDBar* m_hungerBar;
        HUDBar* m_staminaBar;

        // Stored references to game objects
        Player* m_player;
};

#endif // _HUD_HPP_
