#pragma once

#include <queue>
#include "audio/include/SimpleAudioEngine.h"

class AudioManager: CocosDenshion::SimpleAudioEngine {
public:
  AudioManager() {};
  ~AudioManager();

  static AudioManager* getInstance();
  void changeBackgroundMusic(AudioComponent bgm);
  void changeWeatherSFX(AudioComponent bgm);
  void enqueueRandomSFX(AudioComponent[] clips);
  void enqueueSFX(AudioComponent);

private:
  AudioComponent m_game_bg_music;
  AudioComponent m_weather_bg_music;
  std::queue<AudioComponent> m_audio_queue;

  void dequeueSFXIfAvailable();
};
