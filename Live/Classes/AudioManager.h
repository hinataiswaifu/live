#pragma once

#include <queue>
#include "audio/include/SimpleAudioEngine.h"
#include "AudioComponent.h"

class AudioManager {
public:
  AudioManager();
  ~AudioManager();

  static AudioManager* getInstance();
  void preloadEffect(AudioComponent clip);
  void changeBackgroundMusic(AudioComponent bgm);
  void changeWeatherSFX(AudioComponent bgm);
  void stopWeatherSFX();
  void enqueueRandomSFX(AudioComponent[] clips);
  void enqueueSFX(AudioComponent clip);

private:
  AudioComponent m_game_bg_music;
  AudioComponent m_weather_bg_music;
  std::queue<AudioComponent> m_audio_queue;

  static AudioManager *instance;
  CocosDenshion::SimpleAudioEngine *engine;

  void dequeueSFXIfAvailable();
};
