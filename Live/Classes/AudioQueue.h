#pragma once

#include <queue>
#include "AudioComponent.h"
#include "audio/include/SimpleAudioEngine.h"

class AudioQueue {
public:
  AudioQueue();

  void enqueueRandomSFX(AudioComponent clips[], int size);
  void enqueueSFX(AudioComponent clip);
  void clear();
  int size();
private:
  std::queue<AudioComponent> m_audio_queue;
  void dequeueSFXIfAvailable();
  void dequeueSFX();

  CocosDenshion::SimpleAudioEngine *engine;
};
