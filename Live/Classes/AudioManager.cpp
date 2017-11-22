#include "AudioManager.h"
#include <thread>
#include <chrono>

AudioManager::AudioManager() {
  engine = CocosDenshion::SimpleAudioEngine::getInstance();
  engine->setEffectsVolume(0.5);
}

void AudioManager::preloadEffect(AudioComponent clip) {
  engine->preloadEffect(clip.getFilePath());
}

void AudioManager::changeBackgroundMusic(AudioComponent bgm) {
  m_game_bg_music = bgm;
  engine->stopBackgroundMusic();
  engine->preloadEffect(bgm.getFilePath());
  engine->playBackgroundMusic(bgm.getFilePath(), true);
}

void AudioManager::changeWeatherSFX(AudioComponent bgm) {
  if (~m_weather_bg_music.isEmpty())
    engine->stopEffect(m_weather_bg_music.getId());
  m_weather_bg_music = bgm;
  m_weather_bg_music.setId(engine->playEffect(bgm.getFilePath(), true));
}

void AudioManager::enqueueRandomSFX(AudioComponent clips[], int size) {
  m_audio_queue.push(clips[rand()%size]);
  dequeueSFXIfAvailable();
}

void AudioManager::stopWeatherSFX() {
  if (~m_weather_bg_music.isEmpty())
    engine->stopEffect(m_weather_bg_music.getId());
}

void AudioManager::enqueueSFX(AudioComponent clip) {
  m_audio_queue.push(clip);
  dequeueSFXIfAvailable();
}

void AudioManager::dequeueSFXIfAvailable() {
  if (m_audio_queue.size() == 1) {
    std::thread t1(&AudioManager::dequeueSFX, this);
    t1.join();
  }
}

void AudioManager::dequeueSFX() {
  engine->playEffect(m_audio_queue.front().getFilePath(), false);
  std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_audio_queue.front().getLength()));
  m_audio_queue.pop();
  if (!m_audio_queue.empty()) {
    dequeueSFX();
  }
}

AudioManager* AudioManager::getInstance() {
    if (!AudioManager::instance)
        AudioManager::instance = new AudioManager();
    return AudioManager::instance;
}

AudioManager* AudioManager::instance = nullptr;
