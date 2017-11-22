#include <thread>
#include <chrono>
#include "AudioQueue.h"

AudioQueue::AudioQueue() {
  engine = CocosDenshion::SimpleAudioEngine::getInstance();
}

void AudioQueue::enqueueRandomSFX(AudioComponent clips[], int size) {
  m_audio_queue.push(clips[rand()%size]);
  dequeueSFXIfAvailable();
}

void AudioQueue::enqueueSFX(AudioComponent clip) {
  m_audio_queue.push(clip);
  dequeueSFXIfAvailable();
}

void AudioQueue::clear() {
  while (!m_audio_queue.empty()) {
    m_audio_queue.pop();
  }
}

int AudioQueue::size() {
  return m_audio_queue.size();
}

void AudioQueue::dequeueSFXIfAvailable() {
  if (m_audio_queue.size() == 1) {
    std::thread t1(&AudioQueue::dequeueSFX, this);
    t1.detach();
  }
}

void AudioQueue::dequeueSFX() {
  engine->playEffect(m_audio_queue.front().getFilePath(), false);
  std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(m_audio_queue.front().getLength()));
  m_audio_queue.pop();
  if (!m_audio_queue.empty()) {
    dequeueSFX();
  }
}
