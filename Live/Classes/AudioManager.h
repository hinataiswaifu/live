#pragma once

#include <map>
#include "audio/include/SimpleAudioEngine.h"
#include "AudioComponent.h"
#include "AudioQueue.h"

class AudioManager {
public:
  AudioManager();
  ~AudioManager();

  static AudioManager* getInstance();

  // Preload SFX for playing layer
  void preloadEffect(AudioComponent clip);

  // Stops current bg music and plays new AudioComponent
  void changeBackgroundMusic(AudioComponent bgm);

  // Stops current weather sfx and players new AudioComponent
  void changeWeatherSFX(AudioComponent bgm);

  // Stops current weather sfx if exists
  void stopWeatherSFX();

  // Creates a new audio queue to add to, returns id of the queue
  int createNewAudioQueue();

  // given an audio queue id, enqueue and play if possible
  int enqueueIntoAudioQueue(int id, AudioComponent clip);

  // given an array of AudioComponents, choose one at random and enqueue it to
  // the given audio queue
  int randomEnqueueIntoAudioQueue(int id, AudioComponent clips[], int size);

  // remove all items from a given audio queue
  void clearAudioQueue(int id);

  // get size of given audio queue
  int getAudioQueueSize(int id);

  // delete an audio queue
  void deleteAudioQueue(int id);

private:
  AudioComponent m_game_bg_music;
  AudioComponent m_weather_bg_music;

  // a dictionary of created audio queues
  std::map<int, AudioQueue> dict;
  
  // id generator
  int keygen = 0;

  static AudioManager *instance;

  // cocos audio engine
  CocosDenshion::SimpleAudioEngine *engine;
};
