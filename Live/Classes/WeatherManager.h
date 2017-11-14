#pragma once

#include "cocos2d.h"

class WeatherManager
{
public:
    enum Weather { SUNNY, RAINING, SNOWING };
    WeatherManager(float height, float width);
    cocos2d::Layer* getWeatherLayer();
    void setWeather(Weather weather);
    void update();
private:
    cocos2d::Layer* m_weather_layer;
    Weather m_curr_weather;
    cocos2d::ParticleSystem* m_particle_generator;
    cocos2d::LayerColor* m_overlay;
    int m_day;
};
