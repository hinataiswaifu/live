#include "WeatherManager.h"
#include "GameTimer.h"
#include "AudioManager.h"

USING_NS_CC;

WeatherManager::WeatherManager(float width, float height) {
    m_weather_layer = Layer::create();
    m_weather_layer->setContentSize(Size(width, height));
    m_curr_weather = SUNNY;
    m_day = 0;
}

void WeatherManager::setWeather(WeatherManager::Weather weather) {

    if(m_curr_weather != weather) {
        m_curr_weather = weather;
        m_weather_layer->removeChild(m_particle_generator);
        m_weather_layer->removeChild(m_overlay);

        if(weather == RAINING) {
            m_particle_generator = ParticleRain::createWithTotalParticles(100000);
            m_particle_generator->setSpeed(400.);
            m_particle_generator->setDuration(-1);
            m_particle_generator->setEndSize(20);
            m_particle_generator->setEndSize(25);
            m_particle_generator->setSourcePosition(Vec2(0, m_weather_layer->getContentSize().height));
            m_weather_layer->addChild(m_particle_generator);

            m_overlay = cocos2d::LayerColor::create(Color4B(53, 53, 53, 100));
            m_overlay->setContentSize(m_weather_layer->getContentSize());
            m_weather_layer->addChild(m_overlay);
        } else if(weather == SNOWING){
            m_particle_generator = ParticleSnow::createWithTotalParticles(100000);
            m_particle_generator->setSpeed(200.);
            m_particle_generator->setDuration(-1);
            m_particle_generator->setSourcePosition(Vec2(0, m_weather_layer->getContentSize().height));
            m_weather_layer->addChild(m_particle_generator);

            m_overlay = cocos2d::LayerColor::create(Color4B(153, 153, 153, 100));
            m_overlay->setContentSize(m_weather_layer->getContentSize());
            m_weather_layer->addChild(m_overlay);
        }
    }
};

Layer* WeatherManager::getWeatherLayer() {
    return m_weather_layer;
}

void WeatherManager::update() {
    int day = GameTimer::getInstance()->getDaysElapsed();
    if(day % 2 == 0 && m_day < day) {
        m_day = day;
        switch(day % 3) {
        case 0:
          setWeather(SUNNY);
          AudioManager::getInstance()->changeWeatherSFX(AudioComponent("Audio/sunny.mp3", 264));
          break;
        case 1:
          setWeather(RAINING);
          AudioManager::getInstance()->changeWeatherSFX(AudioComponent("Audio/rain.mp3", 110));
          break;
        case 2:
          setWeather(SNOWING);
          AudioManager::getInstance()->changeWeatherSFX(AudioComponent("Audio/blizzard.mp3", 121));
          break;
        default:
          AudioManager::getInstance()->stopWeatherSFX();
        }
    }
}
