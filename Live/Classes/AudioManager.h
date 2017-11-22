#pragma once

#include "audio/include/SimpleAudioEngine.h"
#include "AudioComponent.h"
#include "AudioQueue.h"
#include <map>

class AudioManager {
public:
  AudioManager();
  ~AudioManager();

  static AudioManager* getInstance();
  void preloadEffect(AudioComponent clip);
  void changeBackgroundMusic(AudioComponent bgm);
  void changeWeatherSFX(AudioComponent bgm);
  void stopWeatherSFX();

  int createNewAudioQueue();
  int enqueueIntoAudioQueue(int id, AudioComponent clip);
  int randomEnqueueIntoAudioQueue(int id, AudioComponent clips[], int size);
  void clearAudioQueue(int id);
  void deleteAudioQueue(int id);

private:
  AudioComponent m_game_bg_music;
  AudioComponent m_weather_bg_music;
  std::map<int, AudioQueue> dict;
  int keygen = 0;

  static AudioManager *instance;
  CocosDenshion::SimpleAudioEngine *engine;
};
