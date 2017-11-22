#include "AudioManager.h"

AudioManager::AudioManager() {
  engine = CocosDenshion::SimpleAudioEngine::getInstance();
}

void AudioManager::preloadEffect(AudioComponent clip) {
  engine->preloadEffect(clip.getFilePath());
}

void AudioManager::changeBackgroundMusic(AudioComponent bgm) {
  m_game_bg_music = bgm;
  engine->stopBackgroundMusic();
  engine->preloadBackgroundMusic(bgm.getFilePath());
  engine->playBackgroundMusic(bgm.getFilePath(), true);
  engine->setBackgroundMusicVolume(0.5);
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
  m_dict[keygen] = AudioQueue();
  keygen++;
  return keygen-1;
}

void AudioManager::enqueueIntoAudioQueue(int id, AudioComponent clip) {
  m_dict[id].enqueueSFX(clip);
}

void AudioManager::randomEnqueueIntoAudioQueue(int id, AudioComponent clips[], int size) {
  m_dict[id].enqueueRandomSFX(clips, size);
}

void AudioManager::clearAudioQueue(int id) {
  m_dict[id].clear();
}

int AudioManager::getAudioQueueSize(int id) {
  return m_dict[id].size();
}

void AudioManager::deleteAudioQueue(int id) {
  clearAudioQueue(id);
  m_dict.erase(id);
}

AudioManager* AudioManager::getInstance() {
    if (!AudioManager::instance)
        AudioManager::instance = new AudioManager();
    return AudioManager::instance;
}

AudioManager* AudioManager::instance = nullptr;
