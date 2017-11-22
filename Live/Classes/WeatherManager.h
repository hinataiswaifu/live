#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "GameTimer.h"

class WeatherManager
{
public:
    enum Weather { SUNNY, RAINING, SNOWING };
    WeatherManager(float height, float width);
    cocos2d::Layer* getWeatherLayer();
    void setWeather(Weather weather);
    Weather getWeather();
    void update();
    void addPlayer(Player* p);
private:
    cocos2d::Layer* m_weather_layer;
    Weather m_curr_weather;
    GameTimer::DayPhase m_prev_phase;
    cocos2d::ParticleSystem* m_particle_generator;
    cocos2d::LayerColor* m_overlay;
    cocos2d::LayerColor* m_night_overlay;
    int m_day;
    Player* m_player;
};
