#include "AudioManager.h"

AudioManager::AudioManager() {
  engine = CocosDenshion::SimpleAudioEngine::getInstance();
  engine->setEffectsVolume(0.5);
}

void AudioManager::preloadEffect(AudioComponent *clip) {
  engine->preloadEffect(clip->getFilePath());
}

void AudioManager::changeBackgroundMusic(AudioComponent *bgm) {
  m_game_bg_music = bgm;
  engine->stopBackgroundMusic();
  engine->playBackgroundMusic(bgm->getFilePath(), true);
}

void AudioManager::changeWeatherSFX(AudioComponent *bgm) {
  if (m_weather_bg_music != nullptr)
    engine->stopEffect(m_weather_bg_music->getId());
  m_weather_bg_music = bgm;
  m_weather_bg_music->setId(engine->playEffect(bgm->getFilePath(), true));
}

// void AudioManager::enqueueRandomSFX(AudioComponent clips, int size) {
//   m_audio_queue.push(clips[rand()%size]);
//   dequeueSFXIfAvailable();
// }

void AudioManager::stopWeatherSFX() {
  if (m_weather_bg_music != nullptr)
    engine->stopEffect(m_weather_bg_music->getId());
}

void AudioManager::enqueueSFX(AudioComponent *clip) {
  m_audio_queue.push(clip);
  dequeueSFXIfAvailable();
}

void AudioManager::dequeueSFXIfAvailable() {
  if (m_audio_queue.size() == 0) {
    engine->playEffect(m_audio_queue.front()->getFilePath(), false);
    m_audio_queue.pop();
  }
}

AudioManager* AudioManager::getInstance() {
    if (!AudioManager::instance)
        AudioManager::instance = new AudioManager();
    return AudioManager::instance;
}

AudioManager* AudioManager::instance = nullptr;
