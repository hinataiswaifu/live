#pragma once

#include <queue>
#include "AudioComponent.h"
#include "audio/include/SimpleAudioEngine.h"

class AudioQueue {
public:
  AudioQueue();

  // enqueue it the given AudioComponent
  void enqueueSFX(AudioComponent clip);

  // clear the queue
  void clear();

  // get size of queue
  int size();
private:
  std::queue<AudioComponent> m_audio_queue;

  // dequeue and play AudioComponent if there exists one
  void dequeueSFXIfAvailable();

  // dequeue and play AudioComponent on a separate thread, and once
  // it is finished playing, play the next AudioComponent in the queue
  // if exists
  void dequeueSFX();

  CocosDenshion::SimpleAudioEngine *engine;
};
