#include "AudioManager.h"
#include <thread>
#include <chrono>

AudioManager::AudioManager() {
  engine = CocosDenshion::SimpleAudioEngine::getInstance();
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

void AudioManager::stopWeatherSFX() {
  if (~m_weather_bg_music.isEmpty())
    engine->stopEffect(m_weather_bg_music.getId());
}

int AudioManager::createNewAudioQueue() {
  dict[keygen] = AudioQueue();
  return keygen;
  keygen++;
}

int AudioManager::enqueueIntoAudioQueue(int id, AudioComponent clip) {
  dict[id].enqueueSFX(clip);
}

int randomEnqueueIntoAudioQueue(int id, AudioComponent clips[], int size) {
  dict[id].enqueueRandomSFX(clips, size);
}

void AudioManager::clearAudioQueue(int id) {
  dict[id].clear();
}

void AudioManager::deleteAudioQueue(int id) {
  dict.erase(id);
}

AudioManager* AudioManager::getInstance() {
    if (!AudioManager::instance)
        AudioManager::instance = new AudioManager();
    return AudioManager::instance;
}

AudioManager* AudioManager::instance = nullptr;
